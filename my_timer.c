/*
 * my_timer Kernel Module
 */

#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/timer.h>
#include <linux/jiffies.h>

/* Static Variable Declarations */
static struct timer_list my_timer;
static unsigned long jfsperiod = 0;
static unsigned long counter = 0;      /* Counter for number of times timer awoken */

/* Callback Function Prototype */
static void my_timer_callback(struct timer_list *timer);

/* Param Defitinions */
static char* name = "DEFAULT";      /* DEFAULT is default name for timer module */
static unsigned long period = 500;  /* Default period is 500msec */

/* Callback Function for Timer Module */
static void my_timer_callback(struct timer_list *timer)
{
   counter++;
   printk(KERN_INFO "my_timer module for Roberto Baquerizo woken up %lu times\n",
         counter);

   mod_timer(&my_timer, jiffies + jfsperiod);
}

/* Init Function for Timer Module */
static int __init my_timer_init(void)
{
   timer_setup(&my_timer, my_timer_callback, 0);
   jfsperiod = msecs_to_jiffies(period);
   mod_timer(&my_timer, jiffies + jfsperiod);
   printk(KERN_INFO "Loaded %s kernel timer module with period %lu msec\n",
           name, period);

   return 0;
}

/* Exit Function for Timer Module */
static void __exit my_timer_exit(void)
{
   del_timer(&my_timer);
   printk(KERN_INFO "my_timer module unloaded\n");
}

module_param(name, charp, 0);
module_param(period, ulong, 0);
MODULE_PARM_DESC(name, "Name of the kernel timer.");
MODULE_PARM_DESC(period, "Timer count time in milli-seconds.");

module_init(my_timer_init);
module_exit(my_timer_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Roberto Baquerizo.");
MODULE_DESCRIPTION("Kernel Module using Kernel Timer.");
















