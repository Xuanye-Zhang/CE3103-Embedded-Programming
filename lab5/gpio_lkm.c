#include <linux/gpio.h>
#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/kernel.h>
#include <linux/module.h>

static unsigned int ledGreen = 4;       // GPIO 4 (pin 7) connected to green LED
static unsigned int pushButton = 11;    // GPIO 11 (pin 23) connected to button
static unsigned int irqNumber;          // share IRQ num within file
static bool ledOn = false;                  // toggle LED

// GPIO IRQ handler function
static irq_handler_t rpi_gpio_isr(unsigned int irq,void *dev_id, struct pt_regs *regs
)
{
    ledOn = !ledOn;
    gpio_set_value(ledGreen, ledOn);

    printk(KERN_ALERT "GPIO Interrupt!\n");
    return (irq_handler_t) IRQ_HANDLED;
}

// LKM exit function
static void __exit rpi_gpio_exit(void)
{
    gpio_set_value(ledGreen, false);    // turn LED off
    gpio_free(ledGreen);
    gpio_free(pushButton);
    free_irq(irqNumber, NULL);

    printk(KERN_ALERT "Goodbye from the GPIO LKM\n");
}

// LKM initialisation function
static int __init rpi_gpio_init(void)
{
    int result = 0;
    printk(KERN_ALERT "Initialising the GPIO LKM\n");

    ledOn = true;                           // default: LED on
    gpio_request(ledGreen, "sysfs");        // request for LED GPIO
    gpio_direction_output(ledGreen, ledOn); // set mode to output, turn LED on

    gpio_request(pushButton, "sysfs");      // request for button GPIO
    gpio_direction_input(pushButton);       // set mode to input
    int r = gpio_set_debounce(pushButton, 1000);    // debounce delay of 1000
    printk(KERN_ALERT "return from debounce: %d\n", r);
    

    irqNumber = gpio_to_irq(pushButton);    // map button to IRQ num
    printk(KERN_ALERT "Button mapped to IRQ: %d\n", irqNumber);

    // request for interrupt line
    result = request_irq(
        irqNumber,
        (irq_handler_t) rpi_gpio_isr,
        IRQF_TRIGGER_RISING,
        "rpi_gpio_handler",
        NULL
    );

    return result;
}

module_init(rpi_gpio_init);
module_exit(rpi_gpio_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Zhang Xuanye");
MODULE_DESCRIPTION("Toggle Green LED with button");
MODULE_VERSION("v1");
