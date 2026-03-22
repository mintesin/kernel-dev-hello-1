/*
 * info_timer.c - Kernel module to print jiffies and HZ info
 */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/jiffies.h>

static unsigned long start_jiffies;

/*
 * Messages jiffies on load and HZ.
 */
static int __init upon_loading(void)
{
    start_jiffies = jiffies;
    pr_info("Jiffies on load: %lu\n", start_jiffies);
    pr_info("HZ: %lu\n", HZ);
    return 0;
}

/*
 * Messages jiffies on unload.
 */
static void __exit upon_removal(void)
{
    unsigned long end_jiffies = jiffies;
    pr_info("Jiffies on unload: %lu\n", end_jiffies);
}

module_init(upon_loading);
module_exit(upon_removal);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("System Timer Information");
MODULE_AUTHOR("MINTESINOT ARGAW");
