#ifndef BOARDEXCEPTION_H
#define BOARDEXCEPTION_H

/*!
 * \file boardexception.h
 * \brief Classe d'exception lancées par la classe Board
 * \author G41486
 */

#include <exception>

/*! \class BoardException
 * \brief Classe d'exception pour la classe Board
 *
 *  La classe est une exception personnalisée lancé par la classe Board
 */
class BoardException : public std::exception
{
public:
    /*!
     *  \brief Constructeur
     *
     *  Constructeur de la classe BoardException
     *
     *  \param msg : Message détaillant l'exception
     */
    BoardException(const char* msg);

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

#endif // BOARDEXCEPTION_H
