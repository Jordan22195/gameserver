#ifndef ITEM
#define ITEM

#include <string>
#include <memory>
#include <sstream>
#include "json.hpp"

using json = nlohmann::json;
using namespace std;


enum class ItemIdEnum
{
    ITEM_COINS = 1000000,
    ITEMS_OAKLOGS,
};

class  Item
{
    public:
    string name;
    string description;
    int quantity = 1;
    virtual string getName();
    virtual json to_json();
};

class RegularLogsItem : public Item
{
    public:
    RegularLogsItem(int count = 1) 
    {
        quantity = count;
        name = "Regular Logs";
        description = "Ordinary Logs";
    }

};

class CoinsItem : public Item
{
    public:
    CoinsItem(int count = 1) 
    {
        quantity = count;
        name = "Coins";
        description = "Money!";
    }
};

class ArrowShaftsItem : public Item
{
    public:
    ArrowShaftsItem(int count = 1) 
    {
        quantity = count;
        name = "Arrow Shafts";
        description = "used for making arrows";
    }
};


#endif