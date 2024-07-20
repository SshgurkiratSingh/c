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
static int driver_open(struct inode *device_file) {}
static int __init hello_init(void)
{
    printk(KERN_INFO "Hello World kernel module loaded\n");
    return 0;
}

static void __exit hello_exit(void)
{
    printk(KERN_WARNING "Goodbye World kernel module unloaded\n");
}

module_init(hello_init);
module_exit(hello_exit);