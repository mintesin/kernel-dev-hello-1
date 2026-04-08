#include <stdio.h>

#define BUFFER_SIZE 10

int buffer[BUFFER_SIZE];
int in=0;
int out=0;
int main()
{

    int next_produced;
    

    while(1){
        while (((in+1)% BUFFER_SIZE) == out)
        {
           /*wait for emptying of the buffer*/
        } 

        buffer[in] = next_produced;
        in = (in+1)%BUFFER_SIZE;
}
}

