#include <sys/types.h> 
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h> 



int main()
{
    pid_t pid; 
    /*fork a child process*/

    pid = fork();

    if(pid<0){ /*Error occured*/
        fprintf(stderr,"Fork Failed \n");
        return 1;
    } 
    else if (pid ==0 ){/*child process */
          printf("The child is running\n");
          execlp("/bin/ls","ls",NULL);
    } 
    else { /*Parent Process */
        /*Parent will wait for the child to complete */
        wait(NULL);  
        printf("CHILD COMPLETE\n");

    }
      return 0;     

}