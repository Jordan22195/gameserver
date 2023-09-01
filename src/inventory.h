#ifndef INVENTORY
#define INVENTORY


#include <map>
#include <vector>
#include <iostream>
#include <string>

#include "item.h"
#include "logger.h"


class Inventory
{
    public:


    void addItems(vector<Item> stuff);

    Item * get(Item i);
    void removeItem(Item i); 
    void showInventory(); 
    string packetify();
    private:
    map<string, Item> items;


};

#endif