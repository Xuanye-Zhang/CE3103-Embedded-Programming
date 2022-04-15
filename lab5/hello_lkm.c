#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>

static int __init hello_init(void)
{
    printk(KERN_ALERT "Hello from kernel world\n");
    return 0;
}

static void __exit hello_exit(void)
{
    printk(KERN_ALERT "Goodbye from kernel world\n");
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Zhang Xuanye");
MODULE_DESCRIPTION("Hello module");
MODULE_VERSION("v1");
