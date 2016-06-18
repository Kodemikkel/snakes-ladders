#include "Selection.h"
#include "Arrow.h"
#include "Button.h"
#include "Piece.h"
#include "TextBox.h"
#include "Game.h"
#include <QHBoxLayout>
#include <QDebug>
#include <QGraphicsRectItem>

Selection::Selection(int selPosX, int selPosY, QGraphicsItem * parent): QGraphicsRectItem(parent) {

    setRect(0, 0, 400, 110);

    int pieceX = 0;
    int pieceY = 64;

    //arrowL = new Arrow(0, this);
    //arrowL->setOffset(0, 0);
    //piece = new Piece(pieceX, pieceY, selPosX + 96, selPosY, 1, 1, this);
    //arrowR = new Arrow(selPosX + 192, selPosY, 1, this);
    //textBox = new TextBox("Player 2", this);
    //lockBtn = new Button("Lock", 100, 20, this);

    text = new QGraphicsTextItem("Hello?", this);
    int xPos = 0;
    int yPos = rect().height() / 2 - text->boundingRect().height() / 2;
    text->setPos(xPos,yPos);

}
