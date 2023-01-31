#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "items.h"

//method that adds items to itemList
void addItem(Item **listPtr, Item * newItem) {
    if (newItem != NULL) {
        newItem->next = *listPtr;
        (*listPtr) = newItem;
    }
}

//method that removes items from itemList
Item *removeItem(Item **listPtr, char* n) {
    Item *curNode = *listPtr;
    Item *prev = NULL;
    while (curNode != NULL) {
        if (!strcmp(curNode->name,n)) {
            if (prev == NULL) {
                *listPtr = curNode->next;
            }
            else {
                prev->next = curNode->next;
            }
            return curNode;
        }
        prev = curNode;
        curNode = curNode->next;
    }
    return NULL;
}
