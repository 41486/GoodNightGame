#include "star.h"

Star::Star() : starState(StarState::EMPTY), starColor(Color::NONE) {}

void Star::drop()
{
    if (this->getState() == StarState::EMPTY) {
        throw new StarException("Il n'y a déjà pas d'étoile assignée à cet objet");
    }
    this->setState(StarState::EMPTY);
    this->setColor(Color::NONE);
}

void Star::turnBack()
{
    if (this->getState() == StarState::FRONT) {
        this->setState(StarState::BACK);
    } else if (this->getState() == StarState::BACK) {
        this->setState(StarState::FRONT);
    } else {
        throw new StarException("Aucune étoile ne peut être retournée dans cet objet");
    }
}

StarState Star::getState()
{
    return this->starState;
}

Color Star::getColor()
{
    return this->starColor;
}

void Star::setState(StarState state)
{
    this->starState = state;
}

void Star::setColor(Color color)
{
    if (this->getState() == StarState::EMPTY) {
        this->setState(StarState::FRONT);
    }
    this->starColor = color;
}

