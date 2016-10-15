#include "Dice.h"
#include "Game.h"
#include <QGraphicsRectItem>

#include <QDebug>

extern Game * game;
Dice::Dice(int spriteNum, QGraphicsItem * parent): QGraphicsPixmapItem(parent) {
    this->setSprite(spriteNum);
    diceTimer = new Timer();
    connect(diceTimer->tTimer, SIGNAL(timeout()), this, SLOT(rollDice()));
}

int Dice::getSprite() {
    return this->spriteNum;
}

int Dice::getDiceSpriteCount() {
    return this->diceSpriteCount;
}

void Dice::setSprite(int spriteNum) {
    this->setPixmap(game->info->setSprite((spriteNum * 2 - 1) + 224, 1, 128, 128));
    this->spriteNum = spriteNum;
}

void Dice::setDiceSpriteCount(int spriteCount) {
    this->diceSpriteCount = spriteCount;
}

void Dice::setPos(int posX, int posY) {
    this->setOffset(posX, posY);
}

void Dice::mousePressEvent(QGraphicsSceneMouseEvent * event) {
    if(game->info->getPause() == false) {
        this->diceTimer->startTimer(85);
        emit diceClicked();
    }
}

void Dice::keyPressEvent(QKeyEvent * event) {
    qDebug() << event;
    qDebug() << event->key();
    if(event->key() == Qt::Key_Space) {
        this->diceTimer->startTimer(85);
        emit diceClicked();
    }
}

void Dice::keyReleaseEvent(QKeyEvent * event) {
    qDebug() << event->key();
}

void Dice::rollDice() {

// Check how many times the dice changed sprite
    if(this->getDiceSpriteCount() < 18) {
        int eyes = game->info->randNum(1, 6);
        this->setSprite(eyes);
    } else {
        QSignalMapper * roller = new QSignalMapper(this);
        connect(this, SIGNAL(diceRolled()), roller, SLOT(map()));
        roller->setMapping(this, this->getSprite());
        this->diceTimer->resetTime();
        connect(roller, SIGNAL(mapped(int)), game->board->players[game->info->playerTurn], SLOT(initMove(int)));
        emit diceRolled();
        disconnect(roller, 0, game->board->players[game->info->playerTurn], 0);
        this->setDiceSpriteCount(0);
    }

// Add one to the "changed sprite" member
    this->setDiceSpriteCount(this->getDiceSpriteCount() + 1);
}
