#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include "items.h"
#include "rooms.h"

#define MAX_COMMAND_SIZE 32
typedef struct {
    char *name;
    Room *room;
    Item* inventory;
} Avatar;

typedef struct {
    char *name;
    char *room;
    char *item;
} Answer;

//name of rooms:
char* roomNames[9] = {
    "kitchen", 
    "ballroom", 
    "conservatory", 
    "dining room", 
    "billiard room", 
    "library", 
    "lounge", 
    "hall", 
    "study"};

//name of items:
char* itemNames[6] = {
    "candlestick", 
    "dagger", 
    "lead pipe", 
    "revolver", 
    "rope", 
    "wrench"};

//name of characters:
char* characterNames[6] = {
    "Miss Scarlet", 
    "Colonel Mustard", 
    "Mrs. White", 
    "The Reverend Green", 
    "Mrs. Peacock", 
    "Professor Plum"};

//prints a list of rooms
void listRooms() {
    printf("\nList of Rooms:\n");
    for (int i=0; i<9; i++) {
        printf("\t%s\n", roomNames[i]);
    }
}

//prints a list of items
void listItems() {
    printf("\nList of Items:\n");
    for (int i=0; i<6; i++) {
        printf("\t%s\n", itemNames[i]);
    }
}

//prints a list of characters
void listCharacters(Avatar *avatar) {
    printf("\nList of Characters:\n");
    for (int i=0; i<6; i++) {
        if (strcmp(avatar->name,characterNames[i])) {
            printf("\t%s\n", characterNames[i]);
        }
    }
}

//function to randomize an array of chars
void randomize(char* arr[], int size) {
    srand(time(NULL));
    for (int i = 0; i < size; i++)
    {
        int randIndex = rand() % size;
        char *temp = arr[i];
        arr[i] = arr[randIndex];
        arr[randIndex] = temp;
    }
}

//allocates memory for the 9 rooms in the game board
void createGameBoard(Room *gameBoard[3][3]) {
    //creating a room in each cell of the game board
    for (int i=0; i<3; i++) {
        for (int j=0; j<3; j++) {
            gameBoard[i][j] = createRoom();
        }
    } 
}

//initialize game board
void initGameBoardAndAvatar(Room* gameBoard[3][3], Avatar *avatar) {
    //connect rooms with pointers
    for (int i=0; i<3; i++) {
        for (int j=0; j<3; j++) {
            if (j != 2) {
                gameBoard[i][j]->East = gameBoard[i][j+1];
            }
            if (j != 0) {
                gameBoard[i][j]->West = gameBoard[i][j-1];
            }
            if (i != 0) {
                gameBoard[i][j]->North = gameBoard[i-1][j];
            }
            if (i != 2) {
                gameBoard[i][j]->South = gameBoard[i+1][j];
            }
        }
    }

    //randomize array of room names 
    randomize(roomNames,9);

    //randomize location of rooms
    int roomNameCount = 0;
    for (int i=0; i<3; i++) {
        for (int j=0; j<3; j++) {
            gameBoard[i][j]->name = roomNames[roomNameCount++];
        }
    }

    //place item in a random room, one item per room
    //get random number within 0-8 , and row = num/3, col = num%3, then iterate through items
    //array and add it to the corresponding row and col of gameBoard[r][c]->item, make sure
    //there are no items in the room
    randomize(itemNames,6);
    for (int i=0; i<6;) {
        int randNum = rand() % 9;
        int row = randNum/3;
        int col = randNum%3;
        //conditional to make sure that there is nothing in the linked list 
        //(meaning the room doesn't have any items before adding one)
        if (gameBoard[row][col]->itemList == NULL) {
            Item *head = (Item *) malloc(sizeof(Item));
            head->name = itemNames[i];
            head->next = NULL;
            gameBoard[row][col]->itemList = head; 
            i++;
        } 
    }

    //randomize characterNames array
    randomize(characterNames,6);

    //assign Avatar name
    avatar->name = "You";

    //assign characters to different cells in the game board, there can be multiple characters per room
    for (int i=0; i<6; i++) {
        int randNum = rand() % 9;
        int row = randNum/3;
        int col = randNum%3;
        Character *node = (Character *) malloc(sizeof(Character));
        node->name = characterNames[i];
        node->next = NULL;
        //if the room already has a character, prepend character to charList
        if (gameBoard[row][col]->charList != NULL) {
            node->next = gameBoard[row][col]->charList;
        }
        //if the room has no characters, assign charList to the character
        else {
            gameBoard[row][col]->charList = node;
        }
    }   

    //place Avatar in a random room 
    int randNum = rand() %9;
    avatar->room = gameBoard[randNum/3][randNum%3];
}

