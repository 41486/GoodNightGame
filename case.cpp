#include "case.h"

Case::Case()
{
    this->color = Color::NONE;
    this->caseState = CaseState::EMPTY;
}

void Case::setStar(Color color)
{
    this->color = color;
    this->caseState = CaseState::FRONT;
}

void Case::empty()
{
    this->caseState = CaseState::EMPTY;
    this->color = Color::NONE;
}

void Case::turnBack()
{
    if (this->caseState == CaseState::FRONT) {
        this->caseState = CaseState::BACK;
    } else if (this->caseState == CaseState::BACK) {
        this->caseState = CaseState::FRONT;
    } else {
        throw new CaseException("Aucune étoile ne peut être retournée sur cette case");
    }
}

CaseState Case::getState()
{
    return this->caseState;
}

Color Case::getColor()
{
    return this->color;
}
