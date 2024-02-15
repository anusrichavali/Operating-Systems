/* Author: Anusri Chavali
Date Last Modified: 12/3/2023
Purpose: This program reads values into matrices from file inputs and returns the result of (A*W). It does so by using threads to compute the values for each individual cell, and then adds those values into the shared matrix R. After the inital computation, the program can keep receiving A matrix filenames from the parent program, at which point the program reallocates R and computes the values for the new matrix.  
Sources: To understand how to implement the matrix multiplication using threads, I referenced Geeks for Geeks: Multiplication of Matrix using Threads
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>
#include <stdbool.h>

//define the row and col size for the matrices
#define ROWS 8
#define COLS 8

//create locks for protection memory allocation and printing
//did not use lock for modifying values in R because I use pthread_join to synchronize
pthread_mutex_t lockMem;
pthread_mutex_t lockPrint;
/*the multiplMatrix function takes in rows, cols, the current A row and W matrix, and the matrix to store the results in*/
/*The dot product of each row times the column of W is calculated and stored in the result matrix*/
//this is the thread runner function, so it exits the thread and returns the computed value of the sum of row of A times col W values
void *multiplyMatrix(void* arg)
{
    int *values = (int *) arg;
    int k = 0; 

    //iterate through the received array, where row values are stored in the first 8 positions and cols values in the last 8
    //corresponding values are added
    int x = values[0];
    for(int i = 1; i <= x; i++)
    {
        k += values[i]*values[i+x];
    }
    int *val = (int*)malloc(sizeof(int));
    *val = k;
    pthread_exit(val);
    free(val);
}

//the read from file method takes a filename, file pointer, and the matrix to read the values into
//it iterates through the rows of the file and populates the matrix with those values
//the empty values are 0s in the matrix
void readFromFile(char name[256], FILE *f, int matrix[ROWS][COLS])
{
    char buffer[1024];
    int v[ROWS] = {0, 0, 0, 0, 0, 0, 0, 0};
    f = fopen(name, "r+");
    if(f == NULL)
    {
        fprintf(stderr, "can't open file\n");
        exit(1);
    }
    int r = 0;
    while(fgets(buffer, sizeof(buffer), f) != NULL)
    {
        /* if statement to remove newlines in buffer line */
        if(buffer[strlen(buffer) - 1] == '\n')
        {
            buffer[strlen(buffer) - 1] = '\0';
        }

        //inputs from each file are read into the temporary array 
        sscanf(buffer, "%d %d %d %d %d %d %d %d", &v[0], &v[1], &v[2], &v[3], &v[4], &v[5], &v[6], &v[7]);
        
        /*for loop to add five values from each row into the current row of W*/
        for(int c = 0; c < COLS; c++)
        {
            matrix[r][c] += v[c];
            v[c] = 0;
        }

        r++;
    }

    fclose(f);
}

//function to zero the defined 8x8 matrices
void zero(int R[ROWS][COLS])
{
    for(int i = 0; i < ROWS; i++)
    {
        for(int j = 0; j < COLS; j++)
        {
            R[i][j] = 0;
        }
    }
}

//function to set the malloc and realloc arrays to 0
void setR(int index, int* ptr)
{
    for(int i = index; i < ROWS * COLS; i++)
    {
        ptr[i] = 0;
    }
}

//the printFinal function takes the pointer of a dynamic array and prints out the values based on the number of rows in the array
void printFinal(int numRows, int* ptr)
{
    pthread_mutex_lock(&lockPrint);
    printf("R = [\n");
    /*The result of the computation of A * W is printed out */
    for(int i = 0; i < numRows; i++)
    {
        for(int j = 0; j < COLS; j++)
        {
            
            printf("%d ", ptr[i*COLS + j]);
        }
        printf("\n");
    }
    printf("]\n");
    pthread_mutex_unlock(&lockPrint);
}

