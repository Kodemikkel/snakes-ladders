#include "Container.h"
#include "Game.h"

#include <QDebug>

extern Game * game;

Container::Container(int w, int h, QGraphicsItem * parent): QGraphicsRectItem(parent) {
    this->setRect(0, 0, w, h);
//    this->setPen(Qt::NoPen);
}

void Container::Selection(int nPlayers, int sPieceNo, QGraphicsItem *parent) {

    int contentPosY = this->rect().height() / 2;

// Signalmappers for arrows and buttons
    this->subPieceMapper = new QSignalMapper(this);
    this->addPieceMapper = new QSignalMapper(this);
    this->lockMapper = new QSignalMapper(this);

// Left arrow
    arrowL = new Arrow(0, 0, 0, true, this);
    connect(arrowL, SIGNAL(arrowClick()), subPieceMapper, SLOT(map()));
    subPieceMapper->setMapping(arrowL, nPlayers);
    connect(subPieceMapper, SIGNAL(mapped(int)), this, SLOT(changePieceL(int)));

// Selected piece
    piece = new Piece(sPieceNo, 0, 0, 1, this);

// Right arrow
    arrowR = new Arrow(0, 0, 1, true, this);
    connect(arrowR, SIGNAL(arrowClick()), addPieceMapper, SLOT(map()));
    addPieceMapper->setMapping(arrowR, nPlayers);
    connect(addPieceMapper, SIGNAL(mapped(int)), this, SLOT(changePieceR(int)));

// Textbox for player name
    pNameTextBox = new TextBox(game->info->playerNames[nPlayers - 1], true, this);

// Lock button
    lockBtn = new Button("Lock", 96, 32, this);

    connect(lockBtn, SIGNAL(clicked()), lockMapper, SLOT(map()));
    lockMapper->setMapping(lockBtn, nPlayers);
    connect(lockMapper, SIGNAL(mapped(int)), this, SLOT(lock(int)));

    checkmarkRect = new QGraphicsPixmapItem();
    checkmarkRect->setParentItem(this);
    checkmarkRect->setPixmap(game->info->setSprite(10));
    checkmarkRect->hide();

    this->autoPosition();
}

void Container::Overview(int ovPlayers, int ovPieceNo) {

// Player piece
    ovPiece = new Piece(ovPieceNo, 0, 0, 1, this);

// Player name
    ovTextBox = new TextBox(game->info->playerNames[ovPlayers - 1], false, this);

    this->autoPosition();
}

void Container::check(bool checked) {
    if(checked) {
        checkmarkRect->show();
    } else {
        checkmarkRect->hide();
    }
}

void Container::autoPosition() {

// List storing all children
    QList<QGraphicsItem *> list = this->childItems();

    QListIterator<QGraphicsItem *> autoPos(list);
    int maxHeight;
    int xPos = 32;
    int yPos = 0;
    int marginBottom = 64;
    float yPos1 = 0;
        while(autoPos.hasNext()) {

            autoPos.peekNext()->setPos(0, 0);
            int height = autoPos.peekNext()->boundingRect().height();

            if(!autoPos.hasPrevious()) {
                maxHeight = height;
            }

            maxHeight = qMax(maxHeight, height);

            if(autoPos.hasPrevious()) {
                int prevWidth = autoPos.peekPrevious()->boundingRect().width();
                QPointF prevPos = autoPos.peekPrevious()->pos();
                xPos = prevPos.x() + prevWidth + 32;
            }

            loop:
            if(xPos + autoPos.peekNext()->boundingRect().width() + 32 < game->width()) {

                yPos1 = ((yPos + maxHeight / 2)
                         + (autoPos.peekNext()->boundingRect().height() / 2)
                         + (maxHeight / 2)
                         - autoPos.peekNext()->boundingRect().height());
                    autoPos.peekNext()->setPos(xPos,
                                               yPos1);

            }
            else {
                xPos = 32;
                yPos += maxHeight + 32;
                goto loop;
            }
            autoPos.next();
        }
    // Check for overflow
        if(this->boundingRect().width() < this->childrenBoundingRect().width() || this->boundingRect().height() < this->childrenBoundingRect().height()) {

    // If any - prepare scene for geometry change
        this->prepareGeometryChange();

    // And update the geometry
        this->setRect(this->pos().x(),
                      this->pos().y(),
                      this->childrenBoundingRect().width() + 64,
                      this->childrenBoundingRect().height() + marginBottom);
        }
}

bool Container::compareSprites(int sprite1, int sprite2) {

// Method for comparing two sprites (true if equal)
    if(sprite1 == sprite2) {
        return true;
    } else {
        return false;
    }
}

void Container::lock(int nPlayer) {

// Lock selection
    if(game->info->locked[nPlayer - 1] == false) {
        this->lockBtn->setText("Unlock");

        game->info->playerNames[nPlayer - 1] = game->info->tempPlayerNames[nPlayer]->getText();
        game->info->playerPieces[nPlayer] = game->info->tempPlayerPieces[nPlayer]->getSpriteNum();

        this->pNameTextBox->setEditable(false);
        this->arrowL->setClickable(false);
        this->arrowR->setClickable(false);

        this->check(true);
        game->info->checkmarkMap.insert(nPlayer, checkmarkRect);
        game->info->locked[nPlayer - 1] = true;
    }

// Unlock selection
    else {
        this->lockBtn->setText("Lock");

        this->pNameTextBox->setEditable(true);
        this->arrowL->setClickable(true);
        this->arrowR->setClickable(true);
        checkMark = game->info->checkmarkMap[nPlayer];
        this->check(false);
        game->info->locked[nPlayer - 1] = false;
    }
}

void Container::changePieceL(int nPlayer) {

// Previous piece
pieceCheckerL:
    Piece * piece = game->info->tempPlayerPieces.value(nPlayer);
    int spriteNum = piece->getSpriteNum() - 1;

    if(spriteNum < game->info->getPieceSpriteStart()) {
        spriteNum = game->info->getPieceSpriteStart() + game->info->getPieceAmount() - 1;
    }
    piece->setSpriteNum(spriteNum);

    for(int i = 1; i <= game->info->getPlayers(); i++) {
        Piece * comparePiece = game->info->tempPlayerPieces.value(i);
        int compareSpriteNum = comparePiece->getSpriteNum();

        if(spriteNum == compareSpriteNum && i != nPlayer) {
            goto pieceCheckerL;
        }
    }
}

void Container::changePieceR(int nPlayer) {

// Next piece
pieceCheckerR:
    Piece * piece = game->info->tempPlayerPieces.value(nPlayer);
    int spriteNum = piece->getSpriteNum() + 1;

    if(spriteNum > game->info->getPieceSpriteStart() + game->info->getPieceAmount() - 1) {
        spriteNum = game->info->getPieceSpriteStart();
    }
    piece->setSpriteNum(spriteNum);

    for(int i = 1; i <= game->info->getPlayers(); i++) {
        Piece * comparePiece = game->info->tempPlayerPieces.value(i);
        int compareSpriteNum = comparePiece->getSpriteNum();

        if(spriteNum == compareSpriteNum && i != nPlayer) {
            goto pieceCheckerR;
        }
    }
}
