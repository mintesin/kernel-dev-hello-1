#include <stdio.h>

#define BUFFER_SIZE 10


int buffer[BUFFER_SIZE];
int in=0;
int out=0;

int main(){
    int next_conusmed;

    while(1){
    while(in==out){
        /*Wait for something to happen in the buffer*/
    } 
       next_conusmed = buffer[out];
       out = (out+1)%BUFFER_SIZE;

    }

}