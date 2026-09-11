#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("test");
MODULE_DESCRIPTION("test module");

static int __init test_init(void){
    pr_info("kpms loaded\n");
    return 0;
}
static void __exit test_exit(void){
    pr_info("kpms unloaded\n");
}

module_init(test_init);
module_exit(test_exit);
