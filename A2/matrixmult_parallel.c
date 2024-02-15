/* Author: Anusri Chavali
Date Last Modified: 9/24/2023
Purpose: This program reads values into matrices from file inputs and returns the result of (A*W) + B
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/time.h>

#define ROWS 8
#define COLS 8
/*the multiplMatrix function takes in rows, cols, the current A row and W matrix, and the matrix to store the results in*/
/*The dot product of each row times the column of W is calculated and stored in the result matrix*/
void multiplyMatrix(int r, int c, int A[c], int W[r][c], int R[c])
{
    for(int r= 0; r < ROWS; r++)
    {
        for(int c = 0; c < COLS; c++)
        {
            int a = A[c];
            int w = W[c][r];
            R[r] += a * w;
        }

    }
}

/*Main function takes 4 arguments (argc = 4), the program call followed by 3 file paths*/
/*Assumptions: the user will input 3 files which will have non-negative integers and each row is separated by newline*/
/*Steps: first intializes 3 arrays of fixed dimensions, next reads values from files into each array, finally calculates A * W + B*/
int main(int argc, char* argv[])
{
    /*initiate values to calculate runtime*/
    struct timeval start_time, end_time;
    double runtime;

    /*record start time*/
    gettimeofday(&start_time, NULL);

    /*Initialize variables to store each filename to print at the end*/
    /*Initializing 2 Arrays, A and W, with fixed dimensions*/
    char *Aname, *Wname;
    int A[ROWS][COLS];
    int W[ROWS][COLS];
    int R[ROWS][COLS];
    for(int i = 0; i < ROWS; i++)
    {
        for(int j = 0; j < COLS; j++)
        {
            A[i][j] = 0;
            W[i][j] = 0;
            R[i][j] = 0;
        }
    }

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
        FILE *file = fopen(argv[i], "r");
        char *filename = argv[i];

        /*This if statement checks each file, and if the file can not be opened, prints error message and exits with code 1*/
        if(file == NULL)
        {   
            int exitcode = 1;
            fprintf(stderr, "error: cannot open file %s \nTerminating, exit code %d.\n", filename, exitcode);
            exit(1);
        }

        char buffer[1024];
        int v[8] = {0, 0, 0, 0, 0, 0, 0, 0};
        /* Reads the first file and assigns the values into A
        Only the first row of integers is read into the array */
        if(i == 1)
        {
            /*set Aname to the filename */
            Aname = filename;

            /*A is 1-dimensional; single for loop to read in */
            for(int r = 0; r < ROWS; r++)
            {
                fgets(buffer, sizeof(buffer), file);
                /* if statement to remove newlines in buffer line */
                if(buffer[strlen(buffer) - 1] == '\n')
                {
                    buffer[strlen(buffer) - 1] = '\0';
                }

                sscanf(buffer, "%d %d %d %d %d %d %d %d", &v[0], &v[1], &v[2], &v[3], &v[4], &v[5], &v[6], &v[7]);
                
                /*for loop to add five values from each row into the current row of W*/
                for(int c = 0; c < COLS; c++)
                {
                    A[r][c] = v[c];
                    v[c] = 0;
                }
            }
        }
        else
        {
            Wname = filename;

            /* for loop iterates through 3 lines of W*/
            for(int r = 0; r < ROWS; r++)
            {
                fgets(buffer, sizeof(buffer), file);
                /* if statement to remove newlines in buffer line */
                if(buffer[strlen(buffer) - 1] == '\n')
                {
                    buffer[strlen(buffer) - 1] = '\0';
                }

                /*Load file values into temporary array for proper value conversions into integer format*/
                sscanf(buffer, "%d %d %d %d %d %d %d %d", &v[0], &v[1], &v[2], &v[3], &v[4], &v[5], &v[6], &v[7]);
                
                /*for loop to add eight values from each row into the current row of W*/
                for(int c = 0; c < COLS; c++)
                {
                    W[r][c] = v[c];
                    v[c] = 0;
                }

            }

            /* Close each file after reading is complete */
            fclose(file);
        }
    }

    /*initialize temporary arrays to store the computation of each row's dot product and an array of pipes, one pipe per child */
    int r[ROWS] = {0, 0, 0, 0, 0, 0, 0, 0};
    int pipes[ROWS][2];
    __pid_t pids[ROWS];

    /*this for loop creates 8 separate child processes, one to process the dot product for each row of A*/
    for(int i = 0; i < ROWS; i++)
    {
        /*each value of the pipes array is initialized as the pipe for the current process
        if the pipe fails, then error printed */
        if(pipe(pipes[i]) == -1)
        {
            perror("pipe");
            exit(1);
        }

        /*fork the process*/
        pids[i] = fork();
        
        /*if fork fails, print error */
        /*if fork is successful, the multiplyMatrix function is called for the ith row of A and W, and then loaded into r*/
        if(pids[i] < 0)
        {
            perror("Fork failed");
            exit(1);
        }
        else if(pids[i] == 0)
        {
            close(pipes[i][0]);
            multiplyMatrix(8, 8, A[i], W, r);
            write(pipes[i][1], r, sizeof(r));
            close(pipes[i][1]);
            exit(0);
        } 
    }

    int status;
    int pid_finished;
    int index;
    /*the parent function waits for any of the child functions to finish and determines the index of the child process that ended by using the pid arrays
    //that index becomes the index the program refers to when retrieving the appropriate pipe
    //the program retrieves the individual row arrays from each pipe
    The individual arrays are read into the next row of R
    Pipes are closed after reading and writing*/
    while((pid_finished = wait(&status)) > -1)
    {
        //get the index by iterating through pids to see which matches the pid of the finished child
        for(int i = 0; i < ROWS; i++)
        {
            if(pids[i] == pid_finished)
            {
                index = i;
                break;
            }
        }

        close(pipes[index][1]);
        int received[8] = {0, 0, 0, 0, 0, 0, 0, 0};
        read(pipes[index][0], received, sizeof(received));
        for(int j = 0; j < COLS; j++)
        {
            R[index][j] = received[j];
        }
        close(pipes[index][0]);

    }


    /*The result of the computation of A * W is printed out */
    printf("Result of %s * %s = [\n", Aname, Wname);
    for(int i = 0; i < ROWS; i++)
    {
        for(int j = 0; j < COLS; j++)
        {
            printf("%d ", R[i][j]);
        }
        printf("\n");
    }

    printf("]\n");

    /*Get end time of the process*/
    gettimeofday(&end_time, NULL);

    /*get the runtime*/
    runtime = ((double)(end_time.tv_sec - start_time.tv_sec) + (double)(end_time.tv_usec - start_time.tv_usec))/1000000.0;

    /*print the runtime*/
    printf("Runtime %0.2lf seconds\n", runtime);
    return 0;

}