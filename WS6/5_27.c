//Author: Anusri Chavali
//Date: 10/03/2023
//Purpose: Return the revrese of user input strings
#include <stdio.h>
#include <string.h>

//program keeps running while there is input
int main(void) {
   while(1)
   {
      /* Read in string. */
      char str[50];
      fgets(str, 50, stdin);
      
      //print out the string if a done string is not provided
      if(strcmp(str, "Done\n") != 0 && strcmp(str, "done\n") != 0 && strcmp(str, "d\n") != 0)
      {
         for(int i = strlen(str) - 2; i >= 0; i--)
         {
            printf("%c", str[i]);
         }
         printf("\n");
      }
      //if the string is Done, done, or d, then break from the whole loop
      else
      {
         break;
      }
      
   }
   
   return 0;
}