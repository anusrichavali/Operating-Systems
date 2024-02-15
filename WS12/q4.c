//Author: Anusri Chavali
//Date: 11/24/2023
//What happens when we run this program normally? Returns Integer: 4
//What happens when we run this program with valgrind (leak-check=yes flag)? The heap summary says, "in use at exit: 4 bytes in 1 blocks, total heap usage: 2 allocs, 1 frees, 1,028 bytes allocated". The leak summary says: "definitely lost: 4 bytes in 1 blocks". So the valgrind tells us that there are no errors but we definitely have memory leaks since we did not free the malloc. 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//allocates space for an integer and does not free it
int main(void)
{
    int *ptr = (int*) malloc(sizeof(int));
    *ptr = 4;
    printf("Integer: %d\n", *ptr);
}