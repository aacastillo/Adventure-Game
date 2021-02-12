#include "rooms.h"

//creates a new room dynamically. sets used automatically to 0 and roomInventory automatically to NULL
struct Room* newRoom(char* name, char* description) {
   struct Room* newRoom = NULL;
   newRoom = (struct Room*) malloc(sizeof(struct Room));
   if (newRoom == NULL) {
      printf("Malloc has failed and return NULL\n");
      return NULL;
   }

   newRoom->name = name;
   newRoom->description = description;
   newRoom->roomInventoryHead = newItem("roomInventoryHead", "Head of room Invetory");
   newRoom->use = 0;
   newRoom->rowLoc = 0;
   newRoom->columnLoc = 0;
   return newRoom;
}

//getter methods
char* getRoomName(struct Room* room) {
   return room->name;
}

char* getRoomDescription(struct Room* room) {
   return room->description;
}

struct Item* getRoomInventoryHead(struct Room* room) {
   return room->roomInventoryHead;
}

int getRoomUse(struct Room* room) {
   return room->use;
}

