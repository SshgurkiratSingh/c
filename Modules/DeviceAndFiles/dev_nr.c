#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("Register a device nr and implement some callback func");
MODULE_VERSION("0.1");
/*
* @brief It is called, when device file is opened

*/
static int driver_open(struct inode *device_file, struct file *instance)
{
    printk(KERN_INFO "dev_nr -open was called\n");
    return 0;
}
/*
* @brief It is called, when device file is opened

*/
static int driver_close(struct inode *device_file, struct file *instance)
{
    printk(KERN_INFO "dev_nr -close was called\n");
    return 0;
}

static struct file_operations fops = {
    .owner = THIS_MODULE,
    .open = driver_open,
    .release = driver_close};
#define MYMAJOR 90
#define MYMINOR 0
static int __init
hello_init(void)
{
    int ret;
    printk(KERN_INFO "Hello World kernel module loaded\n");
    // Register the device
    ret = register_chrdev(MYMAJOR, "mydev_generic", &fops);
    if (retval > 0)
    {
        printk(KERN_ALERT "Can't get major number,registered with major:%d and minor:%d\n", reval >> 20, retval && 0xfffff);
    }
    else if (ret < 0)
    {
        printk(KERN_WARNING "Failed to register device\n");
        return ret;
    }
    else
    {
        printk(KERN_ALERT "Registered device with major number %d\n ", MYMAJOR);
    }

    static void __exit hello_exit(void)
    {
        unregister_chrdev(MYMAJOR, "mydev_generic");
        printk(KERN_WARNING "Goodbye World kernel module unloaded\n");
    }

    module_init(hello_init);
    module_exit(hello_exit);