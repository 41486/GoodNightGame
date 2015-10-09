#include "diceexception.h"

DiceException::DiceException() {}

const char* DiceException::what() const throw() {
    return "Le dé n'a pas été lancé";
}
