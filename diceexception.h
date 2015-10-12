#ifndef DICEEXCEPTION_H
#define DICEEXCEPTION_H

/*!
 * \file diceexception.h
 * \brief Classe d'exception lancées par le dé
 * \author G41486
 */

#include <exception>

/*! \class DiceException
 * \brief Classe d'exception pour la classe Dice
 *
 *  La classe est une exception personnalisée lancé par la classe Dice
 */
class DiceException : public std::exception
{
public:
    /*!
     *  \brief Constructeur
     *
     *  Constructeur de la classe DiceException
     *
     *  \param msg : Message détaillant l'exception
     */
    DiceException(const char* msg);

    /*!
     *  \brief Retourne le message détaillant l'exception
     *
     *  Retourne le message détaillant l'exception et la cause de celle-ci
     *
     *  \return message détaillant l'exception
     */
    virtual const char* what() const throw();

private:
    const char* msg;
};

#endif // DICEEXCEPTION_H
