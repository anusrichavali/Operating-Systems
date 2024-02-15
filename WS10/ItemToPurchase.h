#ifndef ITEM_TO_PURCHASE_H
#define ITEM_TO_PURCHASE_H

/* the structure is defined with three variables*/
struct ItemToPurchase
{
    char itemName[100];
    int itemPrice;
    int itemQuantity;
};

//the functions to make item blank and print item are declared but not defined
void MakeItemBlank(struct ItemToPurchase *item);

void PrintItemCost(const struct ItemToPurchase item);

#endif