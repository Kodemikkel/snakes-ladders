#ifndef TIMER_H
#define TIMER_H

#include "TextBox.h"
#include <QTimer>
#include <QObject>
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QTimer>
#include <QTime>
#include <QWidget>
#include <QThread>


class Timer: public QObject, public QGraphicsRectItem {
    Q_OBJECT
public:
// Constructors
    Timer();
    Timer(int sizeX, int sizeY, int posX, int posY);

// Getters


// Setters


// Public methods
    void showDisplay(int sizeX, int sizeY, int posX, int posY);

// Public members
    QGraphicsTextItem * tTextItem;
    QTimer * tTimer;
    QTime * tTime;
    QTime tNewTime;

    int time, tPosX, tPosY;

public slots:
    void updateTimer();
    void updateDisplay();
    void resetTime();
    void startTimer(int interval);
};

#endif // TIMER_H
