#include <linux/module.h>
#include <linux/fs.h>
#include <linux/kernel.h>
#include <linux/uaccess.h>

#define DEVICE_NAME "my_char_device"
#define BUFFER_SIZE 1024

static int major_number;
static char device_buffer[BUFFER_SIZE] = {0};
static loff_t device_offset = 0; // Crucial: Initialize to 0
static int device_open_count = 0;

// Function prototypes for better organization
static int my_device_open(struct inode *inodep, struct file *filep);
static int my_device_release(struct inode *inodep, struct file *filep);
static ssize_t my_device_read(struct file *filep, char *buffer, size_t len, loff_t *offset);
static ssize_t my_device_write(struct file *filep, const char *buffer, size_t len, loff_t *offset);

// open function
static int my_device_open(struct inode *inodep, struct file *filep)
{
    device_open_count++;
    printk(KERN_INFO "Device opened %d time(s)\n", device_open_count);
    // Reset offset on open
    device_offset = 0;
    return 0;
}

// release function
static int my_device_release(struct inode *inodep, struct file *filep)
{
    printk(KERN_INFO "Device closed\n");
    return 0;
}

// read function
static ssize_t my_device_read(struct file *filep, char *buffer, size_t len, loff_t *offset)
{
    int bytes_to_copy = min(len, (size_t)(BUFFER_SIZE - device_offset));

    if (bytes_to_copy <= 0)
    {
        return 0; // Nothing to read
    }

    if (copy_to_user(buffer, device_buffer + device_offset, bytes_to_copy))
    {
        return -EFAULT;
    }

    device_offset += bytes_to_copy;
    *offset += bytes_to_copy; // Update user-space offset
    printk(KERN_INFO "Read %d bytes from the device\n", bytes_to_copy);
    return bytes_to_copy;
}

// write function
static ssize_t my_device_write(struct file *filep, const char *buffer, size_t len, loff_t *offset)
{
    int bytes_to_copy = min(len, (size_t)(BUFFER_SIZE - device_offset));

    if (bytes_to_copy <= 0)
    {
        return 0; // Nothing to write
    }

    if (copy_from_user(device_buffer + device_offset, buffer, bytes_to_copy))
    {
        return -EFAULT;
    }

    device_offset += bytes_to_copy;
    *offset += bytes_to_copy; // Update user-space offset
    printk(KERN_INFO "Wrote %d bytes to the device\n", bytes_to_copy);
    return bytes_to_copy;
}

static struct file_operations fops = {
    .open = my_device_open,
    .release = my_device_release,
    .read = my_device_read,
    .write = my_device_write,
};

static int __init char_device_init(void)
{
    major_number = register_chrdev(0, DEVICE_NAME, &fops);
    if (major_number < 0)
    {
        printk(KERN_ALERT "Registering char device failed with %d\n", major_number);
        return major_number;
    }
    printk(KERN_INFO "I was assigned major number %d. To talk to\n", major_number);
    return 0;
}

static void __exit char_device_exit(void)
{
    unregister_chrdev(major_number, DEVICE_NAME);
    printk(KERN_INFO "Goodbye World kernel module unloaded\n");
}

module_init(char_device_init);
module_exit(char_device_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Gurkirat Singh");
MODULE_DESCRIPTION("A basic character device that stores and returns a string");