/*
*This code calculates the elapsed time to run a comamnd from terminal using pipes.
*The output is in microseconds.
*/

#include <stdio.h>
#include <stdlib.h> 
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/time.h>

#define READ 0
#define WRITE 1 

int fd[2];

int main(int argc, char *argv[]){ 
   if(argc<2){
      fprintf(stderr,"Please enter the command your are about to run.");
      return EXIT_FAILURE;
   }
   pid_t pid;
   struct timeval tv; /*Time value structure */
   long elapsed_time,start,end;

  
   
   pipe(fd); /*Creating the pipe for parent-child communication */
   pid = fork(); 

   if(pid<0){
    fprintf(stderr,"Error in child forking");
    return EXIT_FAILURE;
   } 
    // fd() creating the pipe here
   if(pid ==0){
            close(fd[READ]);
            gettimeofday(&tv,NULL);
            start = tv.tv_sec*1000000L + tv.tv_usec;
            write(fd[WRITE],&start,sizeof(start));
            execlp(argv[1],argv[1],NULL);
           
      return EXIT_SUCCESS;
   } 
   close(fd[WRITE]);
   if(pid>0){
        wait(NULL);
        read(fd[READ],&start,sizeof(start));
       
        close(fd[READ]);
         gettimeofday(&tv, NULL);
         end = tv.tv_sec*1000000L + tv.tv_usec;
        elapsed_time = end - start;
        fprintf(stdout,"The elapsed time is: %ld micorseconds \n",elapsed_time);
  

   } 

   return EXIT_SUCCESS;

}