#ifndef INVENTORY
#define INVENTORY


#include <map>
#include <vector>
#include <iostream>

#include "item.h"


class Inventory
{
    public:


    void addItems(vector<Item> stuff);

    Item * get(Item i);
    void removeItem(Item i); 
    void showInventory(); 

    private:
    map<string, Item> items;


};

#endif