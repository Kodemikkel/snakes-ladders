#include "Game.h"
#include "Arrow.h"
#include "Piece.h"
#include "TextBox.h"
#include "Ladder.h"
#include <ctime>

#include <QGraphicsGridLayout>
#include <QGraphicsWidget>
#include <QGraphicsProxyWidget>
#include <QTextEdit>

#include <QDebug>

extern Game * game;

Game::Game() {
// Create object to store all information about the game
    info = new GameInfo();

// Set up the screen
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    if(this->info->windowed) {
        setFixedSize(1600, 900);
    } else {
        this->showMaximized();
    }

// Set up the scene
    setScene(&scene);

    QImage bkg(":/imgs/background.jpg");
    QImage scaled = bkg.scaled(QSize(1920, 1080));
    scene.setBackgroundBrush(QBrush(scaled));
}

void Game::resizeEvent(QResizeEvent * event) {
    QWidget::resizeEvent(event);
    scene.setSceneRect(0, 0, event->size().width(), event->size().height());
    this->fitInView(scene.sceneRect());
    if(this->width() != 256 && !this->resized) {
        this->resized = true;
        this->displayMainMenu();
    }
}

void Game::displayMainMenu() {
    scene.clear();

    if(this->resized == true) {
    // Create the title text
        this->info->drawTitle();

    // Create the play button
        playButton = new Button("Play", 400, 100);
        int playPosX = 0;
        int playPosY = 300;
        playButton->setPos(playPosX, playPosY);
        connect(playButton, SIGNAL(clicked()), this, SLOT(displayPlayerSelect()));
        scene.addItem(playButton);

    // Create the 'how to play' button
        tutButton = new Button("How to play", 400, 100);
        int tutPosX = this->width() - tutButton->boundingRect().width();
        int tutPosY = 300;
        tutButton->setPos(tutPosX, tutPosY);
        connect(tutButton, SIGNAL(clicked()), this, SLOT(displayPlayerSelect()));
        scene.addItem(tutButton);

    // Create the options button
        optionsButton = new Button("Options", 400, 100);
        int optionsPosX = 0;
        int optionsPosY = 475;
        optionsButton->setPos(optionsPosX, optionsPosY);
        connect(optionsButton, SIGNAL(clicked()), this, SLOT(displayPlayerSelect()));
        scene.addItem(optionsButton);

    // Create the exit button
        quitButton = new Button("Quit", 400, 100);
        int quitPosX = this->width() - quitButton->boundingRect().width();
        int quitPosY = 475;
        quitButton->setPos(quitPosX, quitPosY);
        connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));
        scene.addItem(quitButton);
    }
}

void Game::spawnPiece() {
    float scaleFactor = .7;
    float pieceScale = board->getScale() / scaleFactor;
    Tile * posTile = board->tileRef[1];
    int piecePosX = posTile->getPosX();
    int piecePosY = posTile->getPosY() + (64 * scaleFactor) - (64 * board->getScale());
    for(int i = 1; i <= this->info->getPlayers(); i++) {
        player = new MoveablePiece(this->info->getPiece(i), piecePosX + (i * 6), piecePosY, pieceScale, board);
        this->board->players.insert(i, player);
    }
}

void Game::start() {
    bool locked = true;

// Check that all players have locked their selection
    for(int i = 0; i < info->getPlayers(); i++) {
        if(!info->locked[i]) {
            locked = false;
        }
    }

// Start the game
    if(locked) {
        this->drawGUI();
    }
}

void Game::displayPlayerSelect() {
    scene.clear();

    this->info->playerTurn = 1;

// Create the title text
    info->drawTitle();

// Create all the buttons, and map the signal to the correct slot using QSignalMapper
    signalMapper = new QSignalMapper(this);
    yFactor = 0;

    for(int p = 1; p <= info->getMaxPlayers(); p++) {
        QString playNum = QString::number(p);
        playerButton = new Button(playNum + " players", 400, 100);
        playerButton->setPen(Qt::NoPen);

// TODO fix formula for positioning buttons
        int posX, posY;

        if(p % 2 == 1) {
            posX = 0;
            posY = 300 + yFactor * 175;
        }
        else if(p % 2 == 0) {
            posX = this->width() - playerButton->boundingRect().width();
            posY = 300 + yFactor * 175;
            yFactor++;
        }

        playerButton->setPos(posX, posY);
        connect(playerButton, SIGNAL(clicked()), signalMapper, SLOT(map()));
        signalMapper->setMapping(playerButton, p);
        if(p == info->getMaxPlayers()) {
            connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(displayMatchConfig(int)));
        }
        scene.addItem(playerButton);
    }

