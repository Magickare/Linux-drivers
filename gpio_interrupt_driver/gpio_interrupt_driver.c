#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/gpio.h>
#include <linux/interrupt.h>

#define GPIO_BUTTON 17  

static unsigned int irq_number;

static irqreturn_t irq_handler(int irq, void *dev_id) {
    printk(KERN_INFO "Interrupt: GPIO %d triggered\n", GPIO_BUTTON);
    return IRQ_HANDLED;
}

static int __init gpio_irq_init(void) {
    int result;

    printk(KERN_INFO "Initializing GPIO IRQ module\n");

    if (!gpio_is_valid(GPIO_BUTTON)) {
        printk(KERN_INFO "Invalid GPIO\n");
        return -ENODEV;
    }

    gpio_request(GPIO_BUTTON, "sysfs");
    gpio_direction_input(GPIO_BUTTON);
    gpio_set_debounce(GPIO_BUTTON, 200);
    gpio_export(GPIO_BUTTON, false);

    irq_number = gpio_to_irq(GPIO_BUTTON);
    printk(KERN_INFO "GPIO mapped to IRQ: %d\n", irq_number);

    result = request_irq(irq_number, irq_handler, IRQF_TRIGGER_RISING, "gpio_irq_handler", NULL);

    return result;
}

static void __exit gpio_irq_exit(void) {
    printk(KERN_INFO "Exiting GPIO IRQ module\n");
    free_irq(irq_number, NULL);
    gpio_unexport(GPIO_BUTTON);
    gpio_free(GPIO_BUTTON);
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Siddhu");
MODULE_DESCRIPTION("GPIO Interrupt Example");

module_init(gpio_irq_init);
module_exit(gpio_irq_exit);

