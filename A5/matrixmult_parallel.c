/* Author: Anusri Chavali
Date Last Modified: 11/19/2023
Purpose: This program reads values into matrices from file inputs and returns a result matrix contianing the product of several different A matrices and one W matrix. 
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

//the zero function zeros out an 8 by 8 matrix
void zero(int m[ROWS][COLS])
{
    for(int r = 0; r < ROWS; r++)
    {
        for(int c = 0; c < COLS; c++)
        {
            m[r][c] = 0;
        }
    }
}

//the printFinal function takes the pointer of a dynamic array and prints out the values based on the number of rows in the array
void printFinal(int numRows, int* ptr)
{
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
}

//the addToMatrix takes in the tow index, a temporary array, and pointer of the dynamic array to add the values into
void addToMatrix(int index, int r[COLS], int* ptr)
{
    for(int j = 0; j < COLS; j++)
    {
        ptr[index * COLS + j] = r[j];
    }
}

//the setR function sets a dynamic array and zeros it out
void setR(int index, int* ptr)
{
    for(int i = index; i < ROWS * COLS; i++)
    {
        ptr[i] = 0;
    }
}

/*Main function takes 4 arguments (argc = 4), the program call followed by 3 file paths*/
/*Assumptions: the user will input 3 files which will have non-negative integers and each row is separated by newline*/
/*Steps: first intializes 3 arrays of fixed dimensions, next reads values from files into each array, finally calculates A * W + B*/
int main(int argc, char* argv[])
{

    /*Initialize variables to store each filename to print at the end*/
    /*Initializing 2 Arrays, A and W, with fixed dimensions*/
    //initalizing the dynamic result array which start off as 8 by 8
    //the int vakue starting determines the row to start from when adding values -- becomes more useful as we get more commands from stdin
    //file pointer used for readFromFile function
    char *Aname, *Wname;
    int A[ROWS][COLS], W[ROWS][COLS];
    int* r_ptr = malloc((ROWS*COLS) * sizeof(int));
    int starting = 0;
    setR(0, r_ptr);
    FILE *file;
    zero(A);
    zero(W);

    //returns error if enough files not provided
    if(argc != 3)
    {
        int exitcode = 1;
        fprintf(stderr, "error: expecting exactly 2 files as input\nTerminating, exit code %d.\n", exitcode);
        exit(1);
    }
    
    //reads in A and W matrices
    for(int i = 1; i < argc; i++)
    {
        /* Initializing a FILE variable which will open each file in argv to read it
        Also initalizing the filename, and setting up characters which will allow us to modify the filename to print appropriate messages*/
        char *filename = argv[i];

        /* Reads the first file and assigns the values into A */
        if(i == 1)
        {
            readFromFile(filename, file, A);
        }
        //reads the second file and assigns the values into W
        else
        {
            readFromFile(filename, file, W);
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
    Pipes are closed after reading and writing
    A is zeroed out since it needs to be reset for next iteration of process */
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
        int received[COLS] = {0, 0, 0, 0, 0, 0, 0, 0};
        read(pipes[index][0], received, sizeof(received));
        addToMatrix(index, received, r_ptr);
        close(pipes[index][0]);
        zero(A);
    }
    //print the set of files that were multiplied
    printf("%s x %s\n", argv[1], argv[2]);

    //numRows is used to keep track of how many rows to put in the array -- 8 more are added after another filename is passed through the pipe
    size_t numRows = ROWS;
    char input[256] = {'\0'};
    //filename input is read in from stdin -- the stdin values are passed in from the pipe set up in parent process
    while(read(STDIN_FILENO, &input, sizeof(input)) > 0)
    {
        //flush stdin and stdout to clear any leftover characters
        fflush(stdin);
        fflush(stdout);

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

        //read from the file specified by input into zeroed out A matrix
        readFromFile(input, file, A);
        //numRows and starting are incremented by 8 (numRows is last row, starting is first row of newly added portion of result)
        numRows += ROWS;
        starting += ROWS;
        //new set of pids and pipes initialized, since the first is populated
        pid_t pids2[ROWS];
        int pipes2[ROWS][2];
        //reallocate the result matrix with the new amount of rows, and set all the new rows to 0
        r_ptr = realloc(r_ptr, (numRows * COLS) * sizeof(int));
        setR(starting, r_ptr);


        //iterate through the rows of A and W and assign the products to relevant row of result
        for(int i = 0; i < ROWS; i++)
        {
            /*each value of the pipes array is initialized as the pipe for the current process
            if the pipe fails, then error printed */
            if(pipe(pipes2[i]) == -1)
            {
                perror("pipe");
                exit(1);
            }

            /*fork the process*/
            pids2[i] = fork();
            
            /*if fork fails, print error */
            /*if fork is successful, the multiplyMatrix function is called for the ith row of A and W, and then loaded into r*/
            if(pids2[i] < 0)
            {
                perror("Fork failed");
                exit(1);
            }
            else if(pids2[i] == 0)
            {
                close(pipes2[i][0]);
                multiplyMatrix(8, 8, A[i], W, r);
                write(pipes2[i][1], r, sizeof(r));
                close(pipes2[i][1]);
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
                if(pids2[i] == pid_finished)
                {
                    index = i;
                    break;
                }
            }

            close(pipes2[index][1]);
            int received[COLS] = {0, 0, 0, 0, 0, 0, 0, 0};
            read(pipes2[index][0], received, sizeof(received));
            addToMatrix(starting + index, received, r_ptr);
            close(pipes[index][0]);
            zero(A);
        }
        //print the set of files that were multiplied
        printf("%s x %s\n", input, argv[2]);
        input[0] = '\0';

    }

    //after input stream has ended, print all the rows of result matrix
    printFinal(numRows, r_ptr);

    //free the allocated memory
    free(r_ptr);

    /*print the runtime*/
    //printf("Finished child %d of parent %d\n", getpid(), getppid());
    return 0;

}