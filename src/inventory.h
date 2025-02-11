#ifndef INVENTORY
#define INVENTORY


#include <map>
#include <vector>
#include <iostream>
#include <string>

#include "item.h"
#include "logger.h"
#include "json.hpp"
#include "dropTable.h"

using json = nlohmann::json;
struct rollResult;
class Inventory
{
    public:


    void addItems(vector<rollResult> stuff);
    void addItems(vector<Item> stuff);
    void addItem(Item i);

    Item * get(Item i);
    void removeItem(Item i); 
    void showInventory(); 
    json to_json();
    private:
    map<string, Item> items;


};

#endif