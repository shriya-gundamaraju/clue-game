#ifndef __ITEMS_H__
#define __ITEMS_H__ 
#include <stdio.h>

typedef struct Item {
    char* name;
    struct Item *next;
}Item;

//adds item to itemList
void addItem(Item **listPtr, Item * newItem);

//removes an item from itemList
Item *removeItem(Item **listPtr, char* n);
#endif
