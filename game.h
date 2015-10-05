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

    void setNumberOfPlayers(int numberOfPlayers);

    GameState getState();

private:
    GameState state;
    int numberOfPlayers;
};

#endif // GAME_H
