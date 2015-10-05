#include <QApplication>
#include <iostream>

#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow window;
    window.show();

    Game game;
    window.setGame(&game);

    return a.exec();
}
