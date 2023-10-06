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

    struct rollResult
    {
        int id;
        int count;

        json to_json()
        {
            json j;
            return j;
        }

    };

class dropTable
{

    public:
    struct entry
    {

        int id;
        double dropChance;
        int quantityMin;
        int quantityMax;
    };
    vector<entry> table;



    void addEntry(int item, double dropChance, int quantity);
    void addEntry(int item, double dropChance, int quantityMin, int quantityMax);
    double getRandomDouble(double min, double max) ;
    int getRandomInt(int min, int max) ;
    vector<rollResult> roll();

};



#endif