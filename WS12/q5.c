//Author: Anusri Chavali
//Date: 11/24/2023
//What happens when we run this program normally? When I run this normally, it compiles well and based on ym program design, prints out all values of data. All the values equal 0. 
//What happens when we run this program with valgrind (leak-check=yes flag)? I get an invalid write error when writing to space 100. The heap summary says, "in use at exit: 400 bytes in 1 blocks" and "total heap usage: 2 allocs, 1 frees, 1,424 bytes allocated". The leak summary says, "definitely lost: 400 bytes in 1 blocks". So in this program, since we did not free the data, we have a data leak of 400 bytes, which is the amount taken up by the array of size 100. 
//Is this program correct? This program allocates memory correctly, but the issue is that it does not free the memory and it writes to an index beyond the cope of the array. So t compiles cleanly, but overall not correct because it writes to aa non-allocated location and creates memory leaks. 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//allocates an int array of size 100, and assigns 0 to the value data[100], which is out of the scope of the array. 
int main(void)
{
    int* data = (int*) malloc(100 * sizeof(int));
    data[100] = 0;
    for(int i = 0; i < 100; i++)
    {
        printf("%d ", data[i]);
    }
    return 0;
}