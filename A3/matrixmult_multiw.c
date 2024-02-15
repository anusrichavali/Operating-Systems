//Author: Anusri Chavali
//Date: 10/9/2023
//Purpose: Use exec in order to run matrixmult_parallel on A and N number of W matrices; generate output files for stdout and stderr for each exec function
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

#define SIZE 4
#define MIN 3
#define LENGTH 20

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
    //initalize strings for filenames
    char outName[LENGTH], errName[LENGTH];

    if(argc < MIN)
    {
        fprintf(stderr, "Needs at least 1 input for W matrix\n");
        exit(1);
    }

    //for loop creates child processes for every W file entered
    for(int i = 1; i < argc - 1; i++)
    {
        //store the child process id
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

            //write inital message into output
            char s[100];
            snprintf(s, sizeof(s), "Starting command %d: child %d of parent %d\n", i, getpid(), getppid());
            write(fd[i - 1][1], s, strlen(s));

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
    int pid_finished;
    int status;
    while((pid_finished = wait(&status)) > -1)
    {
        //the current pid is found in pids and the index of that value is stored
        int index = 0;
        const int es = WEXITSTATUS(status);
        for(int i = 0; i < sizeof(pids); i++)
        {
            if(pids[i] == pid_finished)
            {
                index = i;
            }
        }

        //the out and err files for the just ended child are filled again and opened
        snprintf(outName, sizeof(outName), "%d.out", pid_finished);
        snprintf(errName, sizeof(errName), "%d.err", pid_finished);

        //the relevant files are opened using the determined index
        fd[index][1] = open(outName, O_RDWR | O_CREAT | O_APPEND, 0777);
        fd2[index][1] = open(errName, O_RDWR | O_CREAT | O_APPEND, 0777);

        //the child process files now read in from parent's stdout and stderr
        dup2(fd[index][1], 1);
        dup2(fd2[index][1], 2);

        //based on success or failure of the child process, relevant messages are printed to relevant files
        if(status == 0)
        {
            fprintf(stdout, "Finished child %d of parent %d\n", pid_finished, getpid());
            fprintf(stdout, "Exited with exitcode = %d\n", es);
        }
        else
        {
            fprintf(stderr, "Killed with signal %d", es);
        }

        //stdout/stderr is flushed to avoid being read into the wrong file
        fflush(stdout);
        fflush(stderr);
        //current child's files closed
        close(fd[index][0]);
        close(fd[index][1]);
        close(fd2[index][0]);
        close(fd2[index][1]);
    }

    return 0;
}