#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    this->setWindowTitle("Bonne nuit !");
}

MainWindow::~MainWindow()
{
}

void MainWindow::setGame(Game* game) {
    this->game = game;
    this->game->attach(this);
    this->game->initialize();
}

void MainWindow::refresh(SubjectOfObservation * sob) {
    if (sob == game) {
        if (game->getState() == GameState::INITIALIZED) {
            int  numberOfPlayers = QInputDialog::getInt(this, "Nombre de joueur", "A combien souhaitez-vous jouer ?", 1, 1, 5);

            QMessageBox::information(this, "Nombre de joueur", "Vous avez choisi de jouer à " + QString::number(numberOfPlayers) + " joueurs");

            game->setNumberOfPlayers(numberOfPlayers);

            game->start();
        }
    }
}
