#include "starexception.h"

StarException::StarException(const char* msg) {
    this->msg = msg;
}

const char* StarException::what() const throw() {
    return this->msg;
}
