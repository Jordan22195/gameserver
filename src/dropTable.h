#ifndef DROPTABLE
#define DROPTABLE

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cctype>
#include <random>
#include <mutex>
#include <queue>
#include <memory>

#include "item.h"
#include "skill.h"
using namespace std;


class dropTable
{

    public:
    struct entry
    {

        Item item;
        double dropChance;
        int quantityMin;
        int quantityMax;
    };
    vector<entry> table;

    void addEntry(Item item, double dropChance, int quantity);
    void addEntry(Item item, double dropChance, int quantityMin, int quantityMax);
    double getRandomDouble(double min, double max) ;
    int getRandomInt(int min, int max) ;
    vector<Item> roll();

};



#endif