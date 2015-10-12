#include "board.h"

Board::Board() : numberOfStars(0) {
    stars = new Star**[9];
    for (int i = 0; i<9; ++i) {
        stars[i] = new Star*[5];
        for (int j = 0; j<5; ++j) {
            stars[i][j] = new Star();
        }
    }
}

Board::~Board() {
    for (int i = 0; i<9; ++i) {
        for (int j = 0; j<5; ++j) {
            delete stars[i][j];
        }
        delete stars[i];
    }
    delete stars;
}

void Board::addStar(int x, Color color) {
    int y = 0;
    while (stars[x][y]->getState() != StarState::EMPTY) {
        y++;
    }
    if (y == 5) {
        throw new BoardException("Il n'y a plus de place pour ajouter une étoile ici");
    }
    stars[x][y]->setColor(color);
    this->numberOfStars++;
}

void Board::addStar(int x, int y, Color color) {
    if (stars[x][y]->getState() != StarState::EMPTY) {
        throw new BoardException("Il n'y a pas de place pour ajouter une étoile ici");
    }
    stars[x][y]->setColor(color);
    this->numberOfStars++;
}

Star*** Board::getBoard() {
    return this->stars;
}

void Board::turnBackStar(int x, int y) {
    try {
        stars[x][y]->turnBack();
        this->numberOfStars--;
    } catch (StarException &e) {
        throw;
    }
}

void Board::dropStar(int x, int y) {
    try {
        stars[x][y]->drop();
        this->numberOfStars--;
    } catch (StarException &e) {
        throw;
    }
}

Star* Board::getStar(int x, int y) {
    return stars[x][y];
}

int Board::getNumberOfStars() {
    return this->numberOfStars;
}

Color Board::getLastColorLeft() {
    Color winnerColor = Color::NONE;
    if (this->getNumberOfStars() == 1) {
        for (int i = 0; i<9; ++i) {
            for (int j = 0; j<5; ++j) {
                if(stars[i][j]->getState() == StarState::FRONT) {
                    winnerColor = stars[i][j]->getColor();
                    break;
                }
            }
            if (winnerColor != Color::NONE) {
                break;
            }
        }
    } else {
        throw new BoardException("Il reste plus d'une étoile sur le plateau !");
    }
    return winnerColor;
}
