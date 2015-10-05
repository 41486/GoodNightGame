/*!
 * \file observateur.h
 * \brief Définition de la classe Observateur.
 */

#ifndef __OBSERVER__H__
#define __OBSERVER__H__

class SubjectOfObservation;

/*!
 * \brief Classe abstraite de base de tout observateur
 *
 * Classe dont dérive tout écouteur (ou "observateur") du modèle de
 * conception "Observateur / SujetDObservation".
 *
 * \author GOF (?).
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
