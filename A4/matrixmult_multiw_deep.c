//Author: Anusri Chavali
//Date: 10/31/2023
//Purpose: Use exec in order to run take as many lines of input as user wants
//Each line of input contains filenames, and those files are each sent in parallel processes to matrixmult_parallel

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

#define ROWS 8
#define COLS 8
#define SIZE 4
#define MIN 3
#define LENGTH 35

//Takes a file and reads it into a matrix
//Used to read the results in from file
void readFromFile(char outName[LENGTH], FILE *f, int matrix[ROWS][COLS])
{
    char buffer[1024];
    int v[ROWS];
    f = fopen(outName, "r+");
    while(fgets(buffer, sizeof(buffer), f) != NULL)
    {
        /* if statement to remove newlines in buffer line */
        if(buffer[strlen(buffer) - 1] == '\n')
        {
            buffer[strlen(buffer) - 1] = '\0';
        }

        sscanf(buffer, "%d %d %d %d %d %d %d %d", &v[0], &v[1], &v[2], &v[3], &v[4], &v[5], &v[6], &v[7]);
        
        /*for loop to add five values from each row into the current row of W*/
        for(int r = 0; r < ROWS; r++)
        {
            for(int c = 0; c < COLS; c++)
            {
                matrix[r][c] += v[c];
                v[c] = 0;
            }
        }
    }
    fclose(f);
}

