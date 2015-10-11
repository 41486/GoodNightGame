#ifndef CASEEXCEPTION_H
#define CASEEXCEPTION_H

#include <exception>

class CaseException : public std::exception
{
public:
    CaseException(const char* msg);

    virtual const char* what() const throw();

private:
    const char* msg;
};

#endif // CASEEXCEPTION_H
