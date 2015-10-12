#ifndef CASELABEL_H
#define CASELABEL_H

/*!
 * \file caselabel.h
 * \brief Classe CaseLabel héritant de QLabel
 * \author G41486
 */

#include <QLabel>
#include <QMouseEvent>

/*! \class CaseLabel
 * \brief Classe héritant de QLabel
 *
 *  La classe sert à représenter les étoiles dans l'interface graphique. Elle contient les coordonées
 *  de l'étoile qu'elle représente et implémente un signal clicked() envoyant les coordonnées pour
 *  gérer l'interaction avec la partie.
 */
class CaseLabel : public QLabel
{
    Q_OBJECT
public:
    /*!
     *  \brief Constructeur
     *
     *  Constructeur de la classe CaseLabel
     *
     *  \param x : coordonée ordonnée de l'étoile représentée
     *  \param y : coordonée abscisse de l'étoile représentée
     */
    CaseLabel(int x, int y);

signals:
    /*!
     *  \brief Signal clicked(int x, int y) émit lors du clic sur un CaseLabel
     *
     *  Ce signal est émit par l'objet et envoie les coordonnées de l'étoile représentée
     *
     *  \param x : coordonée ordonnée de l'étoile représentée
     *  \param y : coordonée abscisse de l'étoile représentée
     */
    void clicked(int x, int y);

protected:
    /*!
     *  \brief Méthode appelée lors du clic sur un CaseLabel
     *
     *  Cette méthode est appellée lors du clic sur ce-dernier et envoie le signal clicked(int, int)
     *  si le clic est sur le bouton gauche
     *
     *  \param event : event du clic
     */
    void mousePressEvent(QMouseEvent * event);

private:
    int x;
    int y;
};

#endif // CASELABEL_H
