#ifndef MAINWINDOW_H
#define MAINWINDOW_H

/*!
 * \file mainwindow.h
 * \brief Fichier de la classe gérant la vue
 * \author G41486
 */

#include <QApplication>
#include <QMainWindow>
#include <QMessageBox>
#include <QInputDialog>
#include <QPushButton>
#include <QLineEdit>
#include <QString>
#include <iostream>
#include <QLabel>
#include <QPixmap>
#include <QGridLayout>
#include <QEvent>
#include <QMenu>
#include <QMenuBar>

#include "caselabel.h"
#include "game.h"
#include "observer.h"

/*! \class MainWindow
 * \brief Classe de la vue du jeu GoodNightGame
 *
 *  Gère l'affichage et les interactions avec la partie de "Bonne nuit"
 */
class MainWindow : public QMainWindow, public Observer
{
    Q_OBJECT

public:
    /*!
     *  \brief Constructeur
     *
     *  Constructeur de la classe MainWindow. Il charge les images et composants nécessaires à la
     *  fenêtre.
     */
    MainWindow(QWidget *parent = 0);

    /*!
     *  \brief Déconstructeur
     *
     *  Désaloue la mémoire
     */
    virtual ~MainWindow();

    /*!
     *  \brief Méthode appelée par la partie pour mettre à jour la vue
     *
     *  Méthode appelée par la classe Game pour mettre à jour la vue en fonction de l'état de la
     *  partie.
     *
     *  \param sob : objet ayant appelé la méthode
     */
    virtual void refresh(SubjectOfObservation * sob);

    /*!
     *  \brief Méthode mettant à jour le plateau
     *
     *  Méthode demandant le plateau à la classe Game pour mettre la vue à jour (emplacement des
     *  étoiles, de la goute, ...)
     *
     *  \param sob : objet ayant appelé la méthode
     */
    virtual void updateBoard();

public slots:
    /*!
     *  \brief Slot appelé lors du clic sur un CaseLabel contenant une étoile
     *
     *  Méthode demandant à l'attribut Game de retourner l'étoile positionnée en x,y
     *
     *  \param x : ordonnée de l'étoile
     *  \param y : abscisse de l'étoile
     */
    void caseLabelClicked(int x, int y);

    /*!
     *  \brief Slot appelé lors du clic sur le bouton permettant de lancer le dé
     *
     *  Méthode demandant à Game de lancer le dé pour faire joueur le joueur
     */
    void rollDiceClicked();

    /*!
     *  \brief Slot appelé lors du clic sur le bouton permettant d'éteindre/allumer la lumière
     *
     *  Méthode demandant à Game de changer l'état de la lumière. Si GameState de Game est à FINISHED,
     *  on désactive le bouton pour que l'utilisateur ne joue pas avec la lumière.
     */
    void switchLightClicked();

private slots:
    void newGame();

private:

    QLabel*** stars;

    Game* game;

    QWidget* centralWidget;
    QGridLayout* layout;

    QLabel *diceResult;
    QPushButton *rollDice;
    QPushButton *switchLight;

    QPixmap *emptyPixmap;
    QPixmap *dropPixmap;
    QPixmap *noDropPixmap;
    QPixmap *starBlackPixmap;
    QPixmap *starPurplePixmap;
    QPixmap *starRedPixmap;
    QPixmap *starBluePixmap;
    QPixmap *starGreenPixmap;
    QPixmap *starNightPixmap;
    QPixmap *starDownPixmap;

    QMenu *fileMenu;
    QAction *newAction;
    QAction *quitAction;
};

#endif // MAINWINDOW_H
