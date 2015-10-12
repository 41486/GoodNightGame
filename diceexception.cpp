#include "diceexception.h"

DiceException::DiceException(const char* msg) {
    this->msg = msg;
}

const char* DiceException::what() const throw() {
    return this->msg;
}
