#include "game.h"

Game::Game()
{
    this->state = GameState::STOPPED;
    this->dice = Dice;
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
    this->state = GameState::STARTED;
    this->notify();
}

void Game::setNumberOfPlayers(int numberOfPlayers)
{
    this->numberOfPlayers = numberOfPlayers;
}

GameState Game::getState()
{
    return this->state;
}
