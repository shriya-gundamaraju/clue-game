#ifndef __ROOMS_H__
#define __ROOMS_H__ 
#include <stdio.h>
#include <stdbool.h>
#include "items.h"

#define NUM_CHARACTERS 9

typedef struct Character {
    char* name;
    struct Character* next;
}Character;

typedef struct Room {
    char* name;
    struct Room * North;
    struct Room * South;
    struct Room * East;
    struct Room * West;
    struct Item * itemList;
    Character * charList;
    // char *character[NUM_CHARACTERS];
    // char * character;
}Room;

//creates a room
Room* createRoom();

//deallocates a room
void freeRoom(Room * room);

//adds a character to a room
void addCharToRoom(Room * room, Character * newChar);

//removes a character from a room
Character * removeCharFromRoom(Room * room, char * charName);

//check to see if a character is in a room
bool charInRoom(Room * room, char * charName);
#endif
