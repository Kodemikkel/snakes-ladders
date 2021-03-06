#include "Game.h"
#include "Arrow.h"
#include "Piece.h"
#include "TextBox.h"
#include "Ladder.h"
#include <ctime>


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
    //QImage scaled = bkg.scaled(QSize(1920, 1080));
    scene.setBackgroundBrush(QBrush(bkg));
}

void Game::resizeEvent(QResizeEvent * event) {
    QWidget::resizeEvent(event);
    scene.setSceneRect(0, 0, event->size().width(), event->size().height());
    this->fitInView(scene.sceneRect());
    if(this->width() != 256 && !this->resized) {
        this->resized = true;
        this->displayMainMenu();
    }

    this->info->scale = (float)this->width() / 3840;
    qDebug() << this->info->scale;
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
        connect(tutButton, SIGNAL(clicked()), this, SLOT(displayHowTo()));
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

void Game::generateList(QStringList list,
                        bool ordered,
                        int posX,
                        int posY,
                        int posYFactor,
                        QGraphicsItem * parent) {
    for(int i = 0; i < list.length(); i++) {
        QString listItemPrefix;
        if(ordered) {
            listItemPrefix = QString::number(i + 1);
            listItemPrefix.append(". ");
        }
        else {
            listItemPrefix = QString("* ");
        }
        QString * listItemText = new QString(list[i]);
        listItemText->prepend(listItemPrefix);
        TextBox * listItem = new TextBox(*listItemText, false, parent);
        listItem->setPos(posX, posY + posYFactor * i);
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

    for(int p = 1; p <= info->getMaxPlayers(); p++) {
        QString playNum = QString::number(p);
        playerButton = new Button(playNum + " players", 400, 100);

        int posX, posY;

        if(p % 2 == 1) {
            posX = 0;
            posY = 300 + (((p - 1) / 2) * 175);
        }
        else if(p % 2 == 0) {
            posX = this->width() - playerButton->boundingRect().width();
            posY = 300 + (((p - 2) / 2) * 175);
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

void Game::displayHowTo() {
    scene.clear();
    this->howToContainer = new Container((this->width() / 2) - 64,
                                         this->height() - 64);
    howToContainer->setPos(this->scene.width() / 2 -
                            this->howToContainer->boundingRect().width() / 2,
                           32);

    this->howToTitle = new QGraphicsTextItem(QString("Instructions"),
                                             howToContainer);
    howToTitle->setFont(this->info->fontDb->font("Built Titling Rg", 0, 40));
    howToTitle->setPos((howToContainer->boundingRect().width() / 2) -
                        howToTitle->boundingRect().width() / 2, 0);

    this->generateList(this->info->instructions, true, 50, 60, 100, howToContainer);
    this->scene.addItem(howToContainer);

// Create the back button
    backButton = new Button("Back", 400, 100);
    int backPosX = 0;
    int backPosY = this->height() - backButton->boundingRect().height();
    backButton->setPos(backPosX, backPosY);
    connect(backButton, SIGNAL(clicked()), this, SLOT(back()));
    scene.addItem(backButton);

// Create the start button
    startButton = new Button("Start", 400, 100);
    int startPosX = this->width() - startButton->boundingRect().width();
    int startPosY = this->height() - startButton->boundingRect().height();;
    startButton->setPos(startPosX, startPosY);
    connect(startButton, SIGNAL(clicked()), this, SLOT(start()));
    scene.addItem(startButton);
}

void Game::displayOptions() {

// TODO: Add options
    scene.clear();

}

void Game::drawBoard(int boardPosX, int boardPosY) {
    board = new Board();
    board->drawBoard(boardPosX, boardPosY, this->info->scale);

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
    int pausePosX = this->board->getBoardWidth() + 60;
    int pausePosY = 170;
    pauseButton->setPos(pausePosX, pausePosY);
    connect(pauseButton, SIGNAL(clicked()), timer, SLOT(pauseTime()));
    scene.addItem(pauseButton);
}

void Game::drawDice() {
    int diceX = 1;
    dice = new Dice(diceX);
    dice->setPos(this->board->getBoardWidth() + 60, (this->board->getBoardHeight() + 30) - dice->boundingRect().height());
    connect(dice, SIGNAL(diceClicked()), dice, SLOT(rollDice()));
    scene.addItem(dice);
}

void Game::drawTimer() {
    timer = new Timer(192, 88, this->board->getBoardWidth() + 60, 70);
    timer->startTimer(1000);
    timer->updateDisplay();
    scene.addItem(timer);
}

void Game::drawPlayerList() {
    playerListBox = new QGraphicsRectItem();
    QString pName = this->info->playerNames[0];
    QString lastChar = pName.right(1);
    QChar charS = 's';
    QChar charX = 'x';
    QChar charZ = 'z';
    if(lastChar == charS || lastChar == charX || lastChar == charZ) {
        pName = pName + "' turn";
    }
    else {
        pName = pName + "'s turn";
    }
    playersTurn = new TextBox(pName, false, playerListBox);
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

        for(int p = 0; p < this->info->getPlayers(); p++) {
            this->info->finished.push_back(false);
        }


    }

    playerListBox->setPos(this->board->getBoardWidth() + 60 + this->timer->boundingRect().width() + 32, 70);
}
