#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>

/*
* First create shared memory object with shm_open() POSIX API
* parameters- object name, CREATE OF IT DOESN'T EXIST AND THE PERMISSION NUMBER 
* Returns integer file descriptor for the for the shared memory object. 
*/

// fd = shm_open(name, O_CREATE | O_RDWR, 0666);

/*
*Setting the size of the object bby fdtruncate(fd, size(4096))
*/

// fdtruncate(fd,4096) 

int main( int argc, int argv){ 
    /*The size of the memory of the shared memory object*/
    const int size = 4096;
    /*shared memory file descriptor*/
    int fd; 
    /*shared memory object name*/ 
    char const *name  = "OS"; 
    /*Strings written to the shared memory*/
    const char *message_0 = "Hello";
    const char *message_1 = " World!"; 
    /*pointer to the shared memory object*/
    char *ptr;

    /*Create the shared memory object */ 
    
    fd = shm_open(name,O_CREAT | O_RDWR, 0666);
    
    /*Configure the size of shared memory object*/
    ftruncate(fd,size);

    /*Map the shared memory object to memory*/

    ptr = (char *) mmap(0, size, PROT_READ | PROT_WRITE , MAP_SHARED,fd,0);
    
    /*write to the shared memory*/ 
    sprintf(ptr,"%s",message_0);
    ptr +=strlen(message_0);
    sprintf(ptr,"%s",message_1);
    ptr +=strlen(message_1); 

    return 0;
    
}

