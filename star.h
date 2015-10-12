#ifndef STAR_H
#define STAR_H

/*!
 * \file star.h
 * \brief Classe d'exception lancées par le dé
 * \author G41486
 */

#include <iostream>

#include "starstate.h"
#include "color.h"
#include "starexception.h"

/*! \class Star
 * \brief Classe représentant une étoile
 *
 *  La classe représente les étoiles utilisées dans le jeu. Pour plus de facilité et de clareté
 *  d'implémentation du plateau de jeu, une étoile peut être "vide" : elle n'est pas présente.
 */
class Star
{
public:
    /*!
     *  \brief Constructeur
     *
     *  Constructeur de la classe Star, il crée une étoile vide et sans couleur
     */
    Star();

    /*!
     *  \brief Méthode changeant la face de l'étoile
     *
     *  Méthode retournant l'étoile : elle passera de face à pile ou inversément. Si l'étoile est
     *  vide, la méthode levera une exception StarException.
     */
    void turnBack();

    /*!
     *  \brief Méthode supprimant l'étoile
     *
     *  Méthode définissant l'étoile à vide et sans couleur. Si l'étoile est
     *  vide, la méthode levera une exception StarException.
     */
    void drop();

    /*!
     *  \brief Retourne l'état de l'étoile
     *
     *  Methode retournant l'état de l'étoile
     *
     *  \return Etat de l'étoile : face, pile ou vide
     */
    StarState getState();

    /*!
     *  \brief Retourne la couleur de l'étoile
     *
     *  Methode retournant la couleur de l'étoile (la couleur doit faire partie de l'énumération
     *  Color)
     *
     *  \return Couleur de l'étoile
     */
    Color getColor();

    /*!
     *  \brief Définit la couleur d'une étoile
     *
     *  Méthode appliquant une couleur à l'étoile et passant son état à "face" si ce dernier est
     *  vide au préalable.
     *
     *  \return Couleur de l'étoile
     */
    void setColor(Color color);

private:
    StarState starState;
    Color starColor;

    void setState(StarState state);
};

#endif // STAR_H
