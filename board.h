#ifndef BOARD_H
#define BOARD_H

#include "case.h"

#include <vector>
#include <iostream>

class Board
{
public:
    Board();

    Case** getBoard();

    void addStar(int x, Color color);
    void dropStar(int x, int y);

    int getNumberOfStars();
private:
    Case** cases;
    int numberOfStars;
};

#endif // BOARD_H
