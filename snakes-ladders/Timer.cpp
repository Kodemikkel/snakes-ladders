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
    connect(tTimer, SIGNAL(timeout()), this, SLOT(updateTimer()));
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

void Timer::showDisplay(int sizeX, int sizeY, int posX, int posY) {
// Create the wrap around the timer
    setRect(0, 0, sizeX, sizeY);
    setPen(Qt::NoPen);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(QColor(157, 116, 86, 255));
    setBrush(brush);

// Make a font for the time
    QFont font;
    font.setPixelSize(32);
    font.setBold(true);

// Draw the time text
    tTextItem = new QGraphicsTextItem("00:00:00", this);
    tTextItem->setFont(font);
    tPosX = sizeX / 2 - tTextItem->boundingRect().width() / 2;
    tPosY = sizeY / 2 - tTextItem->boundingRect().height() / 2;
    tTextItem->setPos(tPosX, tPosY);

    setPos(posX, posY);
}

void Timer::startTimer(int interval) {
    tTimer->start(interval);
}

void Timer::updateTimer() {
    this->time = this->time + 1000;
    this->tNewTime = tTime->addMSecs(this->time);
}

void Timer::updateDisplay() {
    updateTimer();
    QString tText = tNewTime.toString("hh:mm:ss");
    tTextItem->setPlainText(tText);
}

void Timer::resetTime() {
    tTimer->stop();
    tTime->restart();
    this->time = 0;
}
