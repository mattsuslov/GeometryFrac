#ifndef CANVAS_H
#define CANVAS_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QTimer>
#include <QGraphicsSceneMouseEvent>
#include <QCursor>
#include <cmath>
#include "turtle.h"
#include "lsystem.h"
#include <QKeyEvent>

class Canvas : public QObject, public QGraphicsItem
{
public:
    Canvas();

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

    void keyPressEvent(QKeyEvent *event) override;

private:
    int width_, height_;
    int cur_fr = 0;

    QVector<LSystem> fract;
    QVector<Turtle> turtle;
};

#endif // CANVAS_H
