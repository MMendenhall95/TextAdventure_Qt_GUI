#ifndef STATS_H
#define STATS_H

#include <QObject>

class Stats : public QObject
{
    Q_OBJECT
private:
    int health;
    int maxHealth;
    int def;
    int att;
    int wallet;
public:
    explicit Stats(QObject *parent = 0);
    int getHealth();
    int getMaxHealth();
    int getDef();
    int getAtt();
    int getWallet();
    void setWallet(int amnt);
    void setHealth(int heal);
    void setDef(int def);
    void setAtt(int att);
    void resetStat();

signals:

public slots:
};

#endif // STATS_H
