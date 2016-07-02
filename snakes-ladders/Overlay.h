#ifndef OVERLAY_H
#define OVERLAY_H

#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QMap>
#include <QMouseEvent>
#include <QObject>

class OverlayText: public QGraphicsTextItem {
    Q_OBJECT
public:

// Public constructors
    OverlayText(QGraphicsItem * parent = NULL);

// Public getters


// Public setters


// Public methods


// Public members


// Public events
    void mousePressEvent(QGraphicsSceneMouseEvent * event);

signals:

// Signals
    void pressed();

public slots:

// Public slots


private:

// Private methods


// Private members

protected:

// Protected methods


// Protected members

};

class Overlay: public QObject, public QGraphicsRectItem {
    Q_OBJECT
public:

// Public constructors
    Overlay(QGraphicsItem * parent = NULL);

// Public getters


// Public setters


// Public methods


// Public members


// Public events


signals:

// Signals


public slots:

// Public slots
    void cont();
    void menu();
    void quit();

private:

// Private methods


// Private members
    QMap<int, QString> options;
    OverlayText * text;


protected:

// Protected methods


// Protected members

};

#endif // OVERLAY_H
