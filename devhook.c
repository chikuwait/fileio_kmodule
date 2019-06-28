#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>
#include <linux/module.h>
#define NUM_BUFFER 256
static char stored_value[NUM_BUFFER];

static int chardev_open(struct inode *inode, struct file *filep)
{
	printk(KERN_INFO "Device open\n");
	return 0;
}

static int chardev_close(struct inode *inode, struct file *filep)
{
	printk(KERN_INFO "Device close\n");
	return 0;
}


ssize_t chardev_read(struct file *p, char __user *usr, size_t size, loff_t *loff)
{
	printk(KERN_INFO "Device read\n");
	return 0;
}

ssize_t chardev_write(struct file *p, const char __user *usr, size_t size, loff_t *loff)
{
	printk(KERN_INFO "Device write\n");

	if(copy_from_user(stored_value,usr,size) != 0){
		return -1;
	}
	printk("%s\n", stored_value);
	return size;
}

static struct file_operations chardev_fops = {
    .owner = THIS_MODULE,
    .open = chardev_open,
    .release = chardev_close,
    .read = chardev_read,
    .write = chardev_write,
};


static int __init hook_init(void)
{
	struct cdev *cdev;
	dev_t dev =MKDEV(240,0);

	register_chrdev_region(dev, 1, "hello");
	cdev = cdev_alloc();
	cdev->ops = &chardev_fops;
	int err = cdev_add(cdev, dev, 1);
	return 0;
}

static void __exit hook_exit(void)
{
	printk(KERN_INFO "Bye World\n");
	return ;
}

module_init(hook_init);
module_exit(hook_exit);

MODULE_LICENSE("MIT");
MODULE_AUTHOR("chikuwait");
