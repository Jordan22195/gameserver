
#include "dropTable.h"

void dropTable::addEntry(Item item, double dropChance, int quantity)
{
    addEntry(item, dropChance, quantity, quantity);
}

void dropTable::addEntry(Item item, double dropChance, int quantityMin, int quantityMax)
{
    entry e;
    e.item = item;
    e.dropChance = dropChance;
    e.quantityMin = quantityMin;
    e.quantityMax = quantityMax;
    table.push_back(e);
}

double dropTable::getRandomDouble(double min, double max) 
{
    std::random_device rd; // Obtain a random seed from the hardware
    std::mt19937 gen(rd()); // Seed the generator
    std::uniform_real_distribution<double> dis(min, max); // Define the distribution

    return dis(gen);
}
int dropTable::getRandomInt(int min, int max) 
{
    std::random_device rd; // Obtain a random seed from the hardware
    std::mt19937 gen(rd()); // Seed the generator
    std::uniform_int_distribution<int> dis(min, max); // Define the distribution

    return dis(gen);
}

vector<Item> dropTable::roll()
{
    vector<Item> ret;
    for (entry& e : table)
    {
        if(getRandomDouble(0.0, 1.0) < e.dropChance)
        {
            auto i = e.item;
            i.quantity = getRandomInt(e.quantityMin, e.quantityMax);
            ret.push_back(i);

        }
    }
    return ret;
}