//deallocates memory for the game board
void freeGameBoard(Room * gameBoard[3][3]) {
    for (int i=0; i<3; i++) {
        for (int j=0; j<3; j++) {
            freeRoom(gameBoard[i][j]);
        }
    }
}

//generates a random answer for the game
void createAnswer(Answer* answer) {
    // Randomize Room names, item names and character names and choose the
    // first value of each respective array as the answer
    randomize(roomNames,9);
    randomize(itemNames,6);
    randomize(characterNames,6);
    answer->room = roomNames[0];
    answer->item = itemNames[0];
    answer->name = characterNames[0];
}

//remove new line
void removeLastChar(char * str) {
    str[strlen(str)-1] = '\0';
}

//help command
void help() {
    printf("help: a list of all the valid commands\n");
    printf("list: a list of all the valid rooms, items, and characters\n");
    printf("look: shows your current location and the items and characters in the room, as well as surrounding rooms\n");
    printf("go: command to move around the game board\n");
    printf("take: command to take items from a room\n");
    printf("drop: command to drop items from your inventory into the room\n");
    printf("inventory: shows the items in your inventory\n");
    printf("clue: command to make a guess about the murder!\n");
}

// Your game must allow an avatar to “see” the room they are in with the command “look”, including the
// rooms in each direction, the characters in the room and the items in the room.
void look(Avatar *avatar) {
    Room *room = avatar->room;
    printf("\n%s are in the %s \n", avatar->name, room->name);
    printf("\n");
    if (room->North != NULL) {
        printf("To the North is the %s\n", room->North->name);
    }
    if (room->South != NULL) {
        printf("To the South is the %s\n", room->South->name);
    }
    if (room->East != NULL) {
        printf("To the East is the %s\n", room->East->name);
    }
    if (room->West != NULL) {
        printf("To the West is the %s\n", room->West->name);
    }
    if (room->charList == NULL) {
        printf("\nThere are no characters in the room");
    }
    else {
        printf("\nThe following characters are in the room:");
        Character *charNode = room->charList;
        while (charNode!=NULL) {
            printf("\n%s", charNode->name);
            charNode = charNode->next;
        }
    }
    printf("\n");
    if(room->itemList == NULL) {
        printf("\nThere are no items in the room");
    }
    else {
        printf("\nThe following items are in the room:");
        Item *item = room->itemList;
        while(item!=NULL) {
            printf("\n%s", item->name);
            item = item->next;
        }
    }
    printf("\n");
}

//go command: takes in a direction which the user inputs
bool go(Avatar *avatar, char *direction) {
    Room *room = avatar->room;
    if (!strcmp(direction,"North") && (room->North != NULL)) {
        avatar->room = room->North;
    }
    else if (!strcmp(direction,"South") && (room->South != NULL)) {
        avatar->room = room->South;
    }
    else if (!strcmp(direction,"East") && (room->East != NULL)) {
        avatar->room = room->East;
    }
    else if (!strcmp(direction,"West") && (room->West != NULL)) {
        avatar->room = room->West;
    }
    else {
        printf("Please enter a valid direction (North, South, East, West): ");
        return false;
    }
    return true;
}


