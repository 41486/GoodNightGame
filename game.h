#ifndef GAME_H
#define GAME_H

#include "subjectofobservation.h"
#include "gamestate.h"

class Game : public SubjectOfObservation
{
public:
    Game();
    ~Game();

    void initialize();
    void start();

    GameState getState();

private:
    GameState state;
};

#endif // GAME_H
