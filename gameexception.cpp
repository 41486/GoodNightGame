#include "gameexception.h"

GameException::GameException(const char* msg) {
    this->msg = msg;
}

const char* GameException::what() const throw() {
    return this->msg;
}