//Prints a matrix out to stdout
void printFinal(int matrix[ROWS][COLS])
{
    printf("Rsum = [\n");
    for(int i = 0; i < ROWS; i++)
    {
        for(int j = 0; j < COLS; j++)
        {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("]\n");
}

//zeros out matrices of a fixed size
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


//function which takes in a matrix and prints it to a file
//used to print to RSUM.txt
void printToFile(int matrix[ROWS][COLS])
{
    FILE* f = fopen("RSUM.txt", "w");
    for(int r = 0; r < ROWS; r++)
    {
        for(int c = 0; c < COLS; c++)
        {
            fprintf(f, "%d ", matrix[r][c]);
        }
        fprintf(f, "\n");
    }
    fclose(f);
}

//the main function takes an argv of the executable name and the files for the matrices which will be multiplied
int main(int argc, char *argv[])
{

    //a new array is created which has the executable for exec, the matrix A, and ends with null
    char *myargs[SIZE];
    myargs[0] = "./matrixmult_parallel";
    myargs[1] = argv[1];
    myargs[3] = NULL;
    //initialize matrix to store pids for later reference in parent
    pid_t pids[argc - 2];
    //initalize arrays for pipes which will allow parent to write into child's output in stdout and stderr
    int fd[argc - 2][2], fd2[argc - 2][2];
    FILE *file;
    //initalize strings for filenames
    char outName[LENGTH], errName[LENGTH];
    //initialize and zero the Rsum matrix which stores Rsum
    int Rsum[ROWS][COLS];
    zero(Rsum);

    //prints error if not enough arguments gives
    if(argc < MIN)
    {
        fprintf(stderr, "Needs at least 1 input for W matrix\n");
        exit(1);
    }

    //first loop is used for the first line, in order to generate the first Rsum
    //for loop creates child processes for every W file entered
    for(int i = 1; i < argc - 1; i++)
    {
        //creates a pipe for fd, where information from child process will be printed in read end
        if(pipe(fd[i - 1]) == -1)
        {
            perror("pipe error");
            exit(1);
        }
        //child id is stored in the pids array
        pids[i - 1] = fork();
        //print error if fork failed
        if(pids[i - 1] < 0)
        {
            fprintf(stderr, "fork failed\n");
            exit(1);
        }
        //if fork successful
        else if(pids[i - 1] == 0) {
            //use sprintf to add integer value(pids) to filenames
            snprintf(outName, sizeof(outName), "%d.out", getpid());
            snprintf(errName, sizeof(errName), "%d.err", getpid());

            //open the out and err file for the current process and use flags to read, write, and give permission to all
            fd[i - 1][1] = open(outName, O_RDWR | O_CREAT | O_APPEND, 0777);
            fd2[i - 1][1] = open(errName, O_RDWR | O_CREAT | O_APPEND, 0777);

            //print relevant errors if any of the files can't be opened
            if(fd[i - 1][1] == -1)
            {
                fprintf(stderr, "can't open out file");
                exit(1);
            }

            if(fd2[i - 1][1] == -1)
            {
                fprintf(stderr, "can't open err file");
                exit(1);
            }

            //use dup2 to connect the child's out and err files to the respective file descriptors they should read from
            dup2(fd[i - 1][1], 1);
            dup2(fd2[i - 1][1], 2);

            //close the writing end of the files
            close(fd[i - 1][1]);
            close(fd2[i - 1][1]);

            //initalize the W parameter to the input Wi and call exec on the current version of myargs
            myargs[2] = argv[i + 1];
            execvp(myargs[0], myargs);
            perror("execvp");
            exit(127);
        }
    }

    //parent process
    //waits for any child to end
    //parent process reads each process output array and adds into Rsum
    //after all the child processes are completed, Rsum is printed into the file and zeroed to store the next sum
    int pid_finished;
    int status;
    while((pid_finished = wait(&status)) > -1)
    {
        //the out and err files for the just ended child are filled again and opened
        snprintf(outName, sizeof(outName), "%d.out", pid_finished);

        //open the out and err file for the current process and use flags to read, write, and give permission to all
        readFromFile(outName, file, Rsum);
        
        fflush(stdout);
        fflush(stdin);
    }
    printToFile(Rsum);
    zero(Rsum);

    //the next while loop is used to keep reading in lines of input from stdin
    //after all tokens of the line are parsed, a for loop execs to matrixmult_parallel 
    //the inputs for exec are the RSUM file which stores previous RSUM, and the current token (file) to be multiplied to RSUM
    char input[256];
    char *tokens[256];
    int count = 0; 
    while(fgets(input, sizeof(input), stdin) != NULL)
    {
        if(input[strlen(input) - 1] == '\n')
        {
            input[strlen(input) - 1] = '\0';
        }
        myargs[1] = "RSUM.txt";

        //for each input line, a nested while loop with strtok is used to separate the different filepaths and they are all stored in an array
        char *token = strtok(input, " ");
        while(token != NULL)
        {
            tokens[count] = token;
            count++;
            token = strtok(NULL, " ");
        }

        //these arrays are the pipes for the process, and store the pids of each process
        int p[count][2], perr[count][2];
        pid_t pids_2[count];

        //after all tokens of the line are parsed, a for loop execs to matrixmult_parallel 
        //the inputs for exec are the RSUM file which stores previous RSUM, and the current token (file) to be multiplied to RSUM
        for(int i = 0; i < count; i++)
        {
            myargs[2] = tokens[i];
            pids_2[i] = fork();
            if(pipe(p[i]) == -1)
            {
                perror("pipe error");
                exit(1);
            }

            if(pids_2[i] < 0)
            {
                perror("fork");
                exit(1);
            }
            else if(pids_2[i] == 0)
            {
                //use sprintf to add integer value(pids) to filenames
                snprintf(outName, sizeof(outName), "%d.out", getpid());
                snprintf(errName, sizeof(errName), "%d.err", getpid());

                //open the out and err file for the current process and use flags to read, write, and give permission to all
                p[i][1] = open(outName, O_RDWR | O_CREAT | O_APPEND, 0777);
                perr[i][1] = open(errName, O_RDWR | O_CREAT | O_APPEND, 0777);

                //print relevant errors if any of the files can't be opened
                if(p[i][1] == -1)
                {
                    fprintf(stderr, "can't open out file");
                    exit(1);
                }

                if(perr[i][1] == -1)
                {
                    fprintf(stderr, "can't open err file");
                    exit(1);
                }

                //use dup2 to connect the child's out and err files to the respective file descriptors they should read from
                dup2(p[i][1], 1);
                dup2(perr[i][1], 2);

                //close the writing end of the files
                close(p[i][1]);
                close(perr[i][1]);

                //initalize the W parameter to the input Wi and call exec on the current version of myargs
                execvp(myargs[0], myargs);
                perror("execvp");
                exit(0);
            }
        }

        //parent process retrieves the result from each child, and uses readFromFile to add the values to Rsum
        while((pid_finished = wait(&status)) > -1)
        {
            //the out and err files for the just ended child are filled again and opened
            snprintf(outName, sizeof(outName), "%d.out", pid_finished);

            //open the out and err file for the current process and use flags to read, write, and give permission to all
            readFromFile(outName, file, Rsum);
        
        }

        //any excess whitespaces are flushed from stdin
        //count is set to 0 to write over the previous line's tokens
        fflush(stdin);
        count = 0;

        //the current version of Rsum is written to the file, and Rsum is zeroed to store the next line's sum
        printToFile(Rsum);
        zero(Rsum);
    }

    //after the user exits by doing ctrl+D, the final version of Rsum is read into the zeroed array, and Rsum is printed
    readFromFile(myargs[1], file, Rsum);
    printFinal(Rsum);


    return 0;
}