/* Author: Anusri Chavali
Date Last Modified: 9/9/2023
Purpose: This program reads values into matrices from file inputs and returns the result of (A*W) + B
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Main function takes 4 arguments (argc = 4), the program call followed by 3 file paths*/
/*Assumptions: the user will input 3 files which will have non-negative integers and each row is separated by newline*/
/*Steps: first intializes 3 arrays of fixed dimensions, next reads values from files into each array, finally calculates A * W + B*/
int main(int argc, char* argv[])
{
    /*Initialize variables to store each filename to print at the end*/
    /*Initializing 3 arrays, A, W, and B, all of which have fixed dimensions */
    char *Aname, *Wname, *Bname;
    int A[3] = {0, 0, 0};
    int W[3][5]; 
    int B[5] = {0, 0, 0, 0, 0};
    /*Since W is a 2d array, it is more efficient to loop through each row and column and populate it with 0s*/
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 5; j++)
        {
            W[i][j] = 0;
        }
    }

    /*If 4 arguments are not provided (first being the script name), then it will exit with code 1
    Assumptions: at this stage, assume the 3 inputs are valid files */
    if(argc != 4)
    {
        int exitcode = 1;
        fprintf(stderr, "error: expecting exactly 3 files as input\nTerminating, exit code %d.\n", exitcode);
        exit(1);
    }

    /* This for loop reads in each file and puts it into the appropriate array
    Assumption: the user is entering the files in the order they want them read, that is A first, W second, B third*/
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

        /* Reads the first file and assigns the values into A
        Only the first row of integers is read into the array */
        if(i == 1)
        {
            /*set Aname to the filename */
            Aname = filename;

            /*A is 1-dimensional; single for loop to read in */
            for(int c = 0; c < 3; c++)
            {
                fscanf(file, "%d", &A[c]);

            }
        }
        
        /*Reads the second file and assigns the values into W
        W is 2D, so I use a character array called buffer which gets updated in each for loop to get a new line 
        The values in the buffer are scanned and added into an external int array
        Those values are then added into W, so that the values are properly stored as integers in the W */
        if(i == 2)
        {
            Wname = filename;

            char buffer[1024];
            int v[5];
            /* for loop iterates through 3 lines of W*/
            for(int r = 0; r < 3; r++)
            {
                fgets(buffer, sizeof(buffer), file);
                /* if statement to remove newlines in buffer line */
                if(buffer[strlen(buffer) - 1] == '\n')
                {
                    buffer[strlen(buffer) - 1] = '\0';
                }

                /*Load file values into temporary array for proper value conversions into integer format*/
                sscanf(buffer, "%d %d %d %d %d", &v[0], &v[1], &v[2], &v[3], &v[4]);
                
                /*for loop to add five values from each row into the current row of W*/
                for(int c = 0; c < 5; c++)
                {
                    W[r][c] = v[c];
                    v[c] = 0;
                }

            }
        }
        
        /* Reads file into array B 
        Only first row of integers is read into the array */
        if(i == 3)
        {
            Bname = filename;

            /*B is 1-dimensional, want to read in one row of file & 1 for loop is enough*/
            for(int c = 0; c < 5; c++)
            {
                fscanf(file, "%d", &B[c]);
            }
        }

        /* Close each file after reading is complete */
        fclose(file);
    }

    /* Function calculates the product of A and W by multiplying each value in A by the corresponding row value in each column of W
    Then adds B values to the A*W product matrix and stores all the values in array r*/
    int r[5];
    for(int j = 0; j < 5; j++)
    {
        for(int k = 0; k < 3; k++)
        {
            int a = A[k];
            int w = W[k][j];
            r[j] += a * w;
        }

        r[j] += B[j];
    }

    /*Prints result in appropriate format using the names stored earlier in the for loop*/
    printf("Result of %s * %s + %s = { %d %d %d %d %d }\n", Aname, Wname, Bname, r[0], r[1], r[2], r[3], r[4]);

    return 0;

}

