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
        if (game->getState() == GameState::INITIALIZATION) {
            bool ok = false;
            int numberOfPlayers = 0;
            while (numberOfPlayers < 1 || numberOfPlayers > 5) {
                QString pseudo = QInputDialog::getText(this, "Nombre de joueur", "A combien souhaitez-vous jouer ?", QLineEdit::Normal, QString(), &ok);

                if (ok)
                {
                    QMessageBox::information(this, "Pseudo", "Bonjour " + pseudo + ", ça va ?");
                }
                else
                {
                    QMessageBox::critical(this, "Pseudo", "Vous n'avez pas voulu donner votre nom… snif.");
                }
            }
        }
    }
}
