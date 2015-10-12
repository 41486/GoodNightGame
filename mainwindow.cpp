#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
                                    QMainWindow(parent),
                                    game(nullptr),
                                    centralWidget(new QWidget()), // Widget du contenu de la fenêtre
                                    layout(new QGridLayout()), // Layout de la fenêtre
                                    diceResult(new QLabel(this)), // Label affichant le résultat du dé
                                    activePlayer(new QLabel(this)), // Label affichant le joueur actif
                                    rollDice(new QPushButton("Lancer le dé", this)), // Bouton pour lancer le dé
                                    switchLight(new QPushButton("Interrupteur", this)) // Bouton pour éteindre/allumer la lumière
{
    // Création des pixmap nécessaires
    emptyPixmap = new QPixmap(":img/empty.png");
    dropPixmap = new QPixmap(":img/drop.png");
    noDropPixmap = new QPixmap(":img/no_drop.png");
    starBlackPixmap = new QPixmap(":img/star_black.png");
    starPurplePixmap = new QPixmap(":img/star_purple.png");
    starRedPixmap = new QPixmap(":img/star_red.png");
    starBluePixmap = new QPixmap(":img/star_blue.png");
    starGreenPixmap = new QPixmap(":img/star_green.png");
    starNightPixmap = new QPixmap(":img/star_night.png");
    starDownPixmap = new QPixmap(":img/star_down.png");

    this->setWindowTitle("Bonne nuit !");

    // Mise en place du layout
    centralWidget->setLayout(layout);
    this->setCentralWidget(centralWidget);

    // Ajout du bouton diceResult affichant le résultat du lancé de dé au layout
    layout->addWidget(diceResult, 0, 0, Qt::AlignCenter);

    // Ajout du bouton activePlayer affichant le joueur dont c'est le tour
    layout->addWidget(activePlayer, 0, 5, Qt::AlignCenter);

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
        game->detach(this);
        delete game;
    }

    for (unsigned int i = 0; i < 9; ++i) {
        for (unsigned int j = 0; j < 6; ++j) {
            delete stars[i][j];
        }
        delete stars[i];
    }
    delete stars;

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
}

void MainWindow::newGame() {
    // Si aucune partie était déjà créée, on la supprime avant d'en créer une nouvelle
    if (this->game != nullptr) {
        delete this->game;
    }
    this->game = new Game();

    // On indique à l'objet Game qu'on souhaite l'observer
    this->game->attach(this);

    // On désactive les boutons
    rollDice->setEnabled(false);
    switchLight->setEnabled(false);

    // On lie ensuite les images à la matrice de QLabel : la première colonne contiendra la goute
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

    // On indique à l'objet Game qu'on est prêt à lancer la partie
    this->game->initialize();
}

