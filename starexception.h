#ifndef STAREXCEPTION_H
#define STAREXCEPTION_H

/*!
 * \file starexception.h
 * \brief Classe d'exception lancées par la classe Star
 * \author G41486
 */

#include <exception>

/*! \class StarException
 * \brief Classe d'exception pour la classe Star
 *
 *  La classe est une exception personnalisée lancé par la classe Star
 */
class StarException : public std::exception
{
public:
    /*!
     *  \brief Constructeur
     *
     *  Constructeur de la classe StarException
     *
     *  \param msg : Message détaillant l'exception
     */
    StarException(const char* msg);

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

#endif // STAREXCEPTION_H
