#include "dice.h"

Dice::Dice(int maxValue)
{
    srand((unsigned)time(0));
    this->value = 0;
    this->maxValue = maxValue;
}

void Dice::roll()
{
    this->value = (rand()%6)+1;
}

int Dice::getValue()
{
    if (this->value == 0) {
        throw new DiceException();
    }
    return this->value;
}
