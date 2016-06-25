#ifndef TEXTBOX_H
#define TEXTBOX_H

#include <QGraphicsTextItem>
#include <QGraphicsRectItem>
#include <QTextCursor>
#include <QObject>

#include <qDebug>
class TextBox: public QObject, public QGraphicsRectItem {
    Q_OBJECT
public:
// Constructors
    TextBox(QString text, bool editable, QGraphicsItem* parent=NULL);

// Getters
    QString getText();
    bool getEditable();

// Setters
    void setEditable(bool edit);

// Public methods
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

// Public members
    QGraphicsTextItem * playerText;

private:
// Private members
    bool editable;
};

#endif // TEXTBOX_H
