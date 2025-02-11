
#include <string>
#include "logger.h"
#include "scalableNumber.h"
#include "json.hpp"


using namespace std;


ScalableNumber::ScalableNumber()
{
}



ScalableNumber::ScalableNumber(int base, int lin, int exp)
{
    base = base;
    linearCoefficient = lin;
    exponetialCoefficient = exp;
}

// number = input^exponentialCoefficent + linearCoeffient * input + base;

int ScalableNumber::setScale(int level)
{
    this->level = level;
    return get();
}

int ScalableNumber::get()
{
    if (base < 0) base = 1;
    if (linearCoefficient < 0) linearCoefficient = 1;

    int res = pow(level, exponetialCoefficient) + linearCoefficient * level + base;
    return res;
}



nlohmann::json ScalableNumber::to_json()
{
    nlohmann::json j;
    j["level"] = level;
    j["base"] = base;
    j["linearCoefficient"] = linearCoefficient;
    j["exponetialCoefficient"] = exponetialCoefficient;

    return j;
}



