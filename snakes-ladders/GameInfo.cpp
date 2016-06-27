#include "GameInfo.h"
#include "Game.h"
#include <QDebug>

extern Game * game;

GameInfo::GameInfo() {
    fontDb = new QFontDatabase;
    this->setupBrush();
    this->addFont(":/fonts/built_titling_bd.ttf");
}

QBrush GameInfo::getBrush() {
    return this->brush;
}

int GameInfo::getQuotient(int divident, int divisor) {
    int quotient = 0;
    for(int i = 1; i < divident; i++) {
        if(i % divisor == 0) {
            quotient++;
        }
    }
    return quotient;
}

int GameInfo::getFontNum() {
    return this->fontNum;
}

int GameInfo::getPlayers() {
    return this->players;
}

int GameInfo::getMaxPlayers() {
    return this->maxPlayers;
}

int GameInfo::getPieceSpriteStart() {
    return this->pieceSpriteStart;
}

int GameInfo::getPieceAmount() {
    return this->pieceAmount;
}

bool GameInfo::getPause() {
    return this->pause;
}

void GameInfo::setPlayers(int players) {
    this->players = players;
}

void GameInfo::setMaxPlayers(int maxPlayers) {
    this->maxPlayers = maxPlayers;
}

void GameInfo::setupBrush(QColor color) {
    this->brush.setStyle(Qt::SolidPattern);
    this->brush.setColor(color);
}

void GameInfo::setPieceSpriteStart(int pieceStart) {
    this->pieceSpriteStart = pieceStart;
}

void GameInfo::setPieceAmount(int pieceAmount) {
    this->pieceAmount = pieceAmount;
}

void GameInfo::setPause(bool pause) {
    this->pause = pause;
}

QPixmap GameInfo::setSprite(int spriteNum, float scaleX, float scaleY, int spriteW, int spriteH, QString path) {

// Algorithm for getting sprite coordinates from spriteNum
    int spriteX = ((spriteNum - 1) % 16) * 64;
    int spriteY = this->getQuotient(spriteNum, 16) * 64;

    QRect rect(spriteX, spriteY, spriteW, spriteH);
    QPixmap original(path);
    QPixmap cropped = original.copy(rect);
    QPixmap scaled = cropped.scaled(QSize(spriteW * scaleX, spriteH * scaleY));
    return scaled;
}

void GameInfo::addFont(QString path) {
// Add the font to the database - allowing it to be used multiple places
    this->fontDb->addApplicationFont(path);
}

void GameInfo::drawTitle() {
// Draw the title text
    titleText = new QGraphicsTextItem(QString("Snakes & Ladders"));
    titleText->setFont(this->fontDb->font("Built Titling Rg", 0, 50));

    int titlePosX = game->scene->width() / 2 - titleText->boundingRect().width() / 2;
    int titlePosY = 50;
    titleText->setPos(titlePosX, titlePosY);
    game->scene->addItem(titleText);
}
