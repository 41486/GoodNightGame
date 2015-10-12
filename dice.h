#ifndef DICE_H
#define DICE_H

/*!
 * \file dice.h
 * \brief Classe représentant un dé
 * \author G41486
 */

#include <cstdlib>
#include <ctime>

#include "diceexception.h"

/*! \class Dice
 * \brief Classe représentant un dé
 *
 *  La classe représente un dé d'une valeure maximale définie en paramètre
 *  et qu'on peut lancer autant de fois que voulu
 */
class Dice
{
public:
    /*!
     *  \brief Constructeur
     *
     *  Constructeur de la classe Dice
     *
     *  \param maxValue : valeur maximale que peut prendre le dé
     */
    Dice(int maxValue);

    /*!
     *  \brief Méthode lançant le dé
     *
     *  Méthode générant un nombre alétoire compris entre 1 et maxValue
     *
     *  \return le résultat du lancé
     */
    int roll();

    /*!
     *  \brief Méthode retournant le dernier résultat obtenu avec le lancé de dé
     *
     *  Méthode retournant le dernier résultat obtenu avec le lancé de dé
     *
     *  \return le dernier résultat du lancé de dé
     */
    int getValue();

private:
    int value;
    int maxValue;
};

#endif // DICE_H
