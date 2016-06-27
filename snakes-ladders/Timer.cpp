#include "Timer.h"
#include "Game.h"
#include <QBrush>
#include <QDebug>

extern Game * game;

Timer::Timer() {

// Sets time to 0
    tTime = new QTime();
    tTime->setHMS(0, 0, 0, 0);

// Create the timer
    tTimer = new QTimer(this);
    connect(tTimer, SIGNAL(timeout()), this, SLOT(updateTime()));
    this->time = 0;
}

Timer::Timer(int sizeX, int sizeY, int posX, int posY) {

// Sets time to 0
    tTime = new QTime();
    tTime->setHMS(0, 0, 0, 0);

// Create the timer
    tTimer = new QTimer(this);
    connect(tTimer, SIGNAL(timeout()), this, SLOT(updateDisplay()));
    this->time = 0;
    showDisplay(sizeX, sizeY, posX, posY);
}

int Timer::getTime() {
    return this->time;
}

void Timer::showDisplay(int sizeX, int sizeY, int posX, int posY) {

// Draw the display
    this->setRect(0, 0, sizeX, sizeY);
    this->setPen(Qt::NoPen);
    this->setBrush(game->info->getBrush());

// Draw the timer text
    tTextItem = new QGraphicsTextItem("00:00:00", this);
    tTextItem->setFont(game->info->fontDb->font("Built Titling Rg", 0, 32));
    this->tPosX = sizeX / 2 - tTextItem->boundingRect().width() / 2;
    this->tPosY = sizeY / 2 - tTextItem->boundingRect().height() / 2;
    tTextItem->setPos(this->tPosX, this->tPosY);

    this->setPos(posX, posY);
}

void Timer::updateTime() {
    this->time = this->time + 1000;
    this->tNewTime = this->tTime->addMSecs(this->time);
}

void Timer::updateDisplay() {
    updateTime();
    tText = tNewTime.toString("hh:mm:ss");
    tTextItem->setPlainText(tText);
}

void Timer::resetTime() {
    tTimer->stop();
    tTime->restart();
    this->time = 0;
}

void Timer::startTimer(int interval) {
    tTimer->start(interval);
}

void Timer::pauseTime() {
    if(game->info->getPause()) {
        tTimer->start(1000);
        game->info->setPause(false);
        game->pauseButton->setText("||");
    }
    else {
        tTimer->stop();
        game->info->setPause(true);
        game->pauseButton->setText("Start");
    }
}