/*Main function takes 4 arguments (argc = 4), the program call followed by 3 file paths*/
/*Assumptions: the user will input 3 files which will have non-negative integers and each row is separated by newline*/
/*Steps: first intializes 3 arrays of fixed dimensions, next reads values from files into each array, finally calculates A * W + B*/
int main(int argc, char* argv[])
{

    /*Initialize variables to store each filename to print at the end*/
    /*Initializing 2 Arrays, A and W, with fixed dimensions*/
    //initialize parameter starting, which keeps track of first row in r_ptr of each iteration
    int A[ROWS][COLS];
    int W[ROWS][COLS];
    zero(A);
    zero(W);
    int starting = 0;

    //locks the allocation of the matrix memory
    pthread_mutex_lock(&lockMem);
    int *volatile r_ptr = malloc((ROWS*COLS) * sizeof(int));
    setR(starting, r_ptr);
    pthread_mutex_unlock(&lockMem);

    FILE *file;

    //checks that correct number of files entered
    if(argc != 3)
    {
        int exitcode = 1;
        fprintf(stderr, "error: expecting exactly 2 files as input\nTerminating, exit code %d.\n", exitcode);
        exit(1);
    }
    
    for(int i = 1; i < argc; i++)
    {
        /* Initializing a FILE variable which will open each file in argv to read it
        Also initalizing the filename, and setting up characters which will allow us to modify the filename to print appropriate messages*/
        char *filename = argv[i];

        /*This if statement checks each file, and if the file can not be opened, prints error message and exits with code 1*/
        if(file == NULL)
        {   
            int exitcode = 1;
            fprintf(stderr, "error: cannot open file %s \nTerminating, exit code %d.\n", filename, exitcode);
            exit(1);
        }

        //Reads the first file and assigns the values into A
        if(i == 1)
        {
            /*set Aname to the filename */
            readFromFile(filename, file, A);
        }
        //reads the second file and assigns values into W
        else
        {
            readFromFile(filename, file, W);
            
        }
    }

    //define the size of the array to store all the threads
    //initialize count to iterate through threads, and *data to store the values for multiplication in threads
    int size = ROWS * COLS;
    pthread_t *threads = (pthread_t*)malloc(size*sizeof(pthread_t));
    int count = 0;
    int *values = NULL;
    //iterate through rows of A and columns of B and add to values array
    //create a thread and send the values array to the thread runner function, multiplyMatrix
    for(int i = 0; i < ROWS; i++)
    {
        for(int j = 0; j < COLS; j++)
        {
            values = (int *)malloc((20)*sizeof(int));
            values[0] = COLS;

            for(int k = 0; k < COLS; k++)
            {
                values[k + 1] = A[i][k];
            }

            for(int k = 0; k < ROWS; k++)
            {
                values[k + COLS + 1] = W[k][j];
            }

            pthread_create(&threads[count++], NULL, multiplyMatrix, (void*)values);

        }
        free(values);
    }

    //the result of each thread's computation for a particular cell is added to the appropriate cell in R
    count = 0;
    for(int i = 0; i < ROWS; i++)
    {
        for(int j = 0; j < COLS; j++)
        {
            void *k;
            pthread_join(threads[count], &k);
            int *p = (int *)k;
            r_ptr[i* COLS + j] = *p;
            count++;
        }
    }
    free(threads);

    printf("%s x %s\n", argv[1], argv[2]);

    //numRows is used to keep track of how many rows to put in the array -- 8 more are added after another filename is passed through the pipe
    size_t numRows = ROWS;
    char input[256] = {'\0'};
    //filename input is read in from stdin -- the stdin values are passed in from the pipe set up in parent process
    while(read(STDIN_FILENO, &input, sizeof(input)) > 0)
    {
        //null terminate input
        if(input[strlen(input) - 1] == '\n')
        {
            input[strlen(input) - 1] = '\0';
        }
        
        //compare input to done; if the parent has sent done to the child, that means ctrl-d has been sent and input stream is done
        if(strcmp(input, "done") == 0)
        {
            break;
        }

        //reallocate the threads array for each new input A matrix
        pthread_t *threads = (pthread_t*)malloc(size*sizeof(pthread_t));
        count = 0;

        //read from the file specified by input into zeroed out A matrix
        zero(A);
        readFromFile(input, file, A);
        //numRows and starting are incremented by 8 (numRows is last row, starting is first row of newly added portion of result)
        numRows += ROWS;
        starting += ROWS;

        //lock reallocation which is a critical section
        pthread_mutex_lock(&lockMem);
        //reallocate the result matrix with the new amount of rows, and set all the new rows to 0
        r_ptr = realloc(r_ptr, (numRows * COLS) * sizeof(int));
        setR(starting, r_ptr);
        pthread_mutex_unlock(&lockMem);
        //iterate through the rows of A and cols of W, add to tge values array, and send to the thread_runner function multiplyMatrix
        for(int i = 0; i < ROWS; i++)
        {
            int *values = NULL;
            for(int j = 0; j < COLS; j++)
            {
                values = (int *)malloc((20)*sizeof(int));
                values[0] = COLS;

                for(int k = 0; k < COLS; k++)
                {
                    values[k + 1] = A[i][k];
                }

                for(int k = 0; k < ROWS; k++)
                {
                    values[k + COLS + 1] = W[k][j];
                }

                pthread_create(&threads[count++], NULL, multiplyMatrix, (void*)values);
            }
            free(values);
        }

        //iterate through the threads and add to the appropriate position of r_ptr
        count = 0;
        for(int i = starting; i < numRows; i++)
        {
            for(int j = 0; j < COLS; j++)
            {
                void *k;
                pthread_join(threads[count], &k);
                int *p = (int *)k;
                r_ptr[i* COLS + j] = *p;
                free(p);
                count++;
            }
        }
        free(threads);

        printf("%s x %s\n", input, argv[2]);

    }

    //after all inputs are done, print out the entire final result matrix, and free the allocated memory
    printFinal(numRows, r_ptr);
    free(r_ptr);

    return 0;

}