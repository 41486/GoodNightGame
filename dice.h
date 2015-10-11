#ifndef DICE_H
#define DICE_H

#include <cstdlib>
#include <ctime>

#include "diceexception.h"

class Dice
{
    int value;
    int maxValue;

public:
    Dice(int maxValue);

    int roll();

    int getValue();
};

#endif // DICE_H