void MainWindow::updateBoard() {
    // Mise à jour de la dernière valeur du dé, elle n'est affichée qu'à la première phase car elle n'a pas de sens autrement
    if (game->getState() == GameState::PHASE1) {
        this->diceResult->setText(QString::number(game->getLastRoll()));
    } else {
        this->diceResult->setText("/");
    }

    // Mise à jour du joueur actif, il n'est affiché qu'à la phase 1 ou 2 car il n'a pas de sens autrement
    if (game->getState() == GameState::PHASE1 || game->getState() == GameState::PHASE2) {

        this->activePlayer->setText("Joueur actif:\n"+getQStrColor(game->getActivePlayer()));

    }

    // Mise à jour du gagnant, il n'est affiché qu'une fois la partie finie
    if (game->getState() == GameState::FINISHED && game->isLightOn()) {

        this->activePlayer->setText("Gagnant:\n"+getQStrColor(game->getWinner()));

    }

    // Mise à jour de la position de la goute
    unsigned int dropPos = game->getDropPos();
    for (unsigned int i = 0; i < 9; ++i) {
        if (i == dropPos) {
            stars[i][0]->setPixmap(*dropPixmap);
        } else {
            stars[i][0]->setPixmap(*noDropPixmap);
        }
    }

    // On va chercher la matrice des étoiles pour l'afficher
    Star*** board = game->getBoard();

    // On affiche la matrice d'étoile
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
            // Si on vient d'initialiser la partie, on demande le nombre de joueurs
            bool ok = false;
            int  numberOfPlayers = 0;
            while (!ok) {

                numberOfPlayers = QInputDialog::getInt(this, "Nombre de joueurs", "A combien souhaitez-vous jouer ?", 1, 1, 5, 1, &ok);

            }

            // On indique à l'objet Game le nombre de joueur
            game->setNumberOfPlayers(numberOfPlayers);

            // On peut ensuite commencer la partie
            game->start();

            // Une fois la partie commencé on peut activer le bouton pour lancer le dé et que le premier joueur commence
            rollDice->setEnabled(true);
        } else if (game->getState() == GameState::PHASE1) {
            // Rien à faire, les slots gèrent le jeu
        } else if (game->getState() == GameState::WAITING) {
            // Tous les joueurs ont placés leurs étoiles, on active donc le bouton pour allumer la lumière
            rollDice->setEnabled(false);
            // et on désactive le bouton du dé
            switchLight->setEnabled(true);
        } else if (game->getState() == GameState::PHASE2) {
            // On continue sur la phase 2, le dé est toujours inutile
            rollDice->setEnabled(false);
            // On ne peut pas allumer la lumière avant la fin de partie, on désactive le bouton
            switchLight->setEnabled(false);
        } else if (game->getState() == GameState::FINISHED) {
            // Lorsqu'il ne reste qu'une étoile, le bouton pour allumer la lumière est de nouveau disponible
            switchLight->setEnabled(true);
        }
        this->updateBoard();
    }
}

void MainWindow::caseLabelClicked(int x, int y)
{
    // Si on est à la 1er phase et que le bouton pour lancer le dé est désactivé (donc que le dé vient d'être lancé), on peut mettre son étoile
    if (this->game->getState() == GameState::PHASE1 && !this->rollDice->isEnabled()) {
        try {
            this->game->placeStar(y-1);

            if (this->game->getState() == GameState::PHASE1) {
                // Si on est toujours à la phase 1 (que ce n'était pas au dernier tour du dernier joueur), on réactive le bouton pour lancer le dé
                // pour le suivant.
                this->rollDice->setEnabled(true);
            }
        } catch (GameException *e) {
            QMessageBox::critical(this, "Erreur dans le jeu", e->what());
        } catch (BoardException *e) {
            // Si la place sur laquelle on a déjà cliqué est prise, un message nous averti et on recommence
            QMessageBox::critical(this, "Erreur dans le plateau de jeu", e->what());
        }
    // Si on est à la 2ème phase, on va retourner les étoiles une par une.
    } else if (this->game->getState() == GameState::PHASE2) {
        try {
            this->game->turnBackStar(x,y-1);
        } catch (GameException *e) {
            QMessageBox::critical(this, "Erreur dans le jeu", e->what());
        }
    }
}

void MainWindow::rollDiceClicked()
{
    try {
        // On indique à l'objet Game qu'on souhaite lancer le dé
        this->game->rollDice();
        // On désactive le bouton car le joueur va devoir placer son étoile avant que le suivant joue
        this->rollDice->setEnabled(false);
    } catch (GameException *e) {
        QMessageBox::critical(this, "Erreur dans le jeu", e->what());
    }
}

void MainWindow::switchLightClicked()
{
    try {
        // On indique au jeu qu'on souhaite changer l'état de la lumière
        this->game->switchLight();
        if (game->getState() == GameState::FINISHED) {
            // Si on est à la fin du jeu, il faut désactiver le bouton pour ne pas que les utilisateurs jouent avec la lumière
            switchLight->setEnabled(false);
        }
    } catch (GameException *e) {
        QMessageBox::critical(this, "Erreur dans le jeu", e->what());
    }
}
