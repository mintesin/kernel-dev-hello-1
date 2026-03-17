/*
*kernel_intro.c - This is like the first code intorductory code for kernle program.
*/

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/hash.h>
#include <linux/gcd.h>

/*This is the function loaded when the function is called for the fist time*/

static int __init intro_function(void){ 
     printk(KERN_INFO "The kernel module is loading.....\n");
     /*Printing Golden ratio prime from the hash module in the kernel
     * up on loading.
     */
     printk(KERN_INFO "%llu\n",(unsigned long long )GOLDEN_RATIO_PRIME);
    return 0;
}
/*This is the finction running up on removal of the module*/
static void __exit exit_func(void){
      printk(KERN_INFO "The kernel moduel is removed \n");
      /*Prints the greatest common divisor 
      * up on removal fo the module.
      */
      printk(KERN_INFO "%lu\n",(unsigned long)gcd(3300,24));
}

/*Registering the function */
module_init(intro_function);
module_exit(exit_func);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("THIS IS MY FIRST INTRO KERNEL");
MODULE_AUTHOR("MINTESINOT ARGAW");


