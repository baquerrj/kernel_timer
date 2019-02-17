/*
 * my_timer Kernel Module
 */

#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/timer.h>
#include <linux/jiffies.h>

static struct timer_list my_timer;
static void my_timer_callback(struct timer_list *timer);

static char* name = "DEFAULT";
static unsigned long period = 500; /* Default period is 500msec */
static unsigned long jfsperiod ;
static unsigned long counter = 0;

static void my_timer_callback(struct timer_list *timer)
{
   counter++;
   pr_info("my_timer module for Roberto Baquerizo woken up %lu times\n",
         counter);

   mod_timer(&my_timer, jiffies + jfsperiod);
}

static int __init my_timer_init(void)
{
   timer_setup(&my_timer, my_timer_callback, 0);
   jfsperiod = msecs_to_jiffies(period);
   mod_timer(&my_timer, jiffies + jfsperiod);
   pr_info("Loaded %s kernel timer module with period %lu msec\n",
           name, period);

   return 0;
}

static void __exit my_timer_exit(void)
{
   del_timer(&my_timer);
   pr_info("my_timer module unloaded\n");
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
















