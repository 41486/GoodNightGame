#include "board.h"

Board::Board() : numberOfStars(0) {
    cases = new Case*[9];
    for (int i = 0; i<9; ++i) {
        cases[i] = new Case[5];
        for (int j = 0; j<5; ++j) {
            cases[i][j] = Case();
        }
    }
}

void Board::addStar(int x, Color color) {
    int y = 0;
    while (cases[x][y].getState() != CaseState::EMPTY) {
        y++;
    }
    cases[x][y].setStar(color);
    this->numberOfStars++;
    std::cout << this->numberOfStars << std::endl;
}

Case** Board::getBoard() {
    return this->cases;
}

void Board::dropStar(int x, int y) {
    if (cases[x][y].getState() != CaseState::EMPTY) {
        cases[x][y].empty();
        this->numberOfStars--;
        std::cout << this->numberOfStars << std::endl;
    }
}

int Board::getNumberOfStars() {
    return this->numberOfStars;
}
