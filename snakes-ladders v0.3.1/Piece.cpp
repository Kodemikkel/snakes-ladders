#include "Piece.h"
#include "Game.h"
#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>

#include <QDebug>

extern Game * game;

// Piece::Piece(int pieceX, int pieceY, int piecePosX, int piecePosY, QGraphicsItem *parent) {

Piece::Piece(int pieceX, int pieceY, int piecePosX, int piecePosY, int pieceScaleX, int pieceScaleY, QGraphicsItem *parent): QGraphicsPixmapItem(parent) {

    // Draw the piece
    QRect pieceRect(pieceX, pieceY, 64, 64);
    QPixmap original(":/imgs/Spritesheet.png");
    QPixmap cropped = original.copy(pieceRect);
    QPixmap scaled = cropped.scaled(QSize(64 * pieceScaleX, 64 * pieceScaleY));
    setOffset(piecePosX, piecePosY);
    setPixmap(scaled);

    qDebug() << "Piece";
}

int Piece::getPos() {

}

QString Piece::getOwner() {
    return owner;
}

void Piece::setOwner(QString player) {
    owner = player;
}
