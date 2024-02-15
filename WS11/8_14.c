//Author: Anusri Chavali
//Date Modified: 11/19/2023
//Purpose: Creates a linked list of a struct called ContactNode, in which names and phone numbers of 3 people are stored
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//define the ContactNode structure with specified properties
typedef struct ContactNode_struct {
   /* Define ContactNode struct here. */
   char contactName[100];
   char contactPhoneNumber[100];
   struct ContactNode_struct *nextNodePtr;
} ContactNode;

//intiialize a contactNode object with the provided parameters
void InitializeContactNode(ContactNode *c, char cName[100], char cPN[100])
{
   strcpy(c->contactName, cName);
   strcpy(c->contactPhoneNumber, cPN);
}

//access the name of a contact node object
char *GetName(ContactNode *c)
{
   return c->contactName;
}

//access the phone number of a contact node object
char *GetPhoneNumber(ContactNode *c)
{
   return c->contactPhoneNumber;
}

//insert a new contact node after the current one
void InsertAfter(ContactNode *current, ContactNode* next)
{
   current->nextNodePtr = next;
}

//return the next node using the pointer from the current node
ContactNode* GetNext(ContactNode *current)
{
   return current->nextNodePtr;
}

//print the properties of the contact node
void PrintContactNode(ContactNode *current)
{
   printf("Name: %s\n", current->contactName);
   printf("Phone number: %s\n", current->contactPhoneNumber);
}

   
/* in the main, scan 3 sets of inputs from stdin and assign them to contactNodes
print the information of all three contact nodes*/

int main(void) {
   /* initialize start and end nodes of the linked lists */
   ContactNode* start = NULL;
   ContactNode* end = NULL;
   
   //scan in relevant information 3 times
   for(int i = 0; i < 3; i++)
   {

      char name[100], phoneNumber[100];
      fgets(name, sizeof(name), stdin);
      name[strlen(name) - 1] = '\0';
      fgets(phoneNumber, sizeof(phoneNumber), stdin);
      phoneNumber[strlen(phoneNumber) - 1] = '\0';
      
      printf("Person %d: %s, %s\n", i + 1, name, phoneNumber);
      
      //create a new node and malloc it beccause there is no fixed amount of memory we need for contactNode
      //use one of the defined functions to initialize the node
      ContactNode *current = (ContactNode *) malloc(sizeof(ContactNode));
      InitializeContactNode(current, name, phoneNumber);
      
      //if the start is empty, make this current node the start of the linked list
      if(start == NULL)
      {
         start = current;
      }
      
      //if the end is not empty, then insert this node after the last node
      if(end != NULL)
      {
         InsertAfter(end, current);
      }
      
      //assign the current node to the end, since it is the last of the nodes so far
      end = current;
   }
   
   //use a while loop to iterate through the linked list using the next pointer 
   printf("\nCONTACT LIST\n");
   ContactNode *current = start;
   while(current != NULL)
   {
      PrintContactNode(current);
      printf("\n");
      current = GetNext(current);
   }
   
   return 0;
}
