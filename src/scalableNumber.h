#ifndef SCALABLE_NUMBER
#define SCALABLE_NUMBER

#include <string>
#include "logger.h"
#include "json.hpp"


using namespace std;



class ScalableNumber
{
    private:
    int level = 1;
    public:
    int base = 1;
    int linearCoefficient = 0;
    int exponetialCoefficient = 1;

    ScalableNumber();

    ScalableNumber(int base, int lin, int exp);

    
    int setScale(int level);

    int get();



    nlohmann::json to_json();





};

#endif