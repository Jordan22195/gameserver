#ifndef ACTIONRESULT
#define ACTIONRESULT

#include <vector>

using namespace std;

struct ActionResult
{
    vector<Item> items;
    int xp = 0;
};

#endif