#include <linux/module.h>
#include <linux/fs.h>
#include <linux/uaccess.h>

#define DEVICE_NAME "my_char_device"
#define BUFFER_SIZE 1024

static int major_number;
static char *device_buffer;
static int device_open_count = 0;

// Open function
static int my_device_open(struct inode *inodep, struct file *filep)
{
    device_open_count++;
    printk(KERN_INFO "Device opened %d time(s)\n", device_open_count);
    return 0;
}

// Release function
static int my_device_release(struct inode *inodep, struct file *filep)
{
    printk(KERN_INFO "Device closed\n");
    return 0;
}

// Read function
static ssize_t my_device_read(struct file *filep, char *buffer, size_t len, loff_t *offset)
{
    int bytes_to_copy = min(len, (size_t)(BUFFER_SIZE - *offset));

    if (copy_to_user(buffer, device_buffer + *offset, bytes_to_copy))
    {
        return -EFAULT; // Failed to copy data to user space
    }

    *offset += bytes_to_copy;
    printk(KERN_INFO "Read %d bytes from the device\n", bytes_to_copy);
    return bytes_to_copy;
}

// Write function
static ssize_t my_device_write(struct file *filep, const char *buffer, size_t len, loff_t *offset)
{
    int bytes_to_copy = min(len, (size_t)(BUFFER_SIZE - *offset));

    if (copy_from_user(device_buffer + *offset, buffer, bytes_to_copy))
    {
        return -EFAULT; // Failed to copy data from user space
    }

    *offset += bytes_to_copy;
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
        printk(KERN_ALERT "Failed to register character device\n");
        return major_number;
    }
    device_buffer = kmalloc(BUFFER_SIZE, GFP_KERNEL);
    if (!device_buffer)
    {
        printk(KERN_ALERT "Failed to allocate memory for device buffer\n");
        unregister_chrdev(major_number, DEVICE_NAME);
        return -ENOMEM;
    }
    printk(KERN_INFO "Character device registered with major number %d\n", major_number);
    return 0;
}

static void __exit char_device_exit(void)
{
    kfree(device_buffer);
    unregister_chrdev(major_number, DEVICE_NAME);
    printk(KERN_INFO "Character device unregistered\n");
}

module_init(char_device_init);
module_exit(char_device_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Gurkirat Singh");
MODULE_DESCRIPTION("A basic character device that stores and returns a string");
