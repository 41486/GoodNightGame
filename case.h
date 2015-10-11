#ifndef CASE_H
#define CASE_H

#include <iostream>

#include "casestate.h"
#include "color.h"
#include "caseexception.h"

class Case
{
public:
    Case();

    void setStar(Color color);

    void turnBack();
    void empty();

    CaseState getState();
    Color getColor();
private:
    Color color;
    CaseState caseState;
};

#endif // CASE_H
