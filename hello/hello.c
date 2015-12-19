/*************************************************************************
	> File Name: hello.c
	> Author: Danny
	> Mail: dannysdable@gmail.com 
	> Created Time: 2015-08-10 16:38 下午
 ************************************************************************/

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/moduleparam.h>
#include <linux/stat.h>

MODULE_LICENSE("Dual BSD/GPL");

static char *whom = "world";
static int howmany = 1;

module_param(howmany, int, S_IRUGO);
module_param(whom, charp, S_IRUGO);

static int hello_init(void)
{
	printk(KERN_ALERT "Hello, world\n");
	printk(KERN_ALERT "howmany = %d\n", howmany);
	//printk(KERN_DEBUG "Hello, world\n");

	return 0;
}

static void hello_exit(void)
{
	printk(KERN_ALERT "Goodbye, cruel world\n");
	//printk(KERN_DEBUG "Goodbye, cruel world\n");
}

module_init(hello_init);
module_exit(hello_exit);

