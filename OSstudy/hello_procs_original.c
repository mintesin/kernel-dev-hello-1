/*
*hello_procs.c - is hello proc module written to interact with proc file 
*/ 

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/uaccess.h> 


#define BUFFER_SIZE 4096
#define PROC_NAME "Hello"

/* Initilaize the module */ 

ssize_t proc_read(struct file *file, char __user *usr_buff, size_t count, loff_t *pos){
    int rv = 0;
    char buffer[BUFFER_SIZE];
    static int  completed = 0;
    if(completed){
        completed = 0;
        return 0;
    }

    completed=1;
    rv=sprintf(buffer,"Hello world");
    copy_to_user(usr_buf,buffer,rv);

    return rv;
}
static struct proc_ops proc_ops = {
    .proc_read = proc_read,
};


/*This functions is called up module loadiing*/

static int __init upon_loading(void){
    /*Creates the /proc/Hello entry loading to the kernel*/
     proc_create(PROC_NAME,0666,NULL,&proc_ops);

    return 0;
} 


static void __exit upon_exiting(void){
    /* removes /proc/Hello entry up on exiting the kernel*/
   remove_proc_entry(PROC_NAME,NULL);
} 

module_init(upon_loading);
module_exit(upon_exiting);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("HELLO PROC FILE");
MODULE_AUTHOR("MINTESINOT");

