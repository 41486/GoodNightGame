#include "boardexception.h"

BoardException::BoardException(const char* msg) {
    this->msg = msg;
}

const char* BoardException::what() const throw() {
    return this->msg;
}
