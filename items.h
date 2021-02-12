#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef CH_HEAD
#define CH_HEAD

struct Item { 
  char* name;
  char* description;
  struct Item* next;
  struct Item* traverseResult;
};

//this function dynamically creates a new item. Automatically sets next pointer to NULL
struct Item* newItem(char* name, char* description);

//this is a helper function that takes the itemName and searches
//it in the linked list TOI, where TOI is the type of 
//inventory (player's or room's).
//it returns the item if it is found otherwise returns null.
struct Item* searchItem(char* itemName, struct Item* TOIHead);

//This is a helper function that takes the result from searchItem()
//If the result is not null then it will store the result at the
//end of the TOI, where TOI is the type of inventory (room's or player's).
void moveItem(struct Item* result, struct Item* TOIHead);

//takes item from roomInventory and puts in player's inventory
void takeItem(char* itemName, struct Item* roomInventoryHead, struct Item* playerInventoryHead);
	//searchItem(itemName, roomInventory)
	//moveItem(item*, inventory)

//takes item from player's inventory and puts in room inventory
void dropItem(char* itemName, struct Item* roomInventoryHead, struct Item* playerInventoryHead);
	//searchItem(itemName, inventory)
	//moveItem(item*, roomInvetory)

//getter methods
char* getItemName(struct Item* item);
char* getItemDescription(struct Item* item);
struct Item* getItemNext(struct Item* item);

#endif
