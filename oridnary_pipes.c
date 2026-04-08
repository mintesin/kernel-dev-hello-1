/*
*This is an ordinary unix pipe 
*/ 

#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 256 
#define READ_END 0
#define WRITE_END 1 

int main(){
    char write_msg[BUFFER_SIZE] = "Greetings";
    char read_msg[BUFFER_SIZE];
    int fd[2];
    pid_t pid; 
  /*Creating pipe*/ 
    
  if(pipe(fd))==-1){
    fprintf(stderr,"Error in pipe creation");
    return EXIT_FAILURE;
  }

    /*create child process*/ 

    if ((pid = fork()<0){
        fprintf(stderr,"Error in forking child");
        return EXIT_FAILURE;
    }

    /*Parent process */
    if(pid>0){ 
       /*CLose the unnused end of the pipe*/
       close(fd[READ_END]);
       
       /*Write to the pipe*/
       write(fd[WRITE_END], write_msg,strlen(write_msg)+1);
       /*Close the write end of the pipe*/
       close(fd[WRITE_END]);

    }
    if(pid==0){
        /*close the unused end of the pipe*/
        close(fd[WRITE_END]);
        /*Read from the pipe*/
        read(fd[READ_END],read_msg,BUFFER_SIZE);
        /*Close the read file*/
        close(fd[READ_END]); 


    }

    return 0;
}