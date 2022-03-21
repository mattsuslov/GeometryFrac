#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::paintEvent(QPaintEvent *event) {
    QPainter painter(this);

    QMatrix m;
    m.translate(this->width() / 2, this->height() / 2);
    m.scale(1, -1);
    painter.setTransform(QTransform(m));

    LSystem fract("LLLFRFRFRFRFRFRFRF");
    fract.add_rule('F', "FLLFRRFRRFLLF");
    for (int i = 0; i < 5; ++i) {
        fract.next();
    }

    long double len = 150;
    Turtle turtle(-len / 2, -len);
    turtle.set_angle(M_PI / 4);
    turtle.set_velocity(QVector2D(len / pow(3, fract.iter), 0));
    turtle.draw(fract.get_instruction(), painter);
}

