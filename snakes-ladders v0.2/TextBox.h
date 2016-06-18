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
    TextBox(QString text, QGraphicsItem* parent=NULL);

    void mousePressEvent(QGraphicsSceneMouseEvent *event);

    QString getText();

    QGraphicsTextItem* playerText;
};

#endif // TEXTBOX_H
