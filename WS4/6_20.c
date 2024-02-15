/*Author: Anusri Chavali
Date: 9/19/2023
Purpose: Define a function to convert laps into miles and use it to convert user input laps into miles*/
#include <stdio.h>

/* Function takes innnn a double input called laps and multiplies by 0.25 to return the miles conversion of the double laps */ 
double LapsToMiles(double laps)
{
   double m = laps * 0.25; 
   return m;
}

/*Scans in user input amount of laps and calls LapsToMiles to print the number of miles the laps are equal to*/
int main(void) {

   /* Type your code here. Your code must call the function.  */
   double numLaps;
   scanf("%lf", &numLaps);
   printf("%0.2lf\n", LapsToMiles(numLaps));

   return 0;
}