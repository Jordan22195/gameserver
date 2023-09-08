#ifndef INVENTORY
#define INVENTORY


#include <map>
#include <vector>
#include <iostream>
#include <string>

#include "item.h"
#include "logger.h"
#include "json.hpp"

using json = nlohmann::json;

class Inventory
{
    public:


    void addItems(vector<Item> stuff);

    Item * get(Item i);
    void removeItem(Item i); 
    void showInventory(); 
    json to_json();
    private:
    map<string, Item> items;


};

#endif