#include "TextBox.h"
#include <QFontDatabase>

TextBox::TextBox(QString text, bool editable, QGraphicsItem * parent): QGraphicsRectItem(parent) {
    this->editable = editable;

// Draw the textbox
    setRect(0, 0, 352, 64);
    if(!editable) {
        this->setPen(Qt::NoPen); // Removes border
    }
    else if(editable) {
        QBrush brush;
        brush.setStyle(Qt::SolidPattern);
        brush.setColor(QColor(255, 255, 255, 255));
        setBrush(brush);
    }

// Draw the text
    playerText = new QGraphicsTextItem(text, this);
    int fontId = QFontDatabase::addApplicationFont(":/fonts/built_titling_bd.ttf");

    QString family = QFontDatabase::applicationFontFamilies(fontId).at(0);
    QFont built(family, 25);
    playerText->setFont(built);
    int xPos = 0;
    int yPos = rect().height() / 2 - playerText->boundingRect().height() / 2;
    playerText->setPos(xPos,yPos);
}

void TextBox::mousePressEvent(QGraphicsSceneMouseEvent * event) {
    if(this->editable) {
        this->playerText->setTextInteractionFlags(Qt::TextEditorInteraction);
        this->playerText->setFocus(Qt::MouseFocusReason);
    }
}

