#include "characters.h"

//dynamically creates a new character. Automatically sets Room Location and InventoryHead to NULL
struct Character* newCharacter (char* name1) {
   struct Character* newCharacter = NULL;
   newCharacter = (struct Character*) malloc(sizeof(struct Character));
   if (newCharacter == NULL) {
      printf("malloc has failed and return NULL\n");
      return NULL;
   }

   newCharacter->name = name1;
   newCharacter->location = NULL;
   newCharacter->inventoryHead = newItem("InventoryHead", "Head of player inventory");
   
   return newCharacter;
}

//moves character to new location
void moveCharacter(struct Character* character, struct Room* newLocation) {
   character->location = newLocation;
}

//getter methods
char* getCharacterName(struct Character* character){
   return character->name;
}

struct Room* getCharacterLocation(struct Character* character) {
   return character->location;
}

struct Item* getCharacterInventoryHead(struct Character* character) {
   return character->inventoryHead;
}
