#ifndef GAME_H
#define GAME_H

#include "GameState.h"
#include "subjectofobservation.h"

class Game : public SubjectOfObservation
{
public:
    Game();
    ~Game();

private:
    GameState gameState;
};

#endif // GAME_H
