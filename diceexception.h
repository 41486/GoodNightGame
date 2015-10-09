#ifndef DICEEXCEPTION_H
#define DICEEXCEPTION_H

#include <exception>

class DiceException : public std::exception
{
public:
    DiceException();

    virtual const char* what() const throw();
};

#endif // DICEEXCEPTION_H
