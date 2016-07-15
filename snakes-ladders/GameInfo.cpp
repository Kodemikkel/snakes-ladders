#include "GameInfo.h"
#include "Game.h"
#include "Piece.h"
#include <ctime>
#include <stdlib.h>

#include "json.hpp"
using json = nlohmann::json;

#include <QDebug>

extern Game * game;

GameInfo::GameInfo() {
    fontDb = new QFontDatabase;
    this->setupBrush();
    this->addFont(":/fonts/built_titling_bd.ttf");

    this->file.open("options.json");
    json j;
    j["windowed"] = this->windowed;
    j["theme"] = this->theme;
    j["res"]["16:9"]["1"] = {
        {"Height", 360},
        {"Width", 640}
    };
    j["res"]["16:9"]["2"] = {
        {"Height", 405},
        {"Width", 720}
    };
    j["res"]["16:9"]["3"] = {
        {"Height", 480},
        {"Width", 848}
    };
    j["res"]["16:9"]["4"] = {
        {"Height", 540},
        {"Width", 960}
    };
    j["res"]["16:9"]["5"] = {
        {"Height", 576},
        {"Width", 1024}
    };
    j["res"]["16:9"]["6"] = {
        {"Height", 720},
        {"Width", 1280}
    };
    j["res"]["16:9"]["7"] = {
        {"Height", 768},
        {"Width", 1366}
    };
    j["res"]["16:9"]["8"] = {
        {"Height", 900},
        {"Width", 1600}
    };
    j["res"]["16:9"]["9"] = {
        {"Height", 1080},
        {"Width", 1920}
    };

    if(this->file.is_open()) {
        this->file << j.dump(2);
        this->file.close();
    }
}

GameInfo::~GameInfo() {

}

QBrush GameInfo::getBrush() {
    return this->brush;
}

int GameInfo::getQuotient(int divident, int divisor) {
    int quotient = 0;
    for(int i = 1; i <= divident; i++) {
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

int GameInfo::getPiece(int num) {
    return this->playerPieces.value(num);
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

QPixmap GameInfo::setSprite(int spriteNum, float scale, int spriteW, int spriteH, QString path) {

// Algorithm for getting sprite coordinates from spriteNum
    int spriteX = ((spriteNum - 1) % 16) * 64;
    int spriteY = this->getQuotient(spriteNum - 1, 16) * 64;

    QRect rect(spriteX, spriteY, spriteW, spriteH);
    QPixmap original(path);
    QPixmap cropped = original.copy(rect);
    QPixmap scaled = cropped.scaled(QSize(spriteW * scale, spriteH * scale));
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

    int titlePosX = game->scene.width() / 2 - titleText->boundingRect().width() / 2;
    int titlePosY = 50;
    titleText->setPos(titlePosX, titlePosY);
    game->scene.addItem(titleText);
}

int GameInfo::randNum(int low, int high) {
    if(!srand) {
        srand(time(NULL));
    }
    int divisor = high - low + 1;
    int num = rand() % divisor + low;
    return num;
}
