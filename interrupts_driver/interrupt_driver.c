#include <linux/init.h>
#include <linux/module.h>
#include <linux/interrupt.h>
#include <linux/kernel.h>

#define IRQ_NO 1  

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Siddhu");
MODULE_DESCRIPTION("Simple Interrupt Handler");

static irqreturn_t irq_handler(int irq, void *dev_id)
{
    printk(KERN_INFO "Interrupt Occurred: IRQ %d\n", irq);
    return IRQ_HANDLED;
}

static int __init irq_init(void)
{
    int result;
    printk(KERN_INFO "Initializing Interrupt Module\n");

    result = request_irq(IRQ_NO, irq_handler, IRQF_SHARED, "irq_handler", (void *)(irq_handler));
    if (result) {
        printk(KERN_ERR "Cannot register IRQ %d\n", IRQ_NO);
        return result;
    }

    printk(KERN_INFO "IRQ %d registered successfully\n", IRQ_NO);
    return 0;
}

static void __exit my_irq_exit(void)  
{
    free_irq(IRQ_NO, (void *)(irq_handler));
    printk(KERN_INFO "Interrupt Module Unloaded\n");
}

module_init(irq_init);
module_exit(my_irq_exit);  

