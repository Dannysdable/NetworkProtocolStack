#include <linux/module.h>
#include <linux/init.h>
#include <linux/interrupt.h>

/*
 * cat /proc/interrupts
 * 确定eth0使用用的中断号
 * insmod irq1.ko irq=19
 * 19为网卡共享的中断号
 */
static int irq;
static char *interface="eth0";

//module_param(interface,charp,0644); //2.6内核中的宏
module_param(irq,int,0644);

static irqreturn_t  myinterrupt(int irq, void *dev_id)
{
	static int mycount = 0;
	if (mycount < 10) {
		printk("Interrupt!\n");
	mycount++;
	}
	return IRQ_NONE;
}

static int __init myirqtest_init(void)
{
	printk ("irq in +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
	if (request_irq(irq, &myinterrupt, IRQF_SHARED,interface, &irq)) {
		printk(KERN_INFO "myirqtest: register fialed IRQ %d\n", irq);
		return -EIO;
	}
	printk("%s Request on IRQ %d succeeded\n",interface,irq);
	return 0;
}
static void __exit myirqtest_exit(void)
{
	printk ("irq out ================================================================================\n");
	free_irq(irq, &irq);
	printk("Freeing IRQ %d\n", irq);
	return;
}

module_init(myirqtest_init);
module_exit(myirqtest_exit);
MODULE_LICENSE("GPL");
