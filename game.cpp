#include "game.h"

Game::Game() : numberOfPlayers(0), dice(3), state(GameState::STOPPED), board(), light(true), drop(0), lastRoll(0), colorList(std::vector<Color>()) {
    colorList.push_back(Color::BLACK);
    colorList.push_back(Color::PURPLE);
    colorList.push_back(Color::RED);
    colorList.push_back(Color::GREEN);
    colorList.push_back(Color::BLUE);
}

Game::~Game() {}

void Game::initialize()
{
    if (this->getState() == GameState::STOPPED) {
        // Si le jeu était bien à l'état arrêté, on indique que la partie s'initialise et on notifie les observateurs
        this->state = GameState::INITIALIZED;
        this->notify();
    } else {
        // Sinon on lance une exception
        throw new GameException("Appel à la méthode initialize() au mauvais moment de la partie");
    }
}

void Game::setNumberOfPlayers(int numberOfPlayers)
{
    if (this->getState() == GameState::INITIALIZED) {
        // Si le jeu était bien à l'état initialisé, simule les joueurs absents
        int diceResult;
        for (int j=0; j<3; ++j) {
            for (int i=numberOfPlayers; i<5; ++i) {
                 diceResult = this->dice.roll();
                 this->drop = (this->drop+diceResult)%9;
                 this->board.addStar(this->drop, colorList[i]);
            }
        }
        // Puis on indique le nombre de joueur, le nombre de tours totaux restants et le joueur actif
        this->numberOfPlayers = numberOfPlayers;
        this->numberOfTurnLeft = 3*numberOfPlayers;
        this->activePlayer = 0;
    } else {
        // Sinon on lance une exception
        throw new GameException("Appel à la méthode setNumberOfPlayers() au mauvais moment de la partie");
    }
}

void Game::start()
{
    if (this->getState() == GameState::INITIALIZED) {
        if (this->numberOfPlayers != 0) {
            this->state = GameState::PHASE1;
            this->notify();
        } else {
            throw new GameException("Impossible de démarrer la partie : nombre de joueurs indéfini");
        }
    } else {
        throw new GameException("Appel à la méthode start() au mauvais moment de la partie");
    }
}

void Game::rollDice()
{
    if (this->getState() == GameState::PHASE1) {
        if (numberOfTurnLeft > 0) {
            lastRoll = this->dice.roll();
            this->drop = (this->drop+lastRoll)%9;

            numberOfTurnLeft--;

            this->notify();
        }
    } else {
        throw new GameException("Appel à la méthode rollDice() au mauvais moment de la partie");
    }
}

void Game::placeStar(int x)
{
    try {
        this->board.addStar(drop, x, colorList[activePlayer]);
        activePlayer = (activePlayer+1)%this->numberOfPlayers;
        if (numberOfTurnLeft == 0) {
            this->state = GameState::WAITING;
        }
    } catch (GameException *e) {
        throw;
    }
    this->notify();
}

void Game::switchLight()
{
    if (this->getState() == GameState::WAITING || this->getState() == GameState::FINISHED) {
        this->light = !this->light;

        if (!this->light) {
            this->state = GameState::PHASE2;
        } else {
            Color winnerColor = this->board.getLastColorLeft();

            int i = 0;
            while (colorList[i] != winnerColor) {
                ++i;
            }
            if (i < numberOfPlayers) {
                this->winner = winnerColor;
            } else {
                this->winner = Color::NONE;
            }
        }

        this->notify();
    } else  {
        throw new GameException("Appel à la méthode switchLight() au mauvais moment de la partie");
    }
}

void Game::turnBackStar(int x, int y)
{
    if (this->getState() == GameState::PHASE2) {
        if (this->board.getStar(x,y)->getState() == StarState::FRONT) {
            this->board.turnBackStar(x, y);
            activePlayer = (activePlayer+1)%this->numberOfPlayers;
            if (this->board.getNumberOfStars() == 1) {
                this->state = GameState::FINISHED;
            }
            this->notify();
        }
    } else {
        throw new GameException("Appel à la méthode turnBackStar() au mauvais moment de la partie");
    }
}


GameState Game::getState()
{
    return this->state;
}

Star*** Game::getBoard()
{
    return this->board.getBoard();
}

bool Game::isLightOn()
{
    return this->light;
}

int Game::getDropPos()
{
    return this->drop;
}

int Game::getLastRoll()
{
    return this->lastRoll;
}

Color Game::getActivePlayer()
{
    return this->colorList[activePlayer];
}

Color Game::getWinner()
{
    if (this->getState() == GameState::FINISHED) {
        return this->winner;
    } else {
        throw new GameException("Appel à la méthode getWinner() au mauvais moment de la partie, aucun gagnant encore");
    }
}
