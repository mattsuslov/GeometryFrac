#ifndef LSYSTEM_H
#define LSYSTEM_H

#include <QString>
#include <QMap>
#include <QDebug>


class LSystem
{
public:
    LSystem();
    LSystem(const LSystem& lsys) : mem_(lsys.mem_), dict_(lsys.dict_)  {}
    LSystem(const QString& instruction) {
        mem_.push_back(instruction);
    }

    QString get_instruction() {
        return mem_[iter];
    }

    void next() {
        ++iter;
        if (mem_.size() == iter) {
            gen_iter();
        }
    }


    void prev() {
        if (iter == 0) return;
        --iter;
    }


    void add_rule(QChar a, QString str) {
        dict_[a] = str;
    }


    int iter = 0;
    long double r;
    long double len;

private:
    void gen_iter() {
        QString new_inst = "";
        for (QChar com: mem_[mem_.size() - 1]) {
            if (dict_.contains(com)) {
                new_inst.append(dict_[com]);
            } else {
                new_inst.append(com);
            }
        }
        mem_.push_back(new_inst);
    }

    QMap<QChar, QString> dict_;
    std::vector<QString> mem_;

};

#endif // LSYSTEM_H
