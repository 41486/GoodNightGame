#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
                                    QMainWindow(parent),
                                    game(nullptr),
                                    centralWidget(new QWidget()), // Widget du contenu de la fenêtre
                                    layout(new QGridLayout()), // Layout de la fenêtre
                                    diceResult(new QLabel()), // Label affichant le résultat du dé
                                    rollDice(new QPushButton("Lancer le dé", this)), // Bouton pour lancer le dé
                                    switchLight(new QPushButton("Interrupteur", this)), // Bouton pour éteindre/allumer la lumière
                                    // Création des pixmap nécessaires
                                    emptyPixmap(new QPixmap("img/empty.png")),
                                    dropPixmap(new QPixmap("img/drop.png")),
                                    noDropPixmap( new QPixmap("img/no_drop.png")),
                                    starBlackPixmap(new QPixmap("img/star_black.png")),
                                    starPurplePixmap(new QPixmap("img/star_purple.png")),
                                    starRedPixmap(new QPixmap("img/star_red.png")),
                                    starBluePixmap(new QPixmap("img/star_blue.png")),
                                    starGreenPixmap(new QPixmap("img/star_green.png")),
                                    starNightPixmap(new QPixmap("img/star_night.png")),
                                    starDownPixmap(new QPixmap("img/star_down.png"))
{
    this->setWindowTitle("Bonne nuit !");

    // Mise en place du layout
    centralWidget->setLayout(layout);
    this->setCentralWidget(centralWidget);

    // Ajout du bouton diceResult affichant le résultat du lancé de dé au layout
    layout->addWidget(diceResult, 0, 0, Qt::AlignCenter);

    // Configuration et ajout au layout du bouton permettant de lancer le dé
    rollDice->setEnabled(false);
    layout->addWidget(rollDice, 0, 1, 1, 2);
    QObject::connect(rollDice, SIGNAL(clicked()), this, SLOT(rollDiceClicked()));

    // Configuration et ajout au layout du bouton permettant d'éteindre/allumer la lumière
    switchLight->setEnabled(false);
    layout->addWidget(switchLight, 0, 3, 1, 2);
    QObject::connect(switchLight, SIGNAL(clicked()), this, SLOT(switchLightClicked()));

    // Création du conteneur de la fenêtre, 9x6 QLabel contenant des images avec la première colonne étant des QLabel normaux et les 5 autres des CaseLabel ayant implémenté un signal clicked()
    this->stars = new QLabel**[9];
    for (int i = 0; i<9; ++i) {
        this->stars[i] = new QLabel*[6];
        for (int j = 0; j<6; ++j) {
            if (j == 0) {
                this->stars[i][j] = new QLabel(); // On crée des QLabel pour la première colonne
            } else {
                this->stars[i][j] = new CaseLabel(i,j); // Et des CaseLabel pour les 5 autres colonnes qu'on lie ensuite au slot de la fenêtre pour détecter les clics
                QObject::connect(this->stars[i][j], SIGNAL(clicked(int, int)), this, SLOT(caseLabelClicked(int, int)));
            }
        }
    }

    menuBar()->setNativeMenuBar(false);

    fileMenu = this->menuBar()->addMenu("&Fichier");

    newAction = new QAction("&Nouvelle partie", this);
        fileMenu->addAction(newAction);
    connect(newAction, SIGNAL(triggered()), this, SLOT(newGame()));

    quitAction = new QAction("&Quitter", this);
        fileMenu->addAction(quitAction);
    connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
}

MainWindow::~MainWindow()
{
    if (this->game != nullptr) {
        delete game;
    }

    for (unsigned int i = 0; i < 9; ++i) {
        for (unsigned int j = 0; j < 6; ++j) {
            delete stars[i][j];
        }
        delete stars[i];
    }
    delete stars;

    delete diceResult;
    delete rollDice;
    delete switchLight;

    delete emptyPixmap;
    delete dropPixmap;
    delete noDropPixmap;
    delete starBlackPixmap;
    delete starPurplePixmap;
    delete starRedPixmap;
    delete starBluePixmap;
    delete starGreenPixmap;
    delete starNightPixmap;
    delete starDownPixmap;
    delete layout;

    delete fileMenu;
    delete newAction;
    delete quitAction;
}

