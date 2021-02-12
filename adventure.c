#include "characters.h"
#include <time.h>

void main() {
//more randomization with different seed for rand()
srand(time(NULL));

//Initializations
//Initializing all rooms
   struct Room* Center = newRoom("The Campus Center", "Its buzzing with students, the food from Blue Wall smells good. Over the noise you hear the sound of a piano. You want to eat gelato.");
   struct Room* Garage = newRoom("The Parking Garage", "Theres broken glass all over the ground as if someone had tried to break into a car.");
   struct Room* Library = newRoom("The Library", "The library is full of students on every floor, you look for a quiet room to look at your clues.");
   struct Room* Lederle = newRoom("Lederle", "A tower of rooms for teachers and researchers.");
   struct Room* Hamp = newRoom("Hamp", "One of the more fancy dining halls, you grab some stir fry and sushi.");
   struct Room* Pond = newRoom("The Campus Pond", "Alongside the pond the geese laughing");
   struct Room* FAC = newRoom("The Fine Arts Center", "The auditorium where you had your first student orientation.");
   struct Room* SU = newRoom("The Student Union", "Still under construction with a bunch of pipes lying around");
   struct Room* McGuirk = newRoom("McGuirk Stadium", "Quiet without all the noise from the tailgates.");

//Initializing all items
   struct Item* sword = newItem("sword", "A small sword katana wrapped in a dry white towel");
   struct Item* knife = newItem("knife", "A small army knife switch blade");
   struct Item* brick = newItem("brick", "A brick with blood on it. It looks like it fell from the library");
   struct Item* plate = newItem("plate", "A jagged sharp broken plate from a dining hall");
   struct Item* syringe = newItem("syringe", "A dirty syringe");
   struct Item* pipe = newItem("pipe", "A pipe from the construction site");   

//Initializing characters
   struct Character* Player = newCharacter("Player");
   struct Character* Peter = newCharacter("Peter");
   struct Character* Joe = newCharacter("Joe");
   struct Character* Jorge = newCharacter("Jorge");
   struct Character* Hamid = newCharacter("Hamid");
   struct Character* Subaswammy = newCharacter("Subaswammy");
   
   //helper function to make sure index is not already used
   //IMPORTANT: the rooms have a variable field called use,
   //if a room has the use of 1, it represents that it has
   //already been used in the board creation
   //if a room has the use of 2, it represents that it has 
   //already been used for a character
   //if a room has a use of 3, it represent that is has already
   //been used for an item.
   int produceIndex(char* settings, struct Room* array[9]) {
      int index;
      if (strcmp(settings, "board") == 0) {
	 index = rand() % 9;
	 if (array[index]->use == 1) {
	    for (int i = index; i<9; i++){
	       if (array[i]->use != 1) {
		  return i;
	       }		
	    }
            for (int i = index; i>=0; i--){
               if (array[i]->use != 1) {    
                  return i;
               }
            }
	 } 
	 return index;
      } else if (strcmp(settings, "characters") == 0) {
         index = rand() % 6;
         if (array[index]->use == 2) {
            for (int i = index; i<6; i++){
               if (array[i]->use != 2) {    
                  return i;
               }
            }
            for (int i = index; i>=0; i--){
               if (array[i]->use != 2) {
                  return i;
               }
            }
         }
         return index;
      } else if (strcmp(settings, "items") == 0) {
         index = rand() % 6;
         if (array[index]->use == 3) {
            for (int i = index; i<6; i++){
               if (array[i]->use != 3) {    
                  return i;
               }
            }
            for (int i = index; i>=0; i--){
               if (array[i]->use != 3) {
                  return i;
               }
            }
         }
         return index;
      }
   } 

   struct Item* test[3];
   
//game board
   struct Room* map[3][3];

//this room array will help with randomization
   struct Room* boardArray[] = {Center, Garage, Library, Lederle, Hamp, Pond, FAC, SU, McGuirk};

//board randomization  
   int index;
   for (int i=0; i<3; i++) {
      for (int j=0; j<3; j++) {
  	 index =  produceIndex("board", boardArray);
         map[i][j] = (struct Room*) malloc(sizeof(struct Room));
         map[i][j] = boardArray[index];
	 boardArray[index]->use = 1;
	 boardArray[index]->rowLoc = i;
	 boardArray[index]->columnLoc = j;
      }	 
   }

//character randomization
   struct Character* charArray[6] = {Player, Joe, Peter, Hamid, Jorge, Subaswammy};
   for (int i=0; i<6; i++) {
      index = produceIndex("characters", boardArray);
      (charArray[i])->location = boardArray[index];
      boardArray[index]->use = 2;
   }


//Item randomization
   struct Item* itemArray[6] = {sword, knife, brick, plate, syringe, pipe};
   for (int i=0; i<6; i++) {
      index = produceIndex("items", boardArray);
      boardArray[index]->roomInventoryHead->next = itemArray[i];
      boardArray[index]->use = 3;
   }

//Meat of the Game. Player prompts and comands until game is over
   printf("\n\nWelcome to Clue v.230! You will have 10 guesses to figure out who who the murderer is, in which room, and which weapon.\n");
   printf("the 'List' command will list all the rooms, items, and characters in the game and the 'Help' command will tell you all the commands you can use. Enjoy the game! :) \n\n");

   //randomly generates a correct answer;
   struct Room* roomAns = boardArray[rand() % 9];
   struct Item* itemAns = itemArray[rand() % 6];
   struct Character* characterAns = charArray[(rand() % 5)+1];


//COMMAND function takes player input, processes it, and returns 0, 1, 2
   int command(char word1[12]) {
      //COMMAND: help
      if (strcmp(word1, "help") ==0) {
 	 printf("   'list' lists all the items, areas, and characters in the game.\n");
	 printf("   'look' tells you the area in each direction and the characters and items in the current area\n");
	 printf("   'go DIRECTION' where DIRECTION is north, east, south, or east. Moves you into a new area\n");
	 printf("   'take ITEM' where ITEM is an item in the current area. Also takes item from the area and places it in your inventory\n");
	 printf("   'drop ITEM' removes ITEM from your inventory and drops into the current room\n");
	 printf("   'inventory' lists all the items in your inventory");
	 printf("   'clue CHARACTER' where CHARACTER is a character in the game, is your guess of who done it.\n");
	 printf("    This takes into account the area you're in, the items in the area and your inventory, and the character you guessed\n\n");
         return 0;
       }

       //COMMAND: list
       if (strcmp(word1, "list") == 0) {
	  printf("Characters: Peter, Joe, Jorge, Hamid, Subaswammy\n");
	  printf("Items: sword, knife, brick, broken plate, syringe, pipe\n");
	  printf("Rooms: Center, Garage, Library, Lederle, Hamp, McGuirk, FAC, Pond, SU \n");
	  return 0;
       }

       //COMMAND: look
       if (strcmp(word1, "look") == 0) {
	  //Room and Description
	  printf("\nCurrent Room: %s\n", Player->location->name);
	  printf("Description: %s\n", Player->location->description);

	  //North Direction
	  if ((Player->location->rowLoc)-1 >= 0) {
	     printf("In the North Direction is %s\n", map[(Player->location->rowLoc)-1][Player->location->columnLoc]->name);
	  }
	  //East Direction
          if ((Player->location->columnLoc)+1 <= 2) {
              printf("In the East Direction is %s\n", map[(Player->location->rowLoc)][(Player->location->columnLoc)+1]->name);
           }
	   //South Direction
           if ((Player->location->rowLoc)+1 <= 2) {
              printf("In the South Direction is %s\n", map[(Player->location->rowLoc)+1][(Player->location->columnLoc)]->name);
           }
	   //West Direction
           if ((Player->location->columnLoc)-1 >= 0) {
              printf("In the West Direction is %s\n", map[(Player->location->rowLoc)][(Player->location->columnLoc)-1]->name);
           }
	  
	   //Items in the room
           if (Player->location->roomInventoryHead->next == NULL) {
              printf("There are no items here\n");
           } else {
	      struct Item* temp = (struct Item*) malloc(sizeof(struct Item));
	      temp = Player->location->roomInventoryHead;
              while (temp->next != NULL) {
                 printf("You found %s\n", temp->next->description);
                 temp = temp->next;
              }
	      temp = NULL;
 	      free(temp);
           }

	   //Characters in the room
	   //this is to check if there is no one in the room;
	   int check = 0;
	   for(int i=0; i<6; i++){
	      if (strcmp(charArray[i]->location->name, Player->location->name) == 0) {
	         if (charArray[i] != Player) {
		    printf("%s is here as well\n", charArray[i]->name);
	            check++;
		 }
	      }
	    }
	    if (check == 0) {
	       printf("There is nobody here\n\n");
	    }

	   return 0;
        }

	//COMMAND: go DIRECTION
        if (strcmp(word1, "go") == 0) {
	   char word2[12];
	   scanf("%s", word2);
	   
	   //North
	   if (strcmp(word2, "north") == 0) {
	      if ((Player->location->rowLoc)-1 >= 0) {
	         Player->location = map[(Player->location->rowLoc)-1][(Player->location->columnLoc)];
	         printf("You are now at %s\n", Player->location->name);
                 return 0;
	      } else {
	         printf("There is nothing in that direction, please choose another direction\n");
                 return 0;
	      }
	   }

	   //East
	   if (strcmp(word2, "east") == 0) {
              if ((Player->location->columnLoc)+1 <= 2) {
                 Player->location = map[(Player->location->rowLoc)][(Player->location->columnLoc)+1];
                 printf("You are now at %s\n", Player->location->name);
                 return 0;
              } else {
                 printf("There is nothing in that direction, please choose another direction\n");
                 return 0;
              }
	   }

	   //South
	   if (strcmp(word2, "south") == 0) {
              if ((Player->location->rowLoc)+1 <= 2) {
                 Player->location = map[(Player->location->rowLoc)+1][(Player->location->columnLoc)];
                 printf("You are now at %s\n", Player->location->name);
                 return 0;
              } else {
                 printf("There is nothing in that direction, please choose another direction\n");
                 return 0;
              }
	   }

	   //West
	   if (strcmp(word2, "west") == 0) {
              if ((Player->location->columnLoc)-1 >= 0) {
                 Player->location = map[(Player->location->rowLoc)][(Player->location->columnLoc)-1];
                 printf("You are now at %s\n", Player->location->name);
		 return 0;		 
              } else {
                 printf("There is nothing in that direction, please choose another direction\n");
                 return 0;
              }
	   }

	   printf("invalid direction\n");	   
	   return 0;
        }

	//COMMAND: take ITEM
	if (strcmp(word1, "take") == 0) {
	   char word2[12];
	   scanf("%s", word2); 
	   takeItem(word2, Player->location->roomInventoryHead, Player->inventoryHead);
 	   return 0;
	}

	//COMMAND: Drop Item
        if (strcmp(word1, "drop") == 0) {
           char word2[12];
           scanf("%s", word2);
           dropItem(word2, Player->location->roomInventoryHead, Player->inventoryHead);
           return 0;
        }

	//COMMAND: inventory
	if (strcmp(word1, "inventory") == 0) {
           struct Item* temp = (struct Item*) malloc(sizeof(struct Item));
	   temp = Player->inventoryHead->next;
	   if (Player->inventoryHead->next == NULL) {
	      printf("your inventory is empty\n");
	   } else {
	      printf("In your inventory there is: \n");
   	      while(temp != NULL) {
		 printf("%s\n", temp->name);
	         temp = temp->next;
	      }
	   }
	   temp = NULL;
	   free(temp);
	   return 0;
	}

	//COMMAND: clue CHARACTER
	if (strcmp(word1, "clue") == 0) {
	   char word2[12];
    	   scanf("%s", word2);
	   
           //move the character into the room
           for(int i=0; i<6; i++){
              if (strcmp(charArray[i]->name, word2) == 0) {
                 charArray[i]->location = Player->location;
	         break;
              }
            }	   

	   //room match
	   int count = 0;
	   if (strcmp(Player->location->name, roomAns->name) == 0) {
	      count++;
	      printf("Room Match\n");
	   }

	   //character match
	   if (strcmp(characterAns->name, word2) == 0) {
	      count++;
	      printf("Character Match\n");
	   }

	   //traverse inventory and room
	   struct Item* temp = (struct Item*) malloc(sizeof(struct Item));
	   temp = Player->inventoryHead->next;
	   while (temp != NULL) {
	      if (strcmp(temp->name, itemAns->name) == 0) {
		 count++;
		 printf("Item Match\n");
         	 break;
	      }
	      temp = temp->next;
	   }

	   temp = Player->location->roomInventoryHead->next;
	   while (temp != NULL) {
              if (strcmp(temp->name, itemAns->name) == 0) {
                 count++;
                 printf("Item Match\n");
                 break;
              }
	      temp = temp->next;
	   }

	   temp = NULL;
	   free(temp);
	   if (count == 3) {
	      return 1;
	   } else {
 	      return 2;
    	   }
        }

	//helper method that breaks while loop
	if (strcmp(word1, "break") == 0) {
	   return 6;
	}

	//This is the case where there is no proper command
	else {
	   printf("Invalid command. Try again. \n\n");
	   return 0;
	}
     } 
//---------------------------------------Game Recursive command Loop
  
   char word1[12];
   int gameOver = 0;
   int result = 0;
   int numGuesses = 10;

   while(gameOver == 0) {
      printf("\n	Character Answer: %s\n", characterAns->name);
      printf("	Room Answer: %s\n", roomAns->name);
      printf("	Item Answer: %s\n", itemAns->name);

      printf("\nType 'Help' for the list of commands. type a command: ");
      
      //user input 
      scanf("%s", word1);
      	
      //pass input into command and figures out which command result to return
      result = command(word1);
   
      if (result == 1) {
	 printf("\nCongratulations! You have won since you have guessed correctly!\n");
	 break;
      }
      if (result == 2) {
	 numGuesses--;
	 if (numGuesses == 0) {
	    printf("\nGame over. You have no more guesses left. The correct answer was,\nCharacer: %s\nRoom: %s\nItem: %s\n\n", characterAns->name, roomAns->name, itemAns->name);
	    break;
	 } else {
   	    printf("\nYou have %i guesses left\n", numGuesses);
	 }
      }

      //helper method that breaks code in game
      if (result == 6) {
	 break;
      }
   }
   
   //Free characters, rooms, items, and linked list heads.
   for(int i=0; i<9; i++) {
      if(i < 6) {
	 free(charArray[i]->inventoryHead);
	 free(charArray[i]);
	 free(itemArray[i]);
         free(itemArray[i]->traverseResult);
      }
      free(boardArray[i]->roomInventoryHead);
      free(boardArray[i]);
   }
   
}


