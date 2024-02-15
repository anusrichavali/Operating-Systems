///Author: Anusri Chavali
//Date: 11/5/2023
//Purpose: Reads in user input strings separated by a comma, and then parses the stringa based on the comma
#include<stdio.h>
#include <string.h>

//function to make the whole input string null
void null(char input[1024])
{
    for(int i = 0; i < strlen(input); i++)
    {
        input[i] = '\0';
    }
}

//function to parse through the strings
void parse(char input[1024])
{
    //stores the token pointers in an array, and parses input using the comma as delimiter
    char *tokens[2];
    int count = 0;
    char *token = strtok(input, ",");
    //stores all tokens in the array
    while(token != NULL)
    {
        tokens[count] = token;
        count++;
        token = strtok(NULL, ",");
    }

    //prints the words for the token pointers
    printf("First word: %s\n", tokens[0]);
    printf("Second word: %s\n", tokens[1]);
}

//keeps taking in stdin strings, checking if they have a comma, and parsing the strings until the user enters q
int main(void) {

   //input array is nulled out
   char input[1024];
   null(input);
   int k = 0;
   printf("Enter input string: \n");
   //the while loop keeps taking in strings until the user enters q
   //in the while loop, the string is checked for a comma and then is parsed if it has a comma
   while(fgets(input, sizeof(input), stdin) != NULL)
   {
        if(input[0] == 'q')
        {
            k = 2;
        }

        for(int i = 0; i < strlen(input); i++)
        {
            if(input[i] == ',')
            {
                k = 1;
                break;
            }
        }

        //based on the input integer, the string is rejected, accepted and parsed, or ends the program
        if(k == 0)
        {
            printf("Error: No comma in string\n");
            printf("\n");
            printf("Enter input string:\n");
        }
        else if(k == 1)
        {
            parse(input);
            printf("\n");
            printf("Enter input string:\n");
        }
        else
        {
            break;
        }

    }

    return 0;
}