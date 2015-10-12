#ifndef OBSERVER_H
#define OBSERVER_H

/*!
 * \file observer.h
 * \brief Fichier de classe observateur
 * \author GOF (?)
 */

class SubjectOfObservation;

/*!
 * \brief Classe abstraite de base de tout observateur
 *
 * Classe dont dérive tout écouteur (ou "observateur") du modèle de
 * conception "Observateur / SujetDObservation".
 *
 * \sa SujetDObservation.
 */

class Observer
{
public:

    /*!
     * \brief Méthode virtuelle pure que chaque observateur concret
     * doit implémenter : c'est cette méthode qu'appelle le sujet
     * observé lors d'une notification.
     *
     * \param sdo le sujet d'observation qui notifie un changement.
     * \see SujetDObservation::notifierChangement().
     */
    virtual void refresh(SubjectOfObservation * sob) = 0;

    /*!
     * \brief Destructeur par défaut.
     */
    virtual ~Observer() = default;
};

#endif
