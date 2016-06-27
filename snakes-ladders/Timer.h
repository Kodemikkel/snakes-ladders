#ifndef TIMER_H
#define TIMER_H

#include "TextBox.h"
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QObject>
#include <QTime>
#include <QTimer>


class Timer: public QObject, public QGraphicsRectItem {
    Q_OBJECT
public:
// Constructors
    Timer();
    Timer(int sizeX, int sizeY, int posX, int posY);

// Getters
    int getTime();

// Setters


// Public methods
    void showDisplay(int sizeX, int sizeY, int posX, int posY);

// Public members
    QTimer * tTimer;


public slots:
    void updateTime();
    void updateDisplay();
    void resetTime();
    void startTimer(int interval = 1000);
    void pauseTime();

private:
    QGraphicsTextItem * tTextItem;
    QTime * tTime;
    QTime tNewTime;
    QString tText;

    int time, tPosX, tPosY;
};

#endif // TIMER_H
