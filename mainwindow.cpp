#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), layout(new QGridLayout()), window(new QWidget())
{
    this->setWindowTitle("Bonne nuit !");

    window->setLayout(layout);

    setCentralWidget(window);

    this->diceResult = new QLabel("?");
    layout->addWidget(diceResult, 0, 0, Qt::AlignCenter);

    rollDice = new QPushButton("Lancer le dé", this);
    rollDice->setEnabled(false);
    layout->addWidget(rollDice, 0, 1, 1, 2);
    QObject::connect(rollDice, SIGNAL(clicked()), this, SLOT(rollDiceClicked()));

    switchLight = new QPushButton("Interrupteur", this);
    switchLight->setEnabled(false);
    layout->addWidget(switchLight, 0, 3, 1, 2);
    QObject::connect(switchLight, SIGNAL(clicked()), this, SLOT(switchLightClicked()));

    emptyPixmap = new QPixmap("img/empty.png");
    dropPixmap = new QPixmap("img/drop.png");
    noDropPixmap = new QPixmap("img/no_drop.png");
    starBlackPixmap = new QPixmap("img/star_black.png");
    starPurplePixmap = new QPixmap("img/star_purple.png");
    starRedPixmap = new QPixmap("img/star_red.png");
    starBluePixmap = new QPixmap("img/star_blue.png");
    starGreenPixmap = new QPixmap("img/star_green.png");
    starNightPixmap = new QPixmap("img/star_night.png");
    starDownPixmap = new QPixmap("img/star_down.png");

    this->stars = new QLabel**[9];
    for (int i = 0; i<9; ++i) {
        this->stars[i] = new QLabel*[6];
        for (int j = 0; j<6; ++j) {
            if (j == 0) {
                this->stars[i][j] = new QLabel();
            } else {
                this->stars[i][j] = new CaseLabel(i,j);
                QObject::connect(this->stars[i][j], SIGNAL(clicked(int, int)), this, SLOT(caseLabelClicked(int, int)));
            }
        }
    }

    for (unsigned int i = 0; i < 9; ++i) {
        stars[i][0]->setPixmap(*noDropPixmap);

        layout->addWidget(stars[i][0], i+1, 0);

        stars[i][0]->show();
    }
    for (unsigned int i = 0; i < 9; ++i) {
        for (unsigned int j = 0; j < 5; ++j) {
            stars[i][j+1]->setPixmap(*emptyPixmap);

            layout->addWidget(stars[i][j+1], i+1, j+1);

            stars[i][j+1]->show();
        }
    }
}

MainWindow::~MainWindow()
{
}

void MainWindow::setGame(Game* game) {
    this->game = game;
    this->game->attach(this);
    this->game->initialize();
}

void MainWindow::updateBoard() {
    Case** board = game->getBoard();

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
            if (board[i][j].getState() == CaseState::EMPTY) {
                stars[i][j+1]->setPixmap(*emptyPixmap);
            } else if (board[i][j].getState() == CaseState::FRONT) {
                if (game->getLight()) {
                    if (board[i][j].getColor() == Color::BLACK) {
                        stars[i][j+1]->setPixmap(*starBlackPixmap);
                    } else if (board[i][j].getColor() == Color::PURPLE) {
                        stars[i][j+1]->setPixmap(*starPurplePixmap);
                    }  else if (board[i][j].getColor() == Color::RED) {
                        stars[i][j+1]->setPixmap(*starRedPixmap);
                    }  else if (board[i][j].getColor() == Color::BLUE) {
                        stars[i][j+1]->setPixmap(*starBluePixmap);
                    }  else if (board[i][j].getColor() == Color::GREEN) {
                        stars[i][j+1]->setPixmap(*starGreenPixmap);
                    }
                } else {
                    stars[i][j+1]->setPixmap(*starNightPixmap);
                }
            } else if (board[i][j].getState() == CaseState::BACK) {
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
            this->updateBoard();
        } else if (game->getState() == GameState::WAITING) {
            this->updateBoard();

            rollDice->setEnabled(false);

            switchLight->setEnabled(true);
        } else if (game->getState() == GameState::PHASE2) {
            rollDice->setEnabled(false);

            switchLight->setEnabled(false);

            this->updateBoard();
        } else if (game->getState() == GameState::FINISHED) {
            switchLight->setEnabled(true);

            this->updateBoard();
        }
    }
}

void MainWindow::caseLabelClicked(int x, int y)
{
    this->game->dropStar(x,y-1);
}

void MainWindow::rollDiceClicked()
{
    this->game->rollDice();
}

void MainWindow::switchLightClicked()
{
    this->game->switchLight();
}
