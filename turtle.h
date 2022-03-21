#ifndef TURTLE_H
#define TURTLE_H

#include <QPainter>
#include "lsystem.h"
#include <QVector2D>
#include <cmath>


class Turtle
{
public:
    Turtle();
    Turtle(long double x, long double y) : beg_coords_(x, y), beg_velocity_(0, 0), angle_(0) {}
    Turtle(QVector2D c) : beg_coords_(c), beg_velocity_(0, 0), angle_(0) {}
    Turtle(QVector2D c, QVector2D v) : beg_coords_(c), beg_velocity_(v), angle_(0) {}
    Turtle(QVector2D c, QVector2D v, long double a) : Turtle(c, v) { set_angle(a); }

    void set_angle(long double a) { angle_ = a; }
    void set_velocity(QVector2D v) { beg_velocity_ = v; }

    void draw(QString instr, QPainter& painter) {
        QVector2D coords_ = beg_coords_;
        velocity_ = beg_velocity_;
        int n = instr.count('F');
        long double blue = 0;
        long double red = 255;
        long double delta = 255.0 / n;
        for (QChar com: instr) {
            if (com == 'F') {
                painter.setPen(QColor(red, 0, blue));
                painter.drawLine(coords_.toPointF(), (coords_ + velocity_).toPointF());
                coords_ += velocity_;
                red -= delta;
                blue += delta;
            } else if (com == 'R') {
                turn(-angle_);
            } else if (com == 'L') {
                turn(angle_);
            }
        }
    }

private:
    void turn(long double a) {
        long double x = velocity_.x();
        long double y = velocity_.y();
        long double l = velocity_.length();
        velocity_.setX(x * std::cosl(a) - y * std::sinl(a));
        velocity_.setY(x * std::sinl(a) + y * std::cosl(a));
    }

    QVector2D beg_coords_;
    QVector2D beg_velocity_;
    QVector2D velocity_;
    long double angle_;
};

#endif // TURTLE_H
