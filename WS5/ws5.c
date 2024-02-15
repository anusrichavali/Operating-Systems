/* Author: Anusri Chavali
Date: 9/27/2023
Purpose: Prints a message with process ID of 4 processes using fork and parallel processing */
#include <stdio.h>
#include <unistd.h>

//Call fork twice to create 4 parallel processes 
//Print after so that each process prints a statement
int main(void)
{
    fork();
    fork();
    printf("hello world from PID %d!\n", getpid());
    return 0;
}