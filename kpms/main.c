#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("test");
MODULE_DESCRIPTION("GKI out-of-tree module: list all processes");
MODULE_VERSION("0.1");

static int __init kpms_init(void)
{
    struct task_struct *task;
    pr_info("kpms loaded, start dump process list:\n");

    for_each_process(task) {
        pr_info("pid:%d | comm:%s\n", task->pid, task->comm);
    }
    pr_info("kpms: process list done\n");
    return 0;
}

static void __exit kpms_exit(void)
{
    pr_info("kpms unloaded\n");
}

module_init(kpms_init);
module_exit(kpms_exit);
