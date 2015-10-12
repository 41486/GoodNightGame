#ifndef BOARD_H
#define BOARD_H

/*!
 * \file board.h
 * \brief Classe représentant les étoiles posées
 * \author G41486
 */

#include "star.h"
#include "boardexception.h"

#include <vector>

/*! \class Board
 * \brief Classe représentant les étoiles posées
 *
 *  La classe sert à représenter les étoiles posées
 */
class Board
{
public:
    /*!
     *  \brief Constructeur
     *
     *  Constructeur de la classe Board
     */
    Board();
    /*!
     *  \brief Destructeur
     *
     *  Destructeur de la classe Board
     */
    ~Board();


    /*!
     *  \brief Retourne la matrice de pointeurs d'étoiles
     *
     *  Méthode retournant la matrice de pointeurs d'étoiles pour
     *  pouvoir l'afficher via la vue
     *
     *  \return la matrice de pointeurs d'étoiles
     */
    Star*** getBoard();

    /*!
     *  \brief Ajoute une étoile à la matrice
     *
     *  Ajoute une étoile à la plus petite abscisse de l'ordonnée passée en paramètre
     *
     *  \param x : ordonnée à laquelle ajouter l'étoile
     *  \param color : couleur de (faisant partie de l'énumaration Color) de l'étoile
     */
    void addStar(int x, Color color);

    /*!
     *  \brief Ajoute une étoile à la matrice
     *
     *  Ajoute une étoile à la plus petite abscisse de l'ordonnée passée en paramètre
     *
     *  \param x : ordonnée à laquelle ajouter l'étoile
     *  \param color : couleur de (faisant partie de l'énumaration Color) de l'étoile
     */
    void addStar(int x, int y, Color color);

    /*!
     *  \brief Retourne l'étoile
     *
     *  Retourne l'étoile (elle passera de face visible à face cachée ou inversement)
     *
     *  \param x : coordonée ordonnée de l'étoile
     *  \param y : coordonée abscisse de l'étoile
     */
    void turnBackStar(int x, int y);

    /*!
     *  \brief Supprime une étoile
     *
     *  Supprime une étoile (elle passera à l'état vide)
     *
     *  \param x : coordonée ordonnée de l'étoile
     *  \param y : coordonée abscisse de l'étoile
     */
    void dropStar(int x, int y);

    /*!
     *  \brief Retourne l'étoile dont les coordonées sont passées en paramètre
     *
     *  Retourne un pointeur vers l'étoile se trouvant en x,y (0,0 se trouve en haut à gauche)
     *
     *  \param x : coordonée ordonnée de l'étoile
     *  \param y : coordonée abscisse de l'étoile
     *
     *  \return Star* : l'étoile présente aux coordonnées passées en paramètre
     */

    Star* getStar(int x, int y);

    /*!
     *  \brief Retourne le nombre d'étoile présente dans la matrice
     *
     *  Retourne le nombre d'étoile présente dans la matrice (les étoiles ayant le statut "vide" ne
     *  sont pas comptées).
     *
     *  \param x : coordonée ordonnée de l'étoile
     *  \param y : coordonée abscisse de l'étoile
     *
     *  \return int : nombre d'étoile non vide présentes dans la matrice
     */
    int getNumberOfStars();

    /*!
     *  \brief Retourne le nombre d'étoile présente dans la matrice
     *
     *  Retourne le nombre d'étoile présente dans la matrice (les étoiles ayant le statut "vide" ne
     *  sont pas comptées).
     *
     *  \param x : coordonée ordonnée de l'étoile
     *  \param y : coordonée abscisse de l'étoile
     *
     *  \return int : nombre d'étoile non vide présentes dans la matrice
     */
    Color getLastColorLeft();

private:
    Star*** stars;
    int numberOfStars;
};

#endif // BOARD_H
