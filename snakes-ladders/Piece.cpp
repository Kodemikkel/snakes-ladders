#include "Game.h"
#include "Piece.h"

#include <QDebug>

extern Game * game;

Piece::Piece(int sprite,
             int posX,
             int posY,
             float scale,
             QGraphicsItem *parent):
    QGraphicsPixmapItem(parent) {

    this->owner = "None";
    this->scale = scale;
    this->posX = posX;
    this->posY = posY;

    this->setSpriteNum(sprite);
}

int Piece::getPosX() {
    return this->posX;
}

int Piece::getPosY() {
    return this->posY;
}

QString Piece::getOwner() {
    return owner;
}

int Piece::getSpriteNum() {
    return this->spriteNum;
}

void Piece::setOwner(QString player) {
    this->owner = player;
}

void Piece::setSpriteNum(int num) {
    this->spriteNum = num;
    this->setPixmap(game->info->setSprite(this->spriteNum,
                                          this->scale));
    setOffset(this->posX, this->posY);
}


// MoveablePiece class - used for pieces on the board
MoveablePiece::MoveablePiece(int sprite,
                             int piecePosX,
                             int piecePosY,
                             float scale,
                             QGraphicsItem *parent):
    Piece(sprite, piecePosX, piecePosY, scale, parent) {

    this->setTileNum(1);
    this->forward = true;
    moveTimer = new Timer();
    connect(this->moveTimer->tTimer, SIGNAL(timeout()), this, SLOT(move()));
}

int MoveablePiece::getTileNum() {
    return this->tileNum;
}

int MoveablePiece::getStepsLeft() {
    return this->stepsLeft;
}

int MoveablePiece::getStepsToTake() {
    return this->stepsToTake;
}

void MoveablePiece::setTileNum(int tileNum) {
    int tileX = game->board->tileRef[tileNum]->getPosX()
            - game->board->tileRef[1]->getPosX();

    int tileY = game->board->tileRef[tileNum]->getPosY()
            - game->board->tileRef[1]->getPosY();

    this->setPos(tileX, tileY);
    this->tileNum = tileNum;
}

void MoveablePiece::setStepsLeft(int steps) {
    this->stepsLeft = steps;
}

void MoveablePiece::setStepsToTake(int stepsToTake) {
    this->stepsToTake = stepsToTake;
}

void MoveablePiece::move() {
    int newTileNum;
    bool finish = false;

    if(this->forward) {
        newTileNum = this->getTileNum() + 1;
    }
    else {
        newTileNum = this->getTileNum() - 1;
    }

    if(this->finalTileNum > game->board->tileRef.size()
            && newTileNum > game->board->tileRef.size()
            && this->forward) {
        this->forward = false;
        newTileNum = newTileNum - 2;
    }

    this->setTileNum(newTileNum);
    this->setStepsLeft(this->getStepsLeft() - 1);

    if(this->getStepsLeft() == 0) {
        QMapIterator<int, int> i(game->ladder->ladders);
        while(i.hasNext()) {
            i.next();
            if(this->getTileNum() == i.key()) {
                this->endTile = i.value();
                QTimer::singleShot(350, this, SLOT(climbLadder()));
            }
        }
        this->moveTimer->resetTime();
        if(this->getTileNum() == 100) {
            game->info->finished[game->info->playerTurn - 1] = true;
            game->timer->pauseTime();
        }
        nextPlayer:
        if(std::all_of(std::begin(game->info->finished),
                       std::end(game->info->finished),
                       [](bool i) {
                            return i;
                        })) {
            finish = true;
            game->displayMainMenu();
        }

        if(this->getStepsToTake() != 6 && !finish) {
            game->info->playerTurn++;
            if(game->info->playerTurn > game->info->getPlayers()) {
                game->info->playerTurn = 1;
            }
            if(game->info->finished[game->info->playerTurn - 1]) {
                goto nextPlayer;
            }
            QString pName = game->info->playerNames[game->info->playerTurn - 1];
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
            game->playersTurn->setText(pName);
        }
    }
}

void MoveablePiece::initMove(int steps) {
    this->setStepsToTake(steps);
    this->setStepsLeft(steps);
    finalTileNum = this->getTileNum() + this->getStepsLeft();
    this->moveTimer->startTimer(350); // Time default 350
    this->forward = true;
}

void MoveablePiece::climbLadder() {
    this->setTileNum(this->endTile);
    this->endTile = NULL;
}
