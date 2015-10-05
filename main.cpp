#include "mainwindow.h"
#include <QApplication>
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    Game* game = new Game;

    w.setGame(game);

    delete game;

    return a.exec();
}
