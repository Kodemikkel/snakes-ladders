#include "Selection.h"
#include "Arrow.h"
#include "Button.h"
#include "Piece.h"
#include "TextBox.h"
#include "Game.h"
#include <QHBoxLayout>
#include <QDebug>
#include <QGraphicsRectItem>

extern Game * game;

Container::Container(QGraphicsItem * parent): QGraphicsRectItem(parent) {

}

void Container::Selection(int nPlayers, QGraphicsItem *parent) {

    QString numName = QString::number(nPlayers);

    setRect(0, 0, 672, 110);
    this->setPen(Qt::NoPen); // Removes border

    int pieceX = 0;
    int pieceY = 64;

    int posY = this->rect().height() / 2;

    arrowL = new Arrow(0, posY - 32, 0, this);
    piece = new Piece(pieceX, pieceY, 96, posY - 32, 1, 1, this);
    arrowR = new Arrow(192, posY - 32, 1, this);
    textBox = new TextBox("Player " + numName, true, this);
    textBox->setPos(288, posY - 32);
    lockBtn = new Button("Lock", 96, 32, this);
    lockBtn->setPos(640, posY - 16);

    qDebug() << "Hello?" << rect().width();

}

void Container::Overview(int ovPlayers, QGraphicsItem * parent) {

    QString ovNumName = QString::number(ovPlayers);

    setRect(0, 0, 622, 110);
    this->setPos(0, 0);
    this->setPen(Qt::NoPen); // Removes border

    int ovPieceX = 0;
    int ovPieceY = 64;

    int ovPosY = this->rect().height() / 2;

    ovPiece = new Piece(ovPieceX, ovPieceY, 32, ovPosY - 32, 1, 1, this);
    ovTextBox = new TextBox("Player " + ovNumName, false, this);
    ovTextBox->setPos(128, ovPosY - 32);
}
