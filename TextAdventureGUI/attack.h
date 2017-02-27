#ifndef ATTACK_H
#define ATTACK_H

#include <QObject>
#include "stats.h"

class Attack : public QObject
{
    Q_OBJECT
private:
    int diff;
    Stats *monster;
    int seed;
public:
    explicit Attack(QObject *parent = 0);
    int getDif();
    int monsterWallet();
    bool run();
    void reset();
    void attack();
    void genMonster(int difficulty);
signals:


public slots:
    void incDif(QString tile);

};

#endif // ATTACK_H
