#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rooms.h"

//creates a room
Room* createRoom(){
    Room* room = (Room*) calloc(1,sizeof(Room));
    return room;
}

//deallocates a room
void freeRoom(Room * room) {
    Item * item = room->itemList;
    while (item != NULL) {
        Item * temp = item;
        item = item->next;
        free(temp);
    }
    Character * character = room->charList;
    while (character != NULL) {
        Character * temp = character;
        character = character->next;
        free(temp);
    }
    free(room);
}

//add a character to a room
void addCharToRoom(Room * room, Character * newChar) {
    if (newChar != NULL) {
        newChar->next = room->charList;
        room->charList = newChar;
    }
}

//remove a character from a room
Character * removeCharFromRoom(Room * room, char * charName) {
    Character * curNode = room->charList;
    Character * prevNode = NULL;
    while (curNode != NULL) {
        if (!strcmp(curNode->name,charName)) {
            if (prevNode == NULL) {
                room->charList = curNode->next;
            }
            else {
                prevNode->next = curNode->next;
            }
            return curNode;
        }
        prevNode = curNode;
        curNode = curNode->next;
    }
    return NULL;
}

//check to see if a character is in a room
bool charInRoom(Room * room, char * charName) {
    Character * curNode = room->charList;
    while (curNode != NULL) {
        if (!strcmp(curNode->name,charName)) {
            return true;
        }
        curNode = curNode->next;
    }
    return false;
}
