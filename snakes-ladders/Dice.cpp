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
    this->setPixmap(game->info->setSprite((spriteNum * 2 - 1) + 224, 1, 1, 128, 128));
    setOffset(900, 742);
    this->spriteNum = spriteNum;
}

void Dice::setDiceSpriteCount(int spriteCount) {
    this->diceSpriteCount = spriteCount;
}

void Dice::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    this->diceTimer->startTimer(85);
    emit diceClicked();
}

void Dice::rollDice() {
// Check how many times the dice changed sprite
    if(this->getDiceSpriteCount() < 18) {
        int eyes = game->info->randNum(1, 6);
        qDebug() << eyes;
        this->setSprite(eyes);
    } else {
        this->diceTimer->resetTime();
        this->setDiceSpriteCount(0);
    }
// Add one to the "changed sprite" member
    this->setDiceSpriteCount(this->getDiceSpriteCount() + 1);
}
