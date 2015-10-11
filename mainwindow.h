#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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

#include "caselabel.h"
#include "game.h"
#include "observer.h"

class MainWindow : public QMainWindow, public Observer
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    virtual ~MainWindow();

    virtual void setGame(Game* game);
    virtual void refresh(SubjectOfObservation * sob);

    virtual void updateBoard();

public slots:
    void caseLabelClicked(int x, int y);
    void rollDiceClicked();
    void switchLightClicked();

private:

    QGridLayout* layout;
    QWidget* window;

    QLabel*** stars;

    Game* game;

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

    QLabel *diceResult;
    QPushButton *rollDice;
    QPushButton *switchLight;

};

#endif // MAINWINDOW_H
