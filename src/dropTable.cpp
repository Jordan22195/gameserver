
#include "dropTable.h"

void dropTable::addEntry(int itemId, double dropChance, int quantity)
{
    addEntry(itemId, dropChance, quantity, quantity);
}

void dropTable::addEntry(int itemId, double dropChance, int quantityMin, int quantityMax)
{
    entry e;
    e.id = itemId;
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

vector<rollResult> dropTable::roll()
{
    vector<rollResult> ret;
    for (entry& e : table)
    {
        if(getRandomDouble(0.0, 1.0) <= e.dropChance)
        {
            rollResult r;
            r.id = e.id;
            r.count = getRandomInt(e.quantityMin, e.quantityMax);
            Logger::INFO("Generated loot: %d x%d", r.id, r.count);
            ret.push_back(r);

        }
    }
    return ret;
}