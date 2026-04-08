/*
*This is to clculate the elapsed time for children to run a command from terminal.
*The parent child communications is handled by shared memory.
*/
#include <stdio.h>
#include <stdlib.h>


#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/wait.h>

#define NAME "TIMElAPSE"
#define SIZE sizeof(long)

int main(int argc , char *argv[]) 
{   
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <command> [args...]\n", argv[0]);
        return EXIT_FAILURE;
    }
    struct timeval tv;
    long start,end,elapsed_time;
    long *ptr;
    int fd;
    pid_t pid;  
     

fd = shm_open(NAME, O_CREAT|O_RDWR, 0666);
ftruncate(fd,SIZE);
ptr =(long *) mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED,fd,0);   

pid = fork();

if(pid<0){
    fprintf(stderr,"Error: Failed to create a child");
    return EXIT_FAILURE;
}
if(pid==0){
    gettimeofday(&tv, NULL);
    start = tv.tv_sec*1000000L + tv.tv_usec;
    *ptr = start;
    execlp(argv[1],argv[1],NULL);
    perror("Exit failed");
    return EXIT_SUCCESS;
}

if(pid>0){
       wait(NULL);
        start = *ptr;
        gettimeofday(&tv,NULL); 
        end = tv.tv_sec*1000000L + tv.tv_usec;
        elapsed_time = end -start; 
        printf("The elapsed time is: %ld microseconds \n",elapsed_time); 

        munmap(ptr, SIZE);
        close(fd);
        shm_unlink(NAME);

} 
 return EXIT_SUCCESS;

} 