//take command: take an item from the current room, and add to your inventory
bool take(Avatar *avatar) {
    char *item = (char *) malloc(MAX_COMMAND_SIZE);
    size_t itemSize = MAX_COMMAND_SIZE;
    bool found = false;
    printf("Which item would you like to take? \n");
    getline(&item,&itemSize,stdin);
    removeLastChar(item);
    //conditional to check that item is in room AND user typed in a valid item name
    Item * newItemForInventory = removeItem(&(avatar->room->itemList),item);
    if (newItemForInventory == NULL) {
        printf("Please enter a valid item that is in your current room. \n");
    }
    else {
        addItem(&(avatar->inventory),newItemForInventory);
        found = true;
    }
    free(item);
    return found;
}


//drop command: drop an item from players inventory and add to the current room
bool drop(Avatar *avatar) {
    char *item = (char *) malloc(MAX_COMMAND_SIZE);
    size_t itemSize = MAX_COMMAND_SIZE;
    bool found = false;
    printf("Which item would you like to drop? ");
    getline(&item,&itemSize,stdin);
    removeLastChar(item);
    //if item doesn't exist in avatar's inventory, removeItem will return NULL
    Item * newItemForRoom = removeItem(&(avatar->inventory),item);
    if (newItemForRoom == NULL) {
        printf("Please enter a valid item that is a part of your inventory. \n");
    }
    //else, if item does exist in inventory remove from inventory and add to room
    else {
        addItem(&(avatar->room->itemList),newItemForRoom);
        found = true;
    }
    free(item);
    return found;
}

//inventory command
void inventory(Avatar *avatar) {
    if (avatar->inventory == NULL) {
        printf("\nThere are no items in your inventory. \n");
    }
    else {
        printf("\nYour inventory is: \n");
        Item * curItem = avatar->inventory;
        while (curItem != NULL) {
            printf("%s \n", curItem->name);
            curItem = curItem->next;
        }
    }
}

//check to see if item is in the inventory
bool itemInInv(Avatar *avatar, char * itemName) {
    Item * curNode = avatar->inventory;
    while (curNode != NULL) {
        if (!strcmp(curNode->name,itemName)) {
            return true;
        }
        curNode = curNode->next;
    }
    return false;
}

//check to see if item is in the room
bool itemInRoom(Avatar *avatar, char * itemName) {
    Item * curNode = avatar->room->itemList; 
    while (curNode != NULL) {
        if (!strcmp(curNode->name,itemName)) {
            return true;
        } 
        curNode = curNode->next;
    }
    return false;
} 

//clue command
void clue(Avatar *avatar,Answer *answer, Room * gameBoard[3][3]) {
    if ((avatar->inventory == NULL) && (avatar->room->itemList == NULL)) {
        printf( "There are no items in your inventory or current room. \n");
        return;
    }
    char *character = (char *) malloc(MAX_COMMAND_SIZE);
    size_t characterSize = MAX_COMMAND_SIZE;
    bool charFound = false;
    printf("Choose a character: \n");
    while(!charFound) {
        getline(&character,&characterSize,stdin);
        removeLastChar(character);
        for (int i=0; i<6; i++) {
            if (!strcmp(characterNames[i],character)) {
                charFound = true;
                break;
            }
        }
        if (!charFound) {
            printf("Please enter a valid character name: \n");
        }
    }
    char *item = (char *) malloc(MAX_COMMAND_SIZE);
    size_t itemSize = MAX_COMMAND_SIZE;
    bool itemFound = false;
    while(!itemFound) {
        printf("Choose an item: \n");
        getline(&item,&itemSize,stdin);
        removeLastChar(item);
        if (!itemInInv(avatar,item) && !itemInRoom(avatar,item)) {
            printf("Item is not valid as it is not part of your inventory or room. \n");
        }
        else {
            for (int i=0; i<6; i++) {
                if (!strcmp(itemNames[i],item)) {
                    itemFound = true;
                    break;
                }
            }
        }
    }
    //check gameBoard to see which room has chosen character and remove from that room and
    //move to avatar's current room 
    for (int i=0; i<3; i++) {
        for (int j=0; j<3; j++) {
            if (charInRoom(gameBoard[i][j],character)) {
                Character * moveChar = removeCharFromRoom(gameBoard[i][j],character);
                addCharToRoom(avatar->room,moveChar);
            }
        }
    } 
    //see if the answer is correct
    bool charMatch = false;
    bool itemMatch = false;
    bool roomMatch = false;
    if (!strcmp(answer->name,character)) {
        printf("\nCharacter Match! \n");
        charMatch = true;
    }
    if (!strcmp(answer->item,item)) {
        printf("Item Match! \n");
        itemMatch = true;
    }
    if (!strcmp(answer->room,avatar->room->name)) {
        printf("Room Match! \n");
        roomMatch = true;
    }
    free(character);
    free(item);
    if (charMatch && itemMatch && roomMatch) {
        printf("\nGood job! You have won the game! \n");
        freeGameBoard(gameBoard);
        exit(1);
    }
    if (!charMatch || !itemMatch || !roomMatch) {
        printf("\nAnswer is incorrect, guess again! \n");
    }
}

//MAIN METHOD
int main (int argc, char *argv[]) {
    //empty gameBoard
    Room* gameBoard[3][3] = {NULL};
    Avatar avatar;
    Answer answer;

    //create Gameboard
    createGameBoard(gameBoard);

    //initializing game board
    initGameBoardAndAvatar(gameBoard, &avatar);

    //Create a Random answer
    createAnswer(&answer);
    
    //counter that increments every time clue() is called -> to keep track of losses
    int clueCounter = 0;    

    //Get the user input and act on it
    char *command = (char *) malloc(MAX_COMMAND_SIZE);
    size_t commandSize = MAX_COMMAND_SIZE;
    printf("WELCOME TO THE GAME\n");
    printf("\nType 'help' to see a list of all valid commands\n");
    while (1) {
        //get user entered command
        printf("\nEnter a command: ");
        getline(&command, &commandSize, stdin);
        //strip the newline character at the end of command
        int commandLen = strlen(command);
        command[commandLen-1] = '\0';
        if (!strcmp(command, "help")) {
            help();
        } 
        else if (!strcmp(command, "list")) {
            listRooms();
            listItems();
            listCharacters(&avatar);
        } 
        else if (!strcmp(command, "look")) {
            look(&avatar);
        }
        else if (!strcmp(command, "go")) {
            char * direction = (char *) malloc(MAX_COMMAND_SIZE);
            size_t directionSize = MAX_COMMAND_SIZE;
            printf("Which direction you would like to go (North,South,East,West): ");
            while (1) {
                getline(&direction,&directionSize,stdin);
                direction[strlen(direction)-1] = '\0';
                if (go(&avatar,direction)) { break; }
            }
            free(direction); 
        }
        else if (!strcmp(command, "take")) {
            while (1) {
                if (avatar.room->itemList == NULL) {
                    printf("\nThere are no items in your room, please choose another command. \n");
                    break;
                }
                if (take(&avatar)) {break; }
            }      
        }
        else if (!strcmp(command, "drop")) {
            while (1) {
                if (avatar.inventory == NULL) {
                    printf("\nThere are no items in your inventory, please choose another command. \n");
                    break;
                }
                if (drop(&avatar)) {break; }
            }
        } 
        else if (!strcmp(command, "inventory")) {
            inventory(&avatar);
        }
        else if (!strcmp(command, "clue")) {
            clue(&avatar,&answer,gameBoard);
            clueCounter++;
            if (clueCounter == 10) {
                printf("\nYou have lost. Try again next time! \n");
                freeGameBoard(gameBoard);
                free(command);
                exit(1);
            }
        } 
        else {
            printf("\nThe command \"%s\" is invalid, please type \"help\" to get a list of valid commands\n", command);
        }
    }
}
