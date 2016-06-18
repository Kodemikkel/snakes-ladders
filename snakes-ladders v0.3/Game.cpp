#include "Game.h"
#include "Button.h"
#include "Dice.h"
#include "Piece.h"
#include "Arrow.h"
#include "Selection.h"
#include "TextBox.h"
#include <QGraphicsTextItem>
#include <QPixmap>
#include <QFontDatabase>
#include <QImage>
#include <QPainter>
#include <QApplication>
#include <stdlib.h> // rand() -> really large int
#include <QGraphicsRectItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QThread>
#include <QGraphicsTextItem>
#include <QSignalMapper>
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
}

void Game::start() {
    qDebug()<<"Started";
    scene->clear();
    drawGUI();
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
// Clear the screen
    scene->clear();

    QGraphicsRectItem * overviewBox = new QGraphicsRectItem();
    overviewBox->setRect(0, 0, 782, 686);
    scene->addItem(overviewBox);

// Create the playername textbox

    for(int i = 1; i <= players; i++) {
        /*
        TextBox* textBox = new TextBox("Player " + numName);
        Button * lockButton = new Button("Lock selection", 100, 27);
        textBox->setPos(750, 400 * .32 * i);
        lockButton->setPos(1065, 400 * .32 * i);
        scene->addItem(textBox);
        scene->addItem(lockButton);
        */
        Container * selContainer = new Container();
        selContainer->Selection(i);
        selContainer->setPos(50, 70 + 110 * (i - 1));
        scene->addItem(selContainer);
        Container * ovContainer = new Container(overviewBox);
        ovContainer->Overview(i);
        ovContainer->setPos(0, 0 + 110 * (i - 1));
        scene->addItem(ovContainer);
    }

    overviewBox->setPos(818, 70);


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

    qDebug() << "Dice is clicked!";

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

        qDebug() << diceX;

        scene->addItem(dice);

        unsigned long sleep = 500;
        QThread::msleep(sleep);
    }
}

void Game::testSlot() {
    qDebug() << "This test works";
}

void Game::back() {
    displayMainMenu();
}

void Game::drawBoard(int boardPosX, int boardPosY) {

// Array to map the board. Which tile goes where?
    const int boardArray[30][30] {
        0, 0, 4, 0, 0, 4, 0, 0, 4, 0, 0, 4, 0, 0, 4, 0, 0, 4, 0, 0, 4, 0, 0, 4, 0, 0, 4, 0, 0, 4,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
        0, 0, 4, 0, 0, 4, 0, 0, 4, 0, 0, 4, 0, 0, 4, 0, 0, 4, 0, 0, 4, 0, 0, 4, 0, 0, 4, 0, 0, 4,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
        0, 0, 4, 0, 0, 4, 0, 0, 4, 0, 0, 4, 0, 0, 4, 0, 0, 4, 0, 0, 4, 0, 0, 4, 0, 0, 4, 0, 0, 4,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
        0, 0, 4, 0, 0, 4, 0, 0, 4, 0, 0, 4, 0, 0, 4, 0, 0, 4, 0, 0, 4, 0, 0, 4, 0, 0, 4, 0, 0, 4,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
        0, 0, 4, 0, 0, 4, 0, 0, 4, 0, 0, 4, 0, 0, 4, 0, 0, 4, 0, 0, 4, 0, 0, 4, 0, 0, 4, 0, 0, 4,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
        0, 0, 4, 0, 0, 4, 0, 0, 4, 0, 0, 4, 0, 0, 4, 0, 0, 4, 0, 0, 4, 0, 0, 4, 0, 0, 4, 0, 0, 4,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
        0, 0, 4, 0, 0, 4, 0, 0, 4, 0, 0, 4, 0, 0, 4, 0, 0, 4, 0, 0, 4, 0, 0, 4, 0, 0, 4, 0, 0, 4,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
        0, 0, 4, 0, 0, 4, 0, 0, 4, 0, 0, 4, 0, 0, 4, 0, 0, 4, 0, 0, 4, 0, 0, 4, 0, 0, 4, 0, 0, 4,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
        0, 0, 4, 0, 0, 4, 0, 0, 4, 0, 0, 4, 0, 0, 4, 0, 0, 4, 0, 0, 4, 0, 0, 4, 0, 0, 4, 0, 0, 4,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
        0, 0, 4, 0, 0, 4, 0, 0, 4, 0, 0, 4, 0, 0, 4, 0, 0, 4, 0, 0, 4, 0, 0, 4, 0, 0, 4, 0, 0, 4,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3
    };

// Set the sprite positions
    int spriteX[3];
    int spriteY = 0;

// Set the correct number
    int tileNumX = 0;
    int tileNumY = 192;
    int tileNumVal = 0;

// Scale the board - 1 = 64x64
    float scaleX = 0.4375;
    float scaleY = 0.4375;
    float tileNumScaleX = scaleX * 1;
    float tileNumScaleY = scaleY * 1;

    for(int i = 0; i < 30; i++) {
        for(int j = 0; j < 30; j++) {
            switch(boardArray[i][j]) {
                case 0:
                    spriteX[0] = {0};
                    spriteX[1] = {832};
                    spriteX[2] = {NULL};
                    break;
                case 1:
                    spriteX[0] = {64};
                    spriteX[1] = {NULL};
                    spriteX[2] = {NULL};
                    break;
                case 2:
                    spriteX[0] = {128};
                    spriteX[1] = {960};
                    spriteX[2] = {NULL};
                    break;
                case 3:
                    spriteX[0] = {192};
                    spriteX[1] = {960};
                    spriteX[2] = {NULL};
                    break;
                case 4:
                    spriteX[0] = {256};
                    spriteX[1] = {832};
                    spriteX[2] = {NULL};
                    break;
                case 5:
                    spriteX[0] = {320};
                    spriteX[1] = {NULL};
                    spriteX[2] = {NULL};
                    break;
            }
            if(j % 3 == 0) {
                spriteX[2] = 768;
            }
            if(j % 3 == 2) {
                spriteX[2] = 896;
            }

// Create the tile object with the specified properties, and add it to the scene
            for(int k = 0; k < sizeof(spriteX)/sizeof(*spriteX); k++) {
                if(spriteX[k] != NULL || k == 0) {
                    Tile* tile = new Tile(scaleX * 64 * j + boardPosX, scaleY * 64 * i + boardPosY, spriteX[k], spriteY, scaleX, scaleY);
                    if(j % 3 == 0 && spriteX[k] == 960) {
                        tile->drawTileNum(scaleX * 64 * j + boardPosX, scaleY * 64 * i + boardPosY, tileNumX, tileNumY, tileNumScaleX, tileNumScaleY);
                        tileNumX = tileNumX + 64;
                        if(tileNumX == 640) {
                            tileNumX = 0;
                            tileNumY = tileNumY + 64;
                        }
                    }
                    scene->addItem(tile);
                }
            }
        }
    }
}

void Game::drawGUI() {
    drawBoard(30, 30);
    drawDice(); // 1300, 725, 100, 100
}

void Game::drawDice() {
    qDebug() << "Draw Dice";
    int diceX = 0;
    Dice * dice = new Dice(diceX);
    connect(dice, SIGNAL(diceClicked()), this, SLOT(rollDice()));
    scene->addItem(dice);




}


