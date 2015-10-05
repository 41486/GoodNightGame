#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    this->setWindowTitle("Bonne nuit !");
}

MainWindow::setGame(Game* game) {
    this->game = game;
    game->attach(this);
}

MainWindow::~MainWindow()
{
}
