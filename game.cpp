#include "game.h"

Game::Game()
{
    this->state = GameState::STOPPED;
}

Game::~Game()
{

}

void Game::initialize()
{
    this->state = GameState::INITIALIZATION;
    this->notify();
}

GameState Game::getState()
{
    return this->state;
}
