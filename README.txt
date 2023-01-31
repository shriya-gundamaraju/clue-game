README.txt

HOW TO COMPILE THE CODE:
To compile this code run the following command:
gcc -std=c99 -Wall -o clue items.c rooms.c adventure.c

Then to execute the code enter:
./clue

OVERALL STRUCTURE OF THE GAMEBOARD WITH POINTERS:
I created a 3x3 2D array for my gameboard. I created a method in rooms.c called createRoom() that allocates memory for a room struct and returns it. In my adventure.c file, I then had a method createGameBoard() that called createRoom() 9 times and assigned each cell of the 2D gameboard to an empty room. Then, in my initGameBoardAndAvatar() method I connected each room to surrounding rooms using pointers. 

MANAGING USER INPUT:
In order to manage user input, I used getline and passed in a char pointer to store what the user inputs. I also created a size_t variable that stored the MAX_COMMAND_SIZE, which I set to be 32, which I also passed into getline. Whenever I wanted to use the user input in my code, I was able to just use the char pointer that stores the input.

PROJECT REQUIREMENTS (From the grading rubric):
(in adventure.c unless other specified)

2a -> 9 rooms connected via pointers: 
452: I created an empty 3x3 2D array 
91-99: I traversed the 2D array, and assigned empty rooms to each cell in the gameboard
103-119: I connected the rooms via pointers

2b -> Randomly initialize the location of each room in the game board before the game starts
121 - 130: I randomized the array of room names and then traversed the 2D array and assigned each room a name from the randomized array

2c -> At least 6 items and 5 characters other than the player's avatar
132 - 150: Place 6 items at random locations on the gameboard; only one item per room to start off
152 - 174: Place 6 characters in random rooms; multiple characters can end up in the same room

2d -> Random answer:
190 - 200: Generates a random answer and then executed in line 463

2e -> Your game must allow each room to have a linkedList of items: (in rooms.h)
20 - struct Item * itemList

2f -> Your game must implement an avatar where the avatar has an inventory:
11 - 15: Avatar struct, Item * inventory is a linked list of items
453: Creation of avatar

gi -> help command
207 - 217: help method
480 - 482: runs the help method if the user types in help

gii -> list
53 - 77: 3 methods that print out a list of all rooms, items, and characters
483 - 487: runs the list methods if the user types list

giii -> look
219 - 261: look method
488 - 490: runs the look method if the user types look

giv -> go
263 - 283: go method
491 - 501: runs the go method if the user types go

gv -> take
286 - 305: take method
502 - 510: runs the take method if the user types take

gvi -> drop
309 - 328: drop method
511 - 519; runs the drop method if the user types drop

gvii -> inventory
330 - 343: inventory method
520 - 522: runs the inventory method if the user types inventory

gviii -> clue
369 - 447: clue method
523 - 532: runs the clue method if the user types clue

gix -> The game must allow an avatar to retype a command if the command is not one of the above
533 - 535: Prompts the user to enter another command if it is not a valid command

hi -> Move the character stated in the command to the same room of avatar.
412 - 420: Moves the character using helper methods removeCharFromRoom (rooms.c 37 - 55) and addCharToRoom (rooms.c 29 - 35)

hii -> matching detail
421 - 436: Displays which guesses you got correct

hiii -> winning and losing states
439 - 443: Winning state
526 - 531: Losing state


























 


