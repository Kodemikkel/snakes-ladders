#include "Button.h"
#include "Game.h"
#include <QApplication>
#include <QBrush>
#include <QColor>
#include <QGraphicsTextItem>

#include <QDebug>


extern Game * game;

Button::Button(QString name, int w, int h, QGraphicsItem * parent): QGraphicsRectItem(parent) {
// Draw the button
    this->setRect(0, 0, w, h);
    this->setBrush(game->info->getBrush());

// Draw the text
    this->text = new QGraphicsTextItem(name, this);
    int xPos = rect().width() / 2 - text->boundingRect().width() / 2;
    int yPos = rect().height() / 2 - text->boundingRect().height() / 2;
    this->text->setPos(xPos,yPos);

// Allow responding to hovering events
    setAcceptHoverEvents(true);
}

QString Button::getText() {
    return this->text->toPlainText();
}

void Button::setText(QString text) {
    this->text->setPlainText(text);
}

void Button::mousePressEvent(QGraphicsSceneMouseEvent * event) {
    emit clicked();
    QApplication::setOverrideCursor(Qt::ArrowCursor);
}

void Button::hoverEnterEvent(QGraphicsSceneHoverEvent * event) {
    this->setBrush(QColor(212, 158, 113, 255));
    QApplication::setOverrideCursor(Qt::PointingHandCursor);
}

void Button::hoverLeaveEvent(QGraphicsSceneHoverEvent * event) {
    this->setBrush(game->info->getBrush());
    QApplication::setOverrideCursor(Qt::ArrowCursor);
}
