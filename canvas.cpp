#include "canvas.h"

Canvas::Canvas()
{
    width_ = 700;
    height_ = 700;

    fract.reserve(10);


//Решётка серпинского
    fract.push_back(LSystem("FXFLLFFLLFF"));
    fract.back().add_rule('F', "FF");
    fract.back().add_rule('X', "LLFXFRRFXFRRFXFLL");
    fract.back().len = 250;
    fract.back().r = 2;
    turtle.push_back(Turtle(-fract.back().len, -fract.back().len / 2 * sqrt(3)));
    turtle.back().set_angle(M_PI / 3);


// Десятиугольник Коха
    fract.push_back(LSystem("LLLFRFRFRFRFRFRFRF"));
    fract.back().add_rule('F', "FLLFRRFRRFLLF");
    fract.back().len = 180;
    fract.back().r = 3;
    turtle.push_back(Turtle(-fract.back().len / 2, -fract.back().len));
    turtle.back().set_angle(M_PI / 4);

// Квадратный остров Коха
    fract.push_back(LSystem("FRFRFRF"));
    fract.back().add_rule('F', "FLFRFRFFFLFLFRF");
    fract.back().len = 200;
    fract.back().r = 4;
    turtle.push_back(Turtle(-fract.back().len / 2, fract.back().len / 2));
    turtle.back().set_angle(M_PI / 2);

//Квадратный фрактал Госпера
    fract.push_back(LSystem("YF"));
    fract.back().add_rule('X', "XFXLYFLYFRFXRFXLYFLYFFXRYFRFXFXYFLFXRYFRFXFXRYFLFXYFLYFLFXRFXRYFYFL");
    fract.back().add_rule('Y', "RFXFXLYFLYFRFXRFXYFRFXLYFYFLFXLYFRFXYFYFLFXLYFFXRFXRYFLYFLFXRFXRYFY");
    fract.back().len = 500;
    fract.back().r = 5;
    turtle.push_back(Turtle(-fract.back().len / 2, fract.back().len / 2));
    turtle.back().set_angle(M_PI / 2);


//Кривая дракона
    fract.push_back(LSystem("FX"));
    fract.back().add_rule('X', "XRYFR");
    fract.back().add_rule('Y', "LFXLY");
    fract.back().len = 300;
    fract.back().r = 1.41;
    turtle.push_back(Turtle(0, 0));
    turtle.back().set_angle(M_PI / 2);

//Анклеты Кришны
    fract.push_back(LSystem("LXLLX"));
    fract.back().add_rule('X', "XFXLLXFX");
    fract.back().len = 500;
    fract.back().r = 2.2;
    turtle.push_back(Turtle(0, -250 * sqrt(2) / 2));
    turtle.back().set_angle(M_PI / 4);

// 32-сегментная кривая
    fract.push_back(LSystem("FRFRFRF"));
    fract.back().add_rule('F', "LFRFLFLFRFRFFLFRFRFFRFLFLFFRFFLFFRFRFLFFLFLFRFFLFLFRFRFLFR");
    fract.back().len = 500;
    fract.back().r = 16;
    turtle.push_back(Turtle(-250, 250));
    turtle.back().set_angle(M_PI / 2);

//Pentaplexity
    fract.push_back(LSystem("FRRFRRFRRFRRF"));
    fract.back().add_rule('F', "FRRFRRFRRRRRFLFRRF");
    fract.back().len = 400;
    fract.back().r = 2.6189;
    turtle.push_back(Turtle(-fract.back().len / 2, fract.back().len / 1.41));
    turtle.back().set_angle(M_PI / 5);

// Кольца
    fract.push_back(LSystem("FRFRFRF"));
    fract.back().add_rule('F', "FFRFRFRFRFRFLF");
    fract.back().len = 300;
    fract.back().r = 3.2;
    turtle.push_back(Turtle(0, fract.back().len / 2));
    turtle.back().set_angle(M_PI / 2);


//Ковер серпинского
    fract.push_back(LSystem("YF"));
    fract.back().add_rule('X', "YFRXFRY");
    fract.back().add_rule('Y', "XFLYFLX");
    fract.back().len = 300;
    fract.back().r = 2;
    turtle.push_back(Turtle(-fract.back().len / 2, 0));
    turtle.back().set_angle(M_PI / 3);

}


QRectF Canvas::boundingRect() const {
    return QRectF(0, 0, width_, height_);
}


void Canvas::paint(QPainter *painter_, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    QPixmap pixmap(width_, height_);
    QPainter painter(&pixmap);

    painter.setBrush(Qt::black);
    painter.setPen(Qt::black);
    painter.drawRect(boundingRect());

    QMatrix m;
    m.translate(width_ / 2, height_ / 2);
    m.scale(1, -1);

    painter.setTransform(QTransform(m));

    painter.setBrush(Qt::black);
    painter.setPen(Qt::white);

    turtle[cur_fr].set_velocity(QVector2D(fract[cur_fr].len / pow(fract[cur_fr].r, fract[cur_fr].iter), 0));
    turtle[cur_fr].draw(fract[cur_fr].get_instruction(), painter);

    painter_->drawPixmap(0, 0, width_, height_, pixmap);
}


void Canvas::keyPressEvent(QKeyEvent *event) {
    if (event->key() == '+') {
        fract[cur_fr].next();
    } else if (event->key() == '-') {
        fract[cur_fr].prev();
    } else if (event->key() <= '9' && event->key() >= '0') {
        cur_fr = event->key() - '0';
    }
    update();
}
