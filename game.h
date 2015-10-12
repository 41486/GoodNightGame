#ifndef GAME_H
#define GAME_H

/*!
 * \file game.h
 * \brief Fichier de la classe gérant une partie de "Bonne nuit"
 * \author G41486
 */

#include <vector>

#include "subjectofobservation.h"
#include "gamestate.h"
#include "dice.h"
#include "board.h"
#include "gameexception.h"

/*! \class Game
 * \brief Classe gérant le déroulement d'une partie de "Bonne nuit"
 *
 *  La classe gère une partie de "Bonne nuit" de la manière suivante :
 *  - Appel à la méthode initialize() pour signaler à la vue qu'on attend le nombre de joueurs (jeu en GameState INITIALIZED)
 *  - Définition du nombre de joueur avec setNumberOfPlayers(int)
 *  - Appel à la méthode start() pour commencer à jouer (jeu en GameState PHASE1)
 *  - Appel à la méthode rollDice() pour faire jouer chaque joueur chacun à son tour
 *  - Jeu mis en GameState WAITING lorsque tous les joueurs ont joué, en attendant que la lumière s'éteigne
 *  - Lors de l'extinction de la lumière avec switchLight(), le jeu passe en PHASE2
 *  - Appel à la méthode turnBackStar(int, int) pour retourner les étoiles
 *  - Jeu mis en GameState FINISHED lorsqu'il ne reste qu'une étoile à retourner
 *  - Allumage de la lumière à nouveau possible pour découvrir le vainqueur
 */
class Game : public SubjectOfObservation
{
public:
    /*!
     *  \brief Constructeur
     *
     *  Constructeur de la classe Game, il initialise les variables nécessaires
     */
    Game();

    /*!
     *  \brief Déconstructeur
     *
     *  Désaloue la mémoire
     */
    ~Game();

    /*!
     *  \brief Initialise la partie
     *
     *  Méthode initialisant la partie pour signaler à la vue que l'objet attend le nombre de
     *  joueur avant de commencer. Lève une exception GameException si appelée à un autre moment
     */
    void initialize();

    /*!
     *  \brief Définit le nombre de joueur
     *
     *  Méthode permettant d'indiquer le nombre de joueurs (entre 1 et 5) une fois la partie
     *  initialisée. Lève une exception GameException si appelée à un autre moment
     *
     *  \param numberOfPlayers : nombre de joueurs
     */
    void setNumberOfPlayers(int numberOfPlayers);

    /*!
     *  \brief Commence la partie
     *
     *  Méthode permettant de commencer la partie une fois initialisée et le nombre de joueurs
     *  indiqué.
     *  Lève une exception GameException si appelée à un autre moment ou que le nombre de joueur
     *  n'a pas été défini
     */
    void start();

    /*!
     *  \brief Lance le dé
     *
     *  Méthode lançant le dé et faisant appel à la méthode placeStar(int x, Color color) pour placer
     *  une étoile de la couleur du joueur à l'emplacement où est tombé la goute
     */
    void rollDice();

    /*!
     *  \brief Place une étoile sur le plateau
     *
     *  Méthode plaçant une étoile de la couleur du joueur actif à l'ordonnée x passée en paramètre.
     *  Lève une exception GameException si appelée à un autre moment
     *
     *  \param x : ordonnée où placer l'étoile
     *  \param color : couleur (de l'énumération Color) de l'étoile à placer
     */
    void placeStar(int x);

    /*!
     *  \brief Permet d'éteindre ou allumer la lumière
     *
     *  Méthode changeant l'état de la lumière lorsque la partie est en GameState WAITING (fin de
     *  PHASE1) ou lorsque la partie est en GameState FINISHED (pour découvrir la couleur du
     *  gagnant). Lève une exception GameException si appelée à un autre moment.
     */
    void switchLight();

    /*!
     *  \brief Permet de retourner une étoile
     *
     *  Méthode permettant de retourner l'étoile en coordonée x,y lorsque la partie est en GameState
     *  PHASE2. Lève une exception GameException si appelée à un autre moment.
     */
    void turnBackStar(int x, int y);

    /*!
     *  \brief Retourne l'état de la partie
     *
     *  Permet d'en savoir plus sur l'état de la partie : STOPPED, INITIALIZED, PHASE1, WAITING, PHASE2 ou FINISHED
     *
     *  \return Etat de la partie
     */
    GameState getState();

    /*!
     *  \brief Retourne la matrice de pointeurs d'étoiles
     *
     *  Retourne la matrice de pointeurs d'étoiles pour la mise à jour de la vue
     *
     *  \return Matrice de pointeurs d'étoiles
     */
    Star*** getBoard();

    /*!
     *  \brief Retourne l'état de la lumière
     *
     *  Permet de savoir si la lumière est allumée ou éteinte
     *
     *  \return true si la lumière est allumée
     */
    bool isLightOn();

    /*!
     *  \brief Retourne la position de la goute
     *
     *  Permet de savoir sur quelle case se trouve la goute
     *
     *  \return ordonnée de la goute (0 en haut à gauche)
     */
    int getDropPos();

    /*!
     *  \brief Retourne la valeur du dernier lancé de dé
     *
     *  Permet de savoir combien a fait le dé au dernier lancé
     *
     *  \return valeur du dernier lancé de dé
     */
    int getLastRoll();

    /*!
     *  \brief Retourne la couleur du joueur actif (la personne qui doit jouer)
     *
     *  Permet de savoir la couleur du joueur actif (la personne qui doit jouer)
     *
     *  \return couleur du joueur actif (parmis les couleurs de l'énumération Color)
     */
    Color getActivePlayer();

    /*!
     *  \brief Retourne la couleur du joueur gagnant
     *
     *  Permet de savoir la couleur du joueur gagnant
     *
     *  \return couleur du joueur gagnant
     */
    Color getWinner();

private:
    int numberOfPlayers;
    int numberOfTurnLeft;
    int activePlayer;
    Color winner;

    Dice dice;

    GameState state;

    Board board;

    bool light;

    int rollDiceOrPlaceStar; // Attribut permettant de vérifier si le joueur doit lancer le dé ou placer une étoile, non implémenté

    int drop;
    int lastRoll;

    std::vector<Color> colorList;
};

#endif // GAME_H
