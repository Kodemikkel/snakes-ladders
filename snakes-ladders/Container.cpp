#include "Container.h"
#include "Arrow.h"
#include "Button.h"
#include "Piece.h"
#include "TextBox.h"
#include "Game.h"
#include <QHBoxLayout>
#include <QDebug>
#include <QGraphicsRectItem>
#include <QSignalMapper>

extern Game * game;

Container::Container(QGraphicsItem * parent): QGraphicsRectItem(parent) {

}

void Container::Selection(int nPlayers, int sPieceNo, QGraphicsItem *parent) {

    QString numName = QString::number(nPlayers);

    setRect(0, 0, 672, 110);
    this->setPen(Qt::NoPen); // Removes border

    int posY = this->rect().height() / 2;

    QSignalMapper * subPiece = new QSignalMapper(this);
    QSignalMapper * addPiece = new QSignalMapper(this);
    QSignalMapper * lock = new QSignalMapper(this);

    arrowL = new Arrow(0, posY - 32, 0, true, this);
    connect(arrowL, SIGNAL(arrowClick()), subPiece, SLOT(map()));
    subPiece->setMapping(arrowL, nPlayers);
    connect(subPiece, SIGNAL(mapped(int)), this, SLOT(changePieceL(int)));

    piece = new Piece(sPieceNo, 96, posY - 32, 1, 1, this);

    arrowR = new Arrow(192, posY - 32, 1, true, this);
    connect(arrowR, SIGNAL(arrowClick()), addPiece, SLOT(map()));
    addPiece->setMapping(arrowR, nPlayers);
    connect(addPiece, SIGNAL(mapped(int)), this, SLOT(changePieceR(int)));

    textBox = new TextBox(game->info->names[nPlayers - 1], true, this);
    textBox->setPos(288, posY - 32);

    lockBtn = new Button("Lock", 96, 32, this);
    connect(lockBtn, SIGNAL(clicked()), lock, SLOT(map()));
    lock->setMapping(lockBtn, nPlayers);
    connect(lock, SIGNAL(mapped(int)), this, SLOT(lock(int)));
    lockBtn->setPos(672, posY - 16);

}

void Container::Overview(int ovPlayers, int ovPieceNo) {

    QString ovNumName = QString::number(ovPlayers);

    setRect(0, 0, 622, 110);
    this->setPos(0, 0);
    this->setPen(Qt::NoPen); // Removes border

    int ovPosY = this->rect().height() / 2;

    ovPiece = new Piece(ovPieceNo, 32, ovPosY - 32, 1, 1, this);
    ovTextBox = new TextBox(game->info->names[ovPlayers - 1], false, this);
    ovTextBox->setPos(128, ovPosY - 32);
}

bool Container::compareSprites(int sprite1, int sprite2) {
    if(sprite1 == sprite2) {
        return true;
    } else {
        return false;
    }
}

void Container::lock(int nPlayer) {
    // TODO: Make back button less dirty
    if(game->info->locked[nPlayer - 1] == false) {
        qDebug() << "Locked";
        this->lockBtn->text->setPlainText("Unlock");
        game->info->locked[nPlayer - 1] = true;

        QGraphicsTextItem ** value = game->info->textBoxMap.value(nPlayer, nullptr);
        game->info->names[nPlayer - 1] =(*value)->toPlainText();

        this->textBox->setEditable(false);
        this->arrowL->setClickable(false);
        this->arrowR->setClickable(false);

        checkmark(nPlayer);
        game->info->checkmarkMap.insert(nPlayer, checkmarkRect);
    } else {
        qDebug() << "Unlocked";
        this->lockBtn->text->setPlainText("Lock");
        game->info->locked[nPlayer - 1] = false;

        this->textBox->setEditable(true);
        this->arrowL->setClickable(true);
        this->arrowR->setClickable(true);
        QGraphicsPixmapItem * rect = game->info->checkmarkMap[nPlayer];
        delete rect;
    }
}

void Container::changePieceL(int nPlayer) {
pieceCheckerL:
    Piece ** piece = game->info->piecesMap[nPlayer];
    int spriteNum = (*piece)->getSpriteNum() - 1;

    (*piece)->setSpriteNum(spriteNum);
    if(spriteNum < 0) {
        spriteNum = 21;
    }

    for(int i = 1; i <= game->info->players; i++) {
        Piece ** comparePiece = game->info->piecesMap[i];
        int compareSpriteNum = (*comparePiece)->getSpriteNum();

        if(spriteNum == compareSpriteNum && i != nPlayer) {
            goto pieceCheckerL;
        }
    }
}

void Container::changePieceR(int nPlayer) {
pieceCheckerR:
    Piece ** piece = game->info->piecesMap[nPlayer];
    int spriteNum = (*piece)->getSpriteNum() + 1;

    (*piece)->setSpriteNum(spriteNum);
    if(spriteNum > 21) {
        spriteNum = 0;
    }

    for(int i = 1; i <= game->info->players; i++) {
        Piece ** comparePiece = game->info->piecesMap[i];
        int compareSpriteNum = (*comparePiece)->getSpriteNum();
        qDebug() << compareSpriteNum;

        if(spriteNum == compareSpriteNum && i != nPlayer) {
            goto pieceCheckerR;
        }
    }
}

void Container::checkmark(int nPlayer) {
    int posX = 800;
    int posY = 23;
    checkmarkRect = new QGraphicsPixmapItem();
    checkmarkRect->setParentItem(this);
    QRect rect(576, 0, 64, 64);
    QPixmap original(":/imgs/Spritesheet.png");
    QPixmap cropped = original.copy(rect);
    checkmarkRect->setOffset(posX, posY);
    checkmarkRect->setPixmap(cropped);

}
