#include "caseexception.h"

CaseException::CaseException(const char* msg) {
    this->msg = msg;
}

const char* CaseException::what() const throw() {
    return this->msg;
}
