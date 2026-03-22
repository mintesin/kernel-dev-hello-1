/*
* The first Assignment on kernel module.
* Creates /proc/jiffies entry.
* when it is invoked as /proc/jiffies:
* it returns the number of jiffies in the system since booting
*/

#include <linux/init.h>
#include <linux/module.h>
#include <linux/jiffies.h>
#include <linux/uaccess.h>
#include <linux/proc_fs.h>

/*
*The buffer size in the kernel will be 128.
*The entry in the proc file will be jiffies.
*/
#define BUFFER_SIZE 128 
#define PROC_NAME "jiffies"

static ssize_t proc_read(struct file *file, char __user *usr_buff, size_t count, loff_t *pos){
    int rv;
    char buffer[BUFFER_SIZE]; /*The buffer in the kernel where the jiffies should be written*/
    static int completed = 0; 
   
    if(completed){
        completed=0;
        return 0;    /*When the completed variable becomes 1 the callback stops
        * This will stop the callback from running infinitely.
        */
    }

    completed +=1;

    rv = sprintf(buffer,"The number of jiffes since booting are: %lu jiffies and %lu HZ\n",jiffies,HZ);  /*Writing jiffies to the buffer in the kernel. */
    if(copy_to_user(usr_buff,buffer,rv)){ /*Copying the content of the kernel buffer to the user space. */
        return -EFAULT;
    }

    return rv;


}
/*Defining the structure with reading call back.*/
static struct proc_ops proc_ops = {   
    .proc_read = proc_read,
};

static int __init upon_loading(void){ 
    proc_create(PROC_NAME,0666,NULL,&proc_ops);
    return 0;
}

static void __exit upon_exiting(void){
    remove_proc_entry(PROC_NAME,NULL);
} 

module_init(upon_loading);
module_exit(upon_exiting);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("PROC FILES FOR JIFFIES");
MODULE_AUTHOR("MINTESINOT ARGAW");