#include "Selection.h"
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

void Container::Selection(int nPlayers, int sPiceNo, QGraphicsItem *parent) {

    //qDebug() << game->info->names[1];

    QString numName = QString::number(nPlayers);

    setRect(0, 0, 672, 110);
    this->setPen(Qt::NoPen); // Removes border

    int posY = this->rect().height() / 2;

    QSignalMapper * subPiece = new QSignalMapper(this);
    QSignalMapper * addPiece = new QSignalMapper(this);
    QSignalMapper * lock = new QSignalMapper(this);

    arrowL = new Arrow(0, posY - 32, 0, this);
    connect(arrowL, SIGNAL(arrowClick()), subPiece, SLOT(map()));
    subPiece->setMapping(arrowL, nPlayers);
    connect(subPiece, SIGNAL(mapped(int)), this, SLOT(changePieceL(int)));

    piece = new Piece(sPiceNo, 96, posY - 32, 1, 1, this);

    arrowR = new Arrow(192, posY - 32, 1, this);
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

void Container::Overview(int ovPlayers, int ovPiceNo, QGraphicsItem * parent) {

    QString ovNumName = QString::number(ovPlayers);

    setRect(0, 0, 622, 110);
    this->setPos(0, 0);
    this->setPen(Qt::NoPen); // Removes border

    int ovPosY = this->rect().height() / 2;

    ovPiece = new Piece(ovPiceNo, 32, ovPosY - 32, 1, 1, this);
    ovTextBox = new TextBox(game->info->names[ovPlayers - 1], false, this);
    ovTextBox->setPos(128, ovPosY - 32);
}

void Container::lock(int nPlayer) {
    if(locked[nPlayer - 1] == false) {
        this->lockBtn->text->setPlainText("Unlock");
        locked[nPlayer - 1] = true;

        QGraphicsTextItem **value = game->info->textBoxMap.value(nPlayer, nullptr);
        game->info->names[nPlayer - 1] =(*value)->toPlainText();

        this->textBox->editable = false;
        this->textBox->playerText->setTextInteractionFlags(Qt::NoTextInteraction);
    }
    else {
        this->lockBtn->text->setPlainText("Lock");
        locked[nPlayer - 1] = false;

        this->textBox->editable = true;
        this->textBox->playerText->setTextInteractionFlags(Qt::TextEditorInteraction);
    }
    qDebug() << game->info->textBoxMap[nPlayer];
    qDebug() << game->info->names[nPlayer - 1];
}

void Container::changePieceL(int nPlayer) {
    qDebug() << game->info->pieces[nPlayer - 1];
    game->info->pieces[nPlayer - 1] = game->info->pieces[nPlayer - 1] - 1;
    qDebug() << game->info->pieces[nPlayer - 1];
}

void Container::changePieceR(int nPlayer) {
    qDebug() << 0%15;
    qDebug() << game->info->pieces[nPlayer - 1];
    game->info->pieces[nPlayer - 1] = game->info->pieces[nPlayer - 1] + 1;
    qDebug() << game->info->pieces[nPlayer - 1];
}
