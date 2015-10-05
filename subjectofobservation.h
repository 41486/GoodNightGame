/*!
 * \file sujetdobservation.h
 * \brief Définition de la classe SujetDObservation.
 */

#ifndef __SUBJECTOFOBSERVATION__H__
#define __SUBJECTOFOBSERVATION__H__

#include <set>

class Observer;

/*!
 * \brief Classe de base de tout "sujet d'observation"
 *
 * Classe dont dérive toute source d'événement
 * (ou "sujet d'observation") du modèle de conception
 * "Observateur / SujetDObservation".
 *
 * \author GOF (?).
 * \sa Observateur.
 */
class SubjectOfObservation
{
public:

    /*!
     * \brief Destructeur par défaut.
     */
    virtual ~SubjectOfObservation() = default;

    /*!
     * \brief Méthode permettant à un observateur de s'enregistrer
     * comme écouteur du sujet d'observation.
     *
     * \param obs un pointeur vers le candidat observateur.
     */
    virtual void attach(Observer * obs);

    /*!
     * \brief Méthode permettant à un observateur de se retirer de la
     * liste des écouteurs patentés du sujet d'observation.
     *
     * \param obs l'adresse de l'observateur désintéressé.
     */
    virtual void detach(Observer * obs);

protected:

    /*!
     * \brief Constructeur protégé pour éviter l'instanciation.
     */
    SubjectOfObservation() = default;

    /*!
     * \brief Méthode qui se charge de prévenir les observateurs d'un
     * changement d'état du sujet d'observation, en invoquant leur
     * méthode rafraichir.
     *
     * \sa Observateur::rafraichir(SujetDObservation *).
     */
    virtual void notify();

protected:

    /*!
     * \brief Le vecteur d'observateurs enregistrés.
     */
    std::set<Observer*> myObservers;
};

#endif