void MainWindow::newGame() {
    if (this->game != nullptr) {
        delete this->game;
    }
    this->game = new Game();
    this->game->attach(this);

    diceResult->setText("");
    rollDice->setEnabled(false);
    switchLight->setEnabled(false);

    // On lie ensuite les bonnes images aux bonnes cases : la première colonne contiendra la goute
    for (unsigned int i = 0; i < 9; ++i) {
        stars[i][0]->setPixmap(*noDropPixmap);

        layout->addWidget(stars[i][0], i+1, 0);

        stars[i][0]->show();
    }

    // Les autres colonnes sont remplies avec un motif vide qui sera remplacé par des étoiles en fonction des joueurs
    for (unsigned int i = 0; i < 9; ++i) {
        for (unsigned int j = 0; j < 5; ++j) {
            stars[i][j+1]->setPixmap(*emptyPixmap);

            layout->addWidget(stars[i][j+1], i+1, j+1);

            stars[i][j+1]->show();
        }
    }

    this->game->initialize();
}

void MainWindow::updateBoard() {
    Star*** board = game->getBoard();

    if (game->getState() == GameState::PHASE1) {
        this->diceResult->setText(QString::number(game->getLastRoll()));
    }

    unsigned int dropPos = game->getDropPos();
    for (unsigned int i = 0; i < 9; ++i) {
        if (i == dropPos) {
            stars[i][0]->setPixmap(*dropPixmap);
        } else {
            stars[i][0]->setPixmap(*noDropPixmap);
        }
    }

    for (unsigned int i = 0; i < 9; ++i) {
        for (unsigned int j = 0; j < 5; ++j) {
            if (board[i][j]->getState() == StarState::EMPTY) {
                stars[i][j+1]->setPixmap(*emptyPixmap);
            } else if (board[i][j]->getState() == StarState::FRONT) {
                if (game->isLightOn()) {
                    if (board[i][j]->getColor() == Color::BLACK) {
                        stars[i][j+1]->setPixmap(*starBlackPixmap);
                    } else if (board[i][j]->getColor() == Color::PURPLE) {
                        stars[i][j+1]->setPixmap(*starPurplePixmap);
                    }  else if (board[i][j]->getColor() == Color::RED) {
                        stars[i][j+1]->setPixmap(*starRedPixmap);
                    }  else if (board[i][j]->getColor() == Color::BLUE) {
                        stars[i][j+1]->setPixmap(*starBluePixmap);
                    }  else if (board[i][j]->getColor() == Color::GREEN) {
                        stars[i][j+1]->setPixmap(*starGreenPixmap);
                    }
                } else {
                    stars[i][j+1]->setPixmap(*starNightPixmap);
                }
            } else if (board[i][j]->getState() == StarState::BACK) {
                stars[i][j+1]->setPixmap(*starDownPixmap);
            }
        }
    }
}

void MainWindow::refresh(SubjectOfObservation * sob) {
    if (sob == game) {
        if (game->getState() == GameState::INITIALIZED) {
            bool ok = false;
            int  numberOfPlayers = 0;
            while (!ok) {

                numberOfPlayers = QInputDialog::getInt(this, "Nombre de joueurs", "A combien souhaitez-vous jouer ?", 1, 1, 5, 1, &ok);

            }

            game->setNumberOfPlayers(numberOfPlayers);

            game->start();

            rollDice->setEnabled(true);
        } else if (game->getState() == GameState::PHASE1) {
            // Rien à faire
        } else if (game->getState() == GameState::WAITING) {
            rollDice->setEnabled(false);

            switchLight->setEnabled(true);
        } else if (game->getState() == GameState::PHASE2) {
            rollDice->setEnabled(false);

            switchLight->setEnabled(false);
        } else if (game->getState() == GameState::FINISHED) {
            switchLight->setEnabled(true);
        }
        this->updateBoard();
    }
}

void MainWindow::caseLabelClicked(int x, int y)
{
    try {
        this->game->turnBackStar(x,y-1);
    } catch (GameException *e) {
        // QMessageBox::critical(this, "Erreur dans le jeu", e->what());
        // Rien à afficher car l'utilisateur peut cliquer accidentellement sur une étoile à
        // n'importe quel moment de la partie
    }
}

void MainWindow::rollDiceClicked()
{
    try {
        this->game->rollDice();
    } catch (GameException *e) {
        QMessageBox::critical(this, "Erreur dans le jeu", e->what());
    }
}

void MainWindow::switchLightClicked()
{
    try {
        this->game->switchLight();
        if (game->getState() == GameState::FINISHED) {
            switchLight->setEnabled(false);
        }
    } catch (GameException *e) {
        QMessageBox::critical(this, "Erreur dans le jeu", e->what());
    }
}
