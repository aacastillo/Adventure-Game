#include "items.h"

struct Room {
   char* name;
   char* description;
   struct Item* roomInventoryHead;
   int use;
   int rowLoc;
   int columnLoc;
};

//creates a new room dynamically. sets used automatically to 0 and roomInventoryHead to NULL. This will be reassigned in main.
struct Room* newRoom(char* name, char* description);

//getter methods
char* getRoomName(struct Room* room);
char* getRoomDescription(struct Room* room);
struct Item* getRoomInventoryHead(struct Room* room);
int getRoomUse(struct Room* room);
