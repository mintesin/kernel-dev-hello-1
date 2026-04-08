#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/stat.h>


int main(int argc , char argv[]){
    /*size of memory */
    const int size = 4096;
   /*File descriptor name */
    const char *name = "OS";
   /*File descriptor of the file returned from shm_open()*/
    int fd;
   /*pointer to the shared memory object after maped to memory*/
    char *ptr; 
   /*Open the shared memory file*/ 

   fd = shm_open(name,O_RDONLY,0666);
   /*Memory map the shared memeory object*/
  ptr = (char *)mmap(0,size, PROT_READ | PROT_WRITE, MAP_SHARED,fd,0);

  /*Read from the shared memory object */ 
  printf("%s",(char *)ptr); 
  //sprintf((char *)ptr,"%s");
  /*Remove the shared memory object */

  shm_unlink(name);

  return 0;

} 


    