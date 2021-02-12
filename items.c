#include "items.h"

//this function dynamically creates a new item, set next item automatically to Null.
struct Item* newItem(char* name, char* description) {
   struct Item* newItem = NULL;
   newItem = (struct Item*) malloc(sizeof(struct Item));
   if (newItem == NULL) {
      printf("malloc has failed and returned NULL\n");
      return NULL;
   }

   newItem->name = name;
   newItem->description = description;
   newItem->next = NULL;
   newItem->traverseResult = NULL;
   
   return newItem;
}

//this is a helper function that takes the itemName and searches
//it in the linked list TOI, where TOI is the type of 
//inventory (player's or room's).
//it returns the item if it is found otherwise returns Null

struct Item* searchItem(char* itemName, struct Item* TOIHead) {
   TOIHead->traverseResult = (struct Item*) malloc(sizeof(struct Item));
   while(TOIHead->next != NULL) {
      if (strcmp(TOIHead->next->name, itemName) == 0) {
	 TOIHead->traverseResult = TOIHead->next;
         TOIHead->next = TOIHead->next->next;
         return TOIHead->traverseResult;
      } else {
         TOIHead = TOIHead->next;
      }
   }
   return NULL;
}

//This is a helper function that takes the result from searchItem()
//If the result is not null then it will store the result at the
//end of the TOI, where TOI is the type of inventory (room's or player's).
void moveItem(struct Item* result, struct Item* TOIHead) {
  if (result == NULL) {
     printf("Item was not found\n");
  } else {
     struct Item* temp = (struct Item*) malloc(sizeof(struct Item));
     temp = TOIHead;
     while(temp != NULL) {
        if (temp->next == NULL) {
           temp->next = result;
	   temp = NULL;
	   free(temp);
	   break;
        } else {
 	   temp = temp->next;
        }
     }
  }
}

//takes item from roomInventory and puts in player's inventory
void takeItem(char* itemName, struct Item* roomInventoryHead, struct Item* playerInventoryHead) {
  struct Item* result = (struct Item*) malloc(sizeof(struct Item));
  result =  searchItem(itemName, roomInventoryHead);
  moveItem(result, playerInventoryHead);
  if (result != NULL) {
     printf("The %s has been added to your inventory\n", itemName);
  }
  result = NULL;
  free(result);
}

//takes item from player's inventory and puts in room inventory
void dropItem(char* itemName, struct Item* roomInventoryHead, struct Item* playerInventoryHead) {
   struct Item* result = (struct Item*) malloc(sizeof(struct Item));
   result = searchItem(itemName, playerInventoryHead);
   moveItem(result, roomInventoryHead);
   if (result != NULL) {
      printf("The %s has been dropped in the room\n", itemName);
   }
   result = NULL;
   free(result);
}

//getter methods
char* getItemName(struct Item* item) {
   return item->name;
} 

char* getItemDescription(struct Item* item) {
   return item->description;
}

struct Item* getItemNext(struct Item* item) {
   return item->next;
}
