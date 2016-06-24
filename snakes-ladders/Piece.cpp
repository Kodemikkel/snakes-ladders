#include "Piece.h"
#include "Game.h"
#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>

#include <QDebug>

extern Game * game;

// Piece::Piece(int pieceX, int pieceY, int piecePosX, int piecePosY, QGraphicsItem *parent) {

Piece::Piece(int piece, int piecePosX, int piecePosY, float pieceScaleX, float pieceScaleY, QGraphicsItem *parent): QGraphicsPixmapItem(parent) {
    this->owner = "None";
    this->pieceScaleX = pieceScaleX;
    this->pieceScaleY = pieceScaleY;
    this->piecePosX = piecePosX;
    this->piecePosY = piecePosY;

    this->setSpriteNum(piece);
}

int Piece::getPos() {

}

QString Piece::getOwner() {
    return owner;
}

int Piece::getSpriteNum() {
    return spriteNum;
}

void Piece::setOwner(QString player) {
    owner = player;
}

void Piece::setSpriteNum(int num) {

    if(num > 21) {
        num = 0;
    } else if(num < 0) {
        num = 21;
    }
    spriteNum = num;

    int pieceX, pieceY;

    pieceX = num * 64;

    if(num <= 15) {
        pieceY = 64;
    } else {
        pieceX = ((num % 15) - 1) * 64;
        pieceY = 128;
    }

// Draw the piece
    QRect pieceRect(pieceX, pieceY, 64, 64);
    QPixmap original(":/imgs/Spritesheet.png");
    QPixmap cropped = original.copy(pieceRect);
    QPixmap scaled = cropped.scaled(QSize(64 * this->pieceScaleX, 64 * this->pieceScaleY));
    setOffset(this->piecePosX, this->piecePosY);
    setPixmap(scaled);
}
