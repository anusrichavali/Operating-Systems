//Author: Anusri Chavali
//Date: 11/13/2023
//Purpose: This program takes 2 inputs for item names, prices and quantities, and prints the total of those items
#include<stdio.h>
#include<string.h>

#include "ItemToPurchase.h"

#define SIZE 2

int main(void) {
 
   /* the variables are used to declare name arrays, characters to flush the stdin, and the array to store the two items in the cart*/  
   char c;
   struct ItemToPurchase items[SIZE];
   char name[100];

   //the for loop iterates through the array
   //it scans the names, prices, and quantities and stores them in the respective item in the array
   for(int i = 0; i < SIZE; i++)
   {
      printf("Item %d\n", i + 1);
      printf("Enter the item name:\n");
      fgets(name, sizeof(name), stdin);
      fflush(stdin);
      name[strlen(name) - 1] = '\0';
      strcpy(items[i].itemName, name);
      printf("Enter the item price:\n");
      scanf("%d", &items[i].itemPrice);
      printf("Enter the item quantity:\n");
      scanf("%d", &items[i].itemQuantity);

      c = getchar();
      while(c != '\n' && c != EOF) {
         c = getchar();
      }
      
      printf("\n");
   }

   //the for loop prints the item information using the function
   //it adds the total price of each item to the value total
   int total = 0;
   printf("TOTAL COST\n");
   for(int i = 0; i < SIZE; i++)
   {
      PrintItemCost(items[i]);
      total += items[i].itemPrice * items[i].itemQuantity;
   }
   
   //total gets printed out
   printf("\n");
   printf("Total: $%d\n", total);
   return 0;
}