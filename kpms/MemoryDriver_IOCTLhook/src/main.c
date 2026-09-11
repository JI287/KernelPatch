#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <kernelpatch/kpms.h>

static long (*orig_unlocked_ioctl)(struct file *, unsigned int, unsigned long);

static long hooked_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
    pr_info("MemoryDriver IOCTL hook triggered, cmd=0x%x\n", cmd);
    return orig_unlocked_ioctl(file, cmd, arg);
}

static int __init hook_init(void)
{
    struct file_operations *fops;
    // 这里替换成目标驱动的fops地址，演示仅作占位
    fops = NULL;
    if (!fops || !fops->unlocked_ioctl) {
        pr_err("fops or unlocked_ioctl is NULL\n");
        return -EINVAL;
    }
    orig_unlocked_ioctl = fops->unlocked_ioctl;
    kpms_hook_symbol(&fops->unlocked_ioctl, hooked_ioctl);
    pr_info("MemoryDriver IOCTL hook loaded\n");
    return 0;
}

static void __exit hook_exit(void)
{
    kpms_unhook_all();
    pr_info("MemoryDriver IOCTL hook unloaded\n");
}

module_init(hook_init);
module_exit(hook_exit);
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("KPMS MemoryDriver IOCTL Hook Demo");
