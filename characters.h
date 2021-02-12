#include "rooms.h"

struct Character {
   char* name;
   struct Room* location;
   struct Item* inventoryHead;
};

//dynamically creates a new character. Automatically sets Room Location and InventoryHead to NULL
struct Character* newCharacter (char* name);

//moves character to new location
void movecharacter(struct Character* character, struct Room* newLocation);
	//character->location = newLocation

//getter methods
char* getCharacterName(struct Character* character);
struct Room* getCharacterLocation(struct Character* character);
struct Item* getCharacterInventoryHead(struct Character* character);
