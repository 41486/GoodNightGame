#ifndef GAME_H
#define GAME_H

#include <vector>

#include "subjectofobservation.h"
#include "gamestate.h"
#include "dice.h"
#include "board.h"

class Game : public SubjectOfObservation
{
public:
    Game();
    ~Game();

    void initialize();
    void start();

    void rollDice();
    void placeStar(int x, int y);
    void switchLight();
    void dropStar(int x, int y);

    void setNumberOfPlayers(int numberOfPlayers);

    GameState getState();
    Case** getBoard();
    bool getLight();
    int getDropPos();

private:
    int numberOfPlayers;
    int numberOfTurnLeft;
    int activePlayer;

    Dice dice;

    GameState state;

    Board board;

    bool light;

    int drop;

    std::vector<Color> colorList;
};

#endif // GAME_H
