#ifndef COMMAND_H
#define COMMAND_H

#include <QVector2D>


class Command
{
public:
    Command();

private:
    enum Type {
        DRAW_LINE,
        TURN
    };
    Type type_;

};

#endif // COMMAND_H
