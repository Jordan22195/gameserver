#ifndef ITEM
#define ITEM

#include <string>
#include <memory>

using namespace std;




class  Item
{
    public:
    string name;
    string description;
    int quantity = 1;
    virtual string getName();
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