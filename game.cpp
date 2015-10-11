#include "game.h"

Game::Game() : numberOfPlayers(-1), dice(3), state(GameState::STOPPED), board(), light(true), drop(0), colorList(std::vector<Color>()) {
    colorList.push_back(Color::BLACK);
    colorList.push_back(Color::PURPLE);
    colorList.push_back(Color::RED);
    colorList.push_back(Color::GREEN);
    colorList.push_back(Color::BLUE);
}

Game::~Game()
{

}

void Game::initialize()
{
    this->state = GameState::INITIALIZED;
    this->notify();
}

void Game::start()
{
    this->state = GameState::PHASE1;
    this->notify();
}

void Game::rollDice()
{
    if (this->getState() == GameState::PHASE1) {
        if (numberOfTurnLeft > 0) {
            int i = this->dice.roll();
            this->drop = (this->drop+i)%9;

            this->board.addStar(this->drop, colorList[activePlayer]);

            if (activePlayer == this->numberOfPlayers-1) {
                numberOfTurnLeft--;
                if (numberOfTurnLeft == 0) {
                    this->state = GameState::WAITING;
                }
            }
            activePlayer = (activePlayer+1)%this->numberOfPlayers;

            this->notify();
        }
    }
}

void Game::placeStar(int x, int y)
{

}

void Game::switchLight()
{
    this->light = !this->light;

    if (!this->light) {
        this->state = GameState::PHASE2;
        Case** board = this->board.getBoard();
        for (int i = 0; i<9; ++i) {
            for (int j = 0; j<5; ++j) {
                if (board[i][j].getState() == CaseState::FRONT) {
                    board[i][j].turnBack();
                }
            }
        }
    } else {
        Case** board = this->board.getBoard();
        for (int i = 0; i<9; ++i) {
            for (int j = 0; j<5; ++j) {
                if (board[i][j].getState() == CaseState::BACK) {
                    board[i][j].turnBack();
                }
            }
        }
    }

    this->notify();
}

void Game::dropStar(int x, int y)
{
    if (this->getState() == GameState::PHASE2) {
        this->board.dropStar(x, y);
        if (this->board.getNumberOfStars() == 1) {
            this->state = GameState::FINISHED;
        }
        this->notify();
    }
}

void Game::setNumberOfPlayers(int numberOfPlayers)
{
    int diceResult;
    for (int j=0; j<3; ++j) {
        for (int i=numberOfPlayers; i<5; ++i) {
             diceResult = this->dice.roll();
             this->drop = (this->drop+diceResult)%9;
             this->board.addStar(this->drop, colorList[i]);
        }
    }
    this->numberOfPlayers = numberOfPlayers;
    this->numberOfTurnLeft = 3;
    this->activePlayer = 0;
}

GameState Game::getState()
{
    return this->state;
}

Case** Game::getBoard()
{
    return this->board.getBoard();
}

bool Game::getLight()
{
    return this->light;
}

int Game::getDropPos()
{
    return this->drop;
}
