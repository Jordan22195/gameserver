#include "item.h"

string Item::packetify()
{
    stringstream ss;
    ss << name << endl << quantity << endl;
}

string Item::getName()
{
    return name;
}