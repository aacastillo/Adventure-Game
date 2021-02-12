Alan Castillo
Video Link: https://youtu.be/Ywt8M5JA2Xs

This game was actually a lot of fun despite the suffering of debugging it.

Implementation Overview:
//ROOM RANDOMIZATION
Randomization was a bit tricky.
First I created individual pointer arrays for rooms, items, and characters respectively.
then by using rand(),  srand(time(null)), and modulus I was able to get a random index for each
array.

With this random index, I was able to randomize the map. By using a 3x3 array matric of type Room
Pointer I was able to traverse the matrix with a nested for loop and assign each piece of the matrix
a random room using the random index. The trick however was to make sure that I didn't get the same 
room twice. So what I did was add a new field in Room struct called "use" with type int.

This way when a room is assigned, I set that room's use = 1; so then when we get another random
room with the random matrix, we first check that its use does not equal 1, and then we assign 
the next piece of the matrix to the room that has been checked. if the random room has already
been used (use=1) we find a room that hasn't been used in the pointer array (not the matrix).

//CHARACTER RANDOMIZATION
This same strategy was used to assign the location of each character and item.
for the character location I created a pointer array with each character.
I then traverse the character pointer array and assigned each character location to 
a random room using the room pointer array and rand() % 9 as the index.
How did I avoid using the same room? after using a room, I set its use field  = 2, and 
then after picking another random room I would check that it was not equal to 2.

//ITEM RANDOMIZATION
for each item I created again an item pointer array with every item, I traversed
the item array and then I chose a random room using the room pointer array and assigned
then assigned the "next" item value of the room's inventory head to the current item.
To avoid using the same room I again used the room's use field. after using a room
I set the room's use field to 3, that way with the next item I would check if the room
had been already used (=3).

//RANDOM ANSWER
I then used these pointers and took a random index of each to get a random room answer, 
character answer, and items answer. I made sure that the player avatar could not be a
character answer.

//LOOK AND GO DIRECTION
for the look and go direction, I just used the 3x3 matrix. To implement it in this way,
I needed each room to know where it was on the map. So in the header I gave the room structure
two fields called rowLoc and columnLoc, which would store the indexes that the room was located
on the map. Using these fields I was able to look at that players location and that location's space
on the map and look at the neighboring rooms by adding or subtracting 1 from the rowLoc or columnLoc.
to move a direction, I just changed the players location (location was a field in the character struct).

//TAKE AND DROP ITEM
The trickiest part of this was handling how to take out items, traverse through inventories, and add items.
To do this I gave the room structure an item pointer similiar to the lab to create a linked list. I split
dropping and taking an item into seperate fundamental functions: searching for and moving an item given an
inventoryHead. When traversing I created temporary item pointers that would make sure the inventory heads were
not changed.

//USER INPUT AND END STATE
finally I had a master command function that took in user input and then found the corresponding function
such as go, take, or look and then ran it. the command function returns a number. All functions inside of 
command, beside clue CHARACTER, returns 0. When the player uses the clue command, the function either
returns 1 or 2. 1 being correct and showing the winning state, and 2 being incorrect and deducing the 
number of guesses the player has left. The user scan input and command function is ran continuously in a while
loop until either the player guesses correctly or they run out of guesses (numGuesses=0), in each case the 
while loop is broken. After the while loop is broken everything is freed.



