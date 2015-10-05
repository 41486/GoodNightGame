#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QInputDialog>
#include <QLineEdit>
#include <QString>
#include <iostream>

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

private:
    Game* game;
};

#endif // MAINWINDOW_H
