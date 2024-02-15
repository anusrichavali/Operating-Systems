#include<stdio.h>
#include<string.h>

#include "ItemToPurchase.h";

/* the make item blank function sets each variable of the pointer to the respective blank value*/
void MakeItemBlank(struct ItemToPurchase *item)
{
    char blank[] = "none";
    strcpy(item->itemName, blank);
    item->itemPrice = 0;
    item->itemQuantity = 0;
}

//the print item cost function prints the values of the different ItemToPurchase variables
void PrintItemCost(const struct ItemToPurchase item)
{
    printf("%s %d @ $%d = $%d\n", item.itemName, item.itemQuantity, item.itemPrice, item.itemQuantity * item.itemPrice);
}
