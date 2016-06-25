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


class Timer: public QWidget, public QGraphicsRectItem {
    Q_OBJECT
public:
    Timer();


// Public members
    //QGraphicsRectItem * tWrap;
    QGraphicsTextItem * tTextItem;
    QTimer * tTimer;
    QTime * tTime;

    int i, tPosX, tPosY;

public slots:
    void showTime();
    void resetTime();

};

#endif // TIMER_H
