#ifndef GAMEEXCEPTION_H
#define GAMEEXCEPTION_H

/*!
 * \file gameexception.h
 * \brief Classe d'exception lancées par la classe Game
 * \author G41486
 */

#include <exception>

/*! \class GameException
 * \brief Classe d'exception pour la classe Game
 *
 *  La classe est une exception personnalisée lancé par la classe Game
 */
class GameException
{
public:
    /*!
     *  \brief Constructeur
     *
     *  Constructeur de la classe GameException
     *
     *  \param msg : Message détaillant l'exception
     */
    GameException(const char* msg);

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

#endif // GAMEEXCEPTION_H
