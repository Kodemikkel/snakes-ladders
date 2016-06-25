#include "Timer.h"
#include "Game.h"
#include <QBrush>
#include <QDebug>

extern Game * game;

Timer::Timer() {
// Create the wrap around the timer
    setRect(0, 0, 192, 88);
    setPen(Qt::NoPen);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(QColor(157, 116, 86, 255));
    setBrush(brush);

// Sets time to 0
    tTime = new QTime();
    tTime->setHMS(0, 0, 0, 0);

// Create the timer
    tTimer = new QTimer(this);
    connect(tTimer, SIGNAL(timeout()), this, SLOT(showTime()));
    tTimer->start(1000);
    i = 0;

    QString tText = tTime->toString("hh:mm:ss");

// Make a font for the time
    QFont font;
    font.setPixelSize(32);
    font.setBold(true);

// Draw the time text
    tTextItem = new QGraphicsTextItem("00:00:00", this);
    tTextItem->setFont(font);
    tPosX = 192 / 2 - tTextItem->boundingRect().width() / 2;
    tPosY = 88 / 2 - tTextItem->boundingRect().height() / 2;
    tTextItem->setPos(tPosX, tPosY);

    setPos(900, 70);
}

void Timer::showTime() {
    QTime tNewTime;
    i = i + 1000;
    tNewTime = tTime->addMSecs(i);
    QString tText = tNewTime.toString("hh:mm:ss");
    qDebug() << tText;
    tTextItem->setPlainText(tText);
}

void Timer::resetTime() {
    tTimer->stop();
    tTime->restart();
    i = 0;
}
