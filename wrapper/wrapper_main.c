#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

#include "wrapper_misc.h"

#define WRAPPER_MODULE_NAME "mb_wrapper"

static int __init mb_wrapper_init(void)
{
    printk(KERN_INFO "%s loaded\n", WRAPPER_MODULE_NAME);
    return 0;
}

static void __exit mb_wrapper_exit(void)
{
    printk(KERN_INFO "%s unloaded\n", WRAPPER_MODULE_NAME);
}

module_init(mb_wrapper_init);
module_exit(mb_wrapper_exit);


MODULE_LICENSE("GPL");
MODULE_AUTHOR("MajinBuu");
MODULE_DESCRIPTION("GPL Wrapper for private module");