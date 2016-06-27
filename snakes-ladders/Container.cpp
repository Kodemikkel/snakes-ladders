#include "Container.h"
#include "Game.h"

extern Game * game;

Container::Container(QGraphicsItem * parent): QGraphicsRectItem(parent) {

}

void Container::Selection(int nPlayers, int sPieceNo, int w, int h, QGraphicsItem *parent) {

    this->setRect(0, 0, w, h);
    this->setPen(Qt::NoPen);

    int contentPosY = this->rect().height() / 2;

// Signalmappers for arrows and buttons
    this->subPieceMapper = new QSignalMapper(this);
    this->addPieceMapper = new QSignalMapper(this);
    this->lockMapper = new QSignalMapper(this);

// Left arrow
    arrowL = new Arrow(0, contentPosY - 32, 0, true, this);
    connect(arrowL, SIGNAL(arrowClick()), subPieceMapper, SLOT(map()));
    subPieceMapper->setMapping(arrowL, nPlayers);
    connect(subPieceMapper, SIGNAL(mapped(int)), this, SLOT(changePieceL(int)));

// Selected piece
    piece = new Piece(sPieceNo, 96, contentPosY - 32, 1, 1, this);

// Right arrow
    arrowR = new Arrow(192, contentPosY - 32, 1, true, this);
    connect(arrowR, SIGNAL(arrowClick()), addPieceMapper, SLOT(map()));
    addPieceMapper->setMapping(arrowR, nPlayers);
    connect(addPieceMapper, SIGNAL(mapped(int)), this, SLOT(changePieceR(int)));

// Textbox for player name
    pNameTextBox = new TextBox(game->info->names[nPlayers - 1], true, this);
    pNameTextBox->setPos(288, contentPosY - 32);

// Lock button
    lockBtn = new Button("Lock", 96, 32, this);
    connect(lockBtn, SIGNAL(clicked()), lockMapper, SLOT(map()));
    lockMapper->setMapping(lockBtn, nPlayers);
    connect(lockMapper, SIGNAL(mapped(int)), this, SLOT(lock(int)));
    lockBtn->setPos(672, contentPosY - 16);
}

void Container::Overview(int ovPlayers, int ovPieceNo, int w, int h) {

    this->setRect(0, 0, w, h);
    this->setPen(Qt::NoPen);

    int ovPosY = this->rect().height() / 2;

// Player piece
    ovPiece = new Piece(ovPieceNo, 32, ovPosY - 32, 1, 1, this);

// Player name
    ovTextBox = new TextBox(game->info->names[ovPlayers - 1], false, this);
    ovTextBox->setPos(128, ovPosY - 32);
}

void Container::checkmark() {
// TODO: Make positioning formula
    int posX = 800;
    int posY = 23;
    checkmarkRect = new QGraphicsPixmapItem();
    checkmarkRect->setParentItem(this);
    checkmarkRect->setOffset(posX, posY);
    checkmarkRect->setPixmap(game->info->setSprite(10));
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

        game->info->names[nPlayer - 1] = game->info->textBoxMap[nPlayer]->getText();

        this->pNameTextBox->setEditable(false);
        this->arrowL->setClickable(false);
        this->arrowR->setClickable(false);

        this->checkmark();
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
        delete checkMark;
        game->info->locked[nPlayer - 1] = false;
    }
}

void Container::changePieceL(int nPlayer) {
// Previous piece
pieceCheckerL:
    Piece * piece = game->info->piecesMap[nPlayer];
    int spriteNum = piece->getSpriteNum() - 1;

    if(spriteNum < game->info->getPieceSpriteStart()) {
        spriteNum = game->info->getPieceSpriteStart() + game->info->getPieceAmount() - 1;
    }
    piece->setSpriteNum(spriteNum);

    for(int i = 1; i <= game->info->getPlayers(); i++) {
        Piece * comparePiece = game->info->piecesMap[i];
        int compareSpriteNum = comparePiece->getSpriteNum();

        if(spriteNum == compareSpriteNum && i != nPlayer) {
            goto pieceCheckerL;
        }
    }
}

void Container::changePieceR(int nPlayer) {
// Next piece
pieceCheckerR:
    Piece * piece = game->info->piecesMap[nPlayer];
    int spriteNum = piece->getSpriteNum() + 1;

    if(spriteNum > game->info->getPieceSpriteStart() + game->info->getPieceAmount() - 1) {
        spriteNum = game->info->getPieceSpriteStart();
    }
    piece->setSpriteNum(spriteNum);

    for(int i = 1; i <= game->info->getPlayers(); i++) {
        Piece * comparePiece = game->info->piecesMap[i];
        int compareSpriteNum = comparePiece->getSpriteNum();

        if(spriteNum == compareSpriteNum && i != nPlayer) {
            goto pieceCheckerR;
        }
    }
}
