#include "inventory.h"
#include <sstream>

using namespace std;

void Inventory::addItems(vector<Item> stuff) {
    for ( auto&  i : stuff)
    {
        if(items.count(i.getName()) == 0)
        {
            items[i.getName()] = i;
        }
        else
        {
            items[i.getName()].quantity += i.quantity;
        }
    }
}

Item * Inventory::get(Item i)
{
    if(items.count(i.getName()) == 0)
    {
        return nullptr;
    }
    else
    {
        return &items[i.getName()];
    }
}

void Inventory::removeItem(Item i) 
{
    if(items.count(i.getName()) == 0)
    {

        return;
    }
    else
    {
        items[i.getName()].quantity -= i.quantity;
        if (items[i.getName()].quantity <= 0)
        {
            items.erase(i.getName());
        }
    }
}

void Inventory::showInventory() {
    for (auto it = items.begin(); it != items.end() ; ++it)
    {
        cout << it->first << " x" << it->second.quantity << endl;
    }
}

json Inventory::to_json()
{
    Logger::TRACE("string Inventory::to_json()  %p", this);
    json j;
    json itemArray = json::array();
    Logger::TRACE("item array created");
    for (auto it = items.begin(); it != items.end() ; ++it)
    {
        Logger::TRACE("json-ifie next item");
        json j = it->second.to_json();
        //itemArray.push_back(j.dump());
    }
    Logger::TRACE("end of items");
    j["items"] = itemArray;
    return itemArray;
}