#include "inventory.h"


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