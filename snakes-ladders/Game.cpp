#include "Game.h"
#include "Button.h"
#include "Dice.h"
#include "Piece.h"
#include "Arrow.h"
#include "Container.h"
#include "TextBox.h"
#include "Board.h"
#include "GameInfo.h"
#include <QGraphicsTextItem>
#include <QPixmap>
#include <QFontDatabase>
#include <QImage>
#include <QPainter>
#include <QApplication>
#include <QGraphicsRectItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QThread>
#include <QGraphicsTextItem>
#include <QSignalMapper>
#include <stdlib.h> // rand() -> really large int
#include <string>

#include <QDebug>

extern Game * game;
extern Game * drawDice;

Game::Game(QWidget * parent) {
// Set up the screen
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(1600, 900);

// Set up the scene
    scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, 1600, 900);

    QImage bkg(":/imgs/background.jpg");
    QImage scaled = bkg.scaled(QSize(1600, 900));
    scene->setBackgroundBrush(QBrush(scaled));
    setScene(scene);
    info = new GameInfo();
}

void Game::start() {
    bool locked = true;
    for(int i = 1; i < info->players; i++) {
        if(!info->locked[i]) {
            locked = false;
        }
    }
    if(locked) {
        scene->clear();
        drawGUI();
    }
}

void Game::displayMainMenu() {
    scene->clear();
// Create the title text
    QGraphicsTextItem * titleText = new QGraphicsTextItem(QString("Snakes & Ladders"));

    int fontId = QFontDatabase::addApplicationFont(":/fonts/built_titling_bd.ttf");
    QString family = QFontDatabase::applicationFontFamilies(fontId).at(0);
    QFont built(family, 50);
    titleText->setFont(built);

    int txPos = this->width() / 2 - titleText->boundingRect().width() / 2;
    int tyPos = 50;
    titleText->setPos(txPos, tyPos);
    scene->addItem(titleText);

// Create the play button
    Button * playButton = new Button("Play", 400, 100);
    int bxPos = 0;
    int byPos = 300;
    playButton->setPos(bxPos, byPos);
    connect(playButton, SIGNAL(clicked()), this, SLOT(displayPlayerSelect()));
    scene->addItem(playButton);

// Create the 'how to play' button
    Button * tutButton = new Button("How to play", 400, 100);
    int tbxPos = this->width() - tutButton->boundingRect().width();
    int tbyPos = 300;
    tutButton->setPos(tbxPos, tbyPos);
    connect(tutButton, SIGNAL(clicked()), this, SLOT(displayPlayerSelect()));
    scene->addItem(tutButton);

// Create the options button
    Button * opButton = new Button("Options", 400, 100);
    int obxPos = 0;
    int obyPos = 475;
    opButton->setPos(obxPos, obyPos);
    connect(opButton, SIGNAL(clicked()), this, SLOT(displayPlayerSelect()));
    scene->addItem(opButton);

// Create the exit button
    Button * quitButton = new Button("Quit", 400, 100);
    int qbxPos = this->width() - quitButton->boundingRect().width();
    int qbyPos = 475;
    quitButton->setPos(qbxPos, qbyPos);
    connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));
    scene->addItem(quitButton);
}

void Game::displayPlayerSelect() {
// Clear the screen
    scene->clear();

// Create the title text
    QGraphicsTextItem* titleText = new QGraphicsTextItem(QString("Snakes & Ladders"));

    int fontId = QFontDatabase::addApplicationFont(":/fonts/built_titling_bd.ttf");

    QString family = QFontDatabase::applicationFontFamilies(fontId).at(0);
    QFont built(family, 50);
    titleText->setFont(built);

    int txPos = this->width() / 2 - titleText->boundingRect().width() / 2;
    int tyPos = 50;
    titleText->setPos(txPos, tyPos);
    scene->addItem(titleText);

// Integer for storing the max amount of players - default = 6
    int maxPlayers = 6;

// Create all the buttons, and map the signal to the correct slot using QSignalMapper
    QSignalMapper* signalMapper = new QSignalMapper(this);

    for(int p = 1; p <= maxPlayers; p++) {
        QString playNum = QString::number(p);
        Button * pButton = new Button(playNum + " players", 400, 100);

// Array storing the x, y position of the buttons
        int bPos[maxPlayers][2] {
            0, 300,
            0, 475,
            0, 650,
            this->width() - pButton->boundingRect().width(), 300,
            this->width() - pButton->boundingRect().width(), 475,
            this->width() - pButton->boundingRect().width(), 650
        };

        pButton->setPos(bPos[p-1][0], bPos[p-1][1]);
        connect(pButton, SIGNAL(clicked()), signalMapper, SLOT(map()));
        signalMapper->setMapping(pButton, p);
        if(p == maxPlayers) {
            connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(displayMatchConfig(int)));
        }
        scene->addItem(pButton);
    }

// Create the back button
    Button * bckButton = new Button("Back", 400, 100);
    int bcbxPos = 600;
    int bcbyPos = 800;
    bckButton->setPos(bcbxPos, bcbyPos);
    connect(bckButton, SIGNAL(clicked()), this, SLOT(back()));
    scene->addItem(bckButton);
}

void Game::displayMatchConfig(int players) {
    game->info->players = players;

// Clear the screen
    scene->clear();

    int faceNo = 6;

// Create the player selection section
    for(int i = 1; i <= players; i++) {
        selContainer = new Container();
        selContainer->Selection(i, i - 1);
        selContainer->setPos(50, 70 + 110 * (i - 1));
        scene->addItem(selContainer);

        info->textBoxMap.insert(i, &selContainer->textBox->playerText);
        info->piecesMap.insert(i, &selContainer->piece);
    }


// Create the back button
    Button * bckButton = new Button("Back", 400, 100);
    int bcbxPos = 0;
    int bcbyPos = 780;
    bckButton->setPos(bcbxPos, bcbyPos);
    connect(bckButton, SIGNAL(clicked()), this, SLOT(displayPlayerSelect()));
    scene->addItem(bckButton);

// Create the start button
    Button * stButton = new Button("Start", 400, 100);
    int sbxPos = 1200;
    int sbyPos = 780;
    stButton->setPos(sbxPos, sbyPos);
    connect(stButton, SIGNAL(clicked()), this, SLOT(start()));
    scene->addItem(stButton);
}

void Game::rollDice() {
    // scene->removeItem(Game->drawDice());
    int diceX, eyes;

    for(int i = 0; i <= 12; i++) {

        eyes = rand() % 6 + 1;
        switch(eyes) {
            case 1:
                diceX = 0;
                break;
            case 2:
                diceX = 128;
                break;
            case 3:
                diceX = 256;
                break;
            case 4:
                diceX = 384;
                break;
            case 5:
                diceX = 512;
                break;
            case 6:
                diceX = 640;
                break;


        }

        Dice * dice = new Dice(diceX);
        connect(dice, SIGNAL(diceClicked()), this, SLOT(rollDice()));

        scene->addItem(dice);

        unsigned long sleep = 50;
        QThread::msleep(sleep);
    }
}

void Game::testSlot() {
}

void Game::back() {
    displayMainMenu();
}

void Game::drawBoard(int boardPosX, int boardPosY) {
    Board * board = new Board(1, boardPosX, boardPosY, .4375, .4375);
    board->drawBoard();
    scene->addItem(board);
}

void Game::drawGUI() {
    drawBoard(30, 30);
    drawDice(); // 1300, 725, 100, 100

    QGraphicsRectItem * playerListBox = new QGraphicsRectItem();
    playerListBox->setRect(0, 0, 480, 686);
    scene->addItem(playerListBox);

    playerListBox->setPen(Qt::NoPen); // Removes border

    int faceNo = 0;

    for(int i = 1; i <= game->info->players; i++) {
        Container * playerList = new Container(playerListBox);
        playerList->Overview(i, i - 1);
        playerList->setPos(0, 0 + 110 * (i - 1));
    }

    playerListBox->setPos(1120, 70);

    // Create the play button
        Button * backButton = new Button("Back", 400, 100);
        int backxPos = 1200;
        int backyPos = 780;
        backButton->setPos(backxPos, backyPos);
        connect(backButton, SIGNAL(clicked()), this, SLOT(displayPlayerSelect()));
        scene->addItem(backButton);
}

void Game::drawDice() {
    int diceX = 0;
    Dice * dice = new Dice(diceX);
    connect(dice, SIGNAL(diceClicked()), this, SLOT(rollDice()));
    scene->addItem(dice);




}


