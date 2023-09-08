#include "item.h"

#include "logger.h"

json Item::to_json()
{
    Logger::TRACE("Item::to_json()");
    json j;
    j["name"] = name;
    j["description"] = description;
    j["quantity"] = quantity;
    return j;
}

string Item::getName()
{
    return name;
}