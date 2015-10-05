#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "game.h"

class MainWindow : public QMainWindow, public Observer
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void setGame(Game* game);

private:
    Game* game;
};

#endif // MAINWINDOW_H