// Create the back button
    backButton = new Button("Back", 400, 100);
    int backPosX = this->width() / 2 - backButton->boundingRect().width() / 2;
    int backPosY = this->height() - backButton->boundingRect().height();
    backButton->setPos(backPosX, backPosY);
    connect(backButton, SIGNAL(clicked()), this, SLOT(back()));
    scene.addItem(backButton);
}

void Game::displayMatchConfig(int players) {
    scene.clear();

    this->info->setPlayers(players);

// Create the player selection section
    for(int i = 1; i <= players; i++) {
        selectionMenu = new Container(672, 110);
        scene.addItem(selectionMenu);
        selectionMenu->Selection(i, (i + this->info->getPieceSpriteStart()) - 1);
        selectionMenu->setPos(50, 70 + 110 * (i - 1));

        this->info->tempPlayerNames.insert(i, selectionMenu->pNameTextBox);
        this->info->tempPlayerPieces.insert(i, selectionMenu->piece);
    }

// Create the back button
    backButton = new Button("Back", 400, 100);
    int backPosX = 0;
    int backPosY = this->height() - backButton->boundingRect().height();
    backButton->setPos(backPosX, backPosY);
    connect(backButton, SIGNAL(clicked()), this, SLOT(displayPlayerSelect()));
    scene.addItem(backButton);

// Create the start button
    startButton = new Button("Start", 400, 100);
    int startPosX = this->width() - startButton->boundingRect().width();
    int startPosY = this->height() - startButton->boundingRect().height();;
    startButton->setPos(startPosX, startPosY);
    connect(startButton, SIGNAL(clicked()), this, SLOT(start()));
    scene.addItem(startButton);
}

void Game::back() {
    displayMainMenu();
}

void Game::drawBoard(int boardPosX, int boardPosY) {
    board = new Board();
    board->drawBoard(boardPosX, boardPosY, .4375);

    ladder = new Ladder();

    scene.addItem(board);
    this->spawnPiece();
}

void Game::drawGUI() {
    scene.clear();
    srand(time(NULL));
    drawBoard(30, 30);
    drawDice();
    drawTimer();
    drawPlayerList();

// Create the back button
    backButton = new Button("Back", 400, 100);
    int backPosX = this->width() - backButton->boundingRect().width();
    int backPosY = this->height() - backButton->boundingRect().height();
    backButton->setPos(backPosX, backPosY);
    connect(backButton, SIGNAL(clicked()), this, SLOT(displayPlayerSelect()));
    scene.addItem(backButton);

// Create the pause button
    pauseButton = new Button("||", 192, 88);
    int pausePosX = 900;
    int pausePosY = 170;
    pauseButton->setPos(pausePosX, pausePosY);
    connect(pauseButton, SIGNAL(clicked()), timer, SLOT(pauseTime()));
    scene.addItem(pauseButton);
}

void Game::drawDice() {
    int diceX = 1;
    dice = new Dice(diceX);
    connect(dice, SIGNAL(diceClicked()), dice, SLOT(rollDice()));
    scene.addItem(dice);
}

void Game::drawTimer() {
    timer = new Timer(192, 88, 900, 70);
    timer->startTimer(1000);
    timer->updateDisplay();
    scene.addItem(timer);
}

void Game::drawPlayerList() {
    playerListBox = new QGraphicsRectItem();
    QString turn = QString::number(game->info->playerTurn);
    turn = "Player " + turn + "'s turn";
    playersTurn = new TextBox(turn, false, playerListBox);
    playersTurn->setPos(0, playerListBox->boundingRect().y() - 32);
    playerListBox->setRect(0, 0, 480, 686);
    scene.addItem(playerListBox);

    playerListBox->setPen(Qt::NoPen);

    for(int i = 1; i <= this->info->getPlayers(); i++) {
        Container * playerList = new Container(622, 110, playerListBox);
        int faceNum = this->info->getPiece(i);
        playerList->Overview(i, faceNum);
        playerList->setPos(0, 0 + 110 * (i - 1));

        this->info->locked[i - 1] = false;
    }

    playerListBox->setPos(1120, 70);
}
