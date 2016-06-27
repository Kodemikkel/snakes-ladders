#include "Piece.h"
#include "Game.h"

extern Game * game;

Piece::Piece(int sprite, int piecePosX, int piecePosY, float pieceScaleX, float pieceScaleY, QGraphicsItem *parent): QGraphicsPixmapItem(parent) {
    this->owner = "None";
    this->pieceScaleX = pieceScaleX;
    this->pieceScaleY = pieceScaleY;
    this->piecePosX = piecePosX;
    this->piecePosY = piecePosY;

    this->setSpriteNum(sprite);
}

int Piece::getPos() {

}

QString Piece::getOwner() {
    return owner;
}

int Piece::getSpriteNum() {
    return this->spriteNum;
}

void Piece::setOwner(QString player) {
    owner = player;
}

void Piece::setSpriteNum(int num) {
    this->setPixmap(game->info->setSprite(num));
    setOffset(this->piecePosX, this->piecePosY);
    this->spriteNum = num;
}
