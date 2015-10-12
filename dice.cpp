#include "dice.h"

Dice::Dice(int maxValue)
{
    srand((unsigned)time(0));
    this->value = 0;
    this->maxValue = maxValue;
}

int Dice::roll()
{
    this->value = (rand()%this->maxValue)+1;
    return this->value;
}

int Dice::getValue()
{
    if (this->value == 0) {
        throw new DiceException("Le dé n'a pas encore été lancé");
    }
    return this->value;
}
