//Author: Anusri Chavali
//Date: 11/24/2023
//What happens when we run this program normally? When I run this normally, it compiles well and it prints out a garbage value for the value at data[0]. 
//What happens when we run with valgrind? There are no memory leaks detected, however, we get an invalid read error. THis is because we are trying to read from a block that has already been freed. 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//allocate 100 size array, free it, and try to read a value from the freed array
int main(void)
{
    int* data = (int*) malloc(100 * sizeof(int));
    data[100] = 0;
    free(data);
    printf("%d", data[0]);
    return 0;
}