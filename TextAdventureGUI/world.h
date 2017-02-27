#ifndef WORDL_H
#define WORDL_H

#include <QObject>
#include <QString>
#include <QVector2D>
#include <QStringList>

class World : public QObject
{
    Q_OBJECT
private:
    QStringList world_map;
    QString cord[20];
    QString tile;
    bool event;
    QString player;
    int x;
    int y;
    int currentSeed;

public:
    explicit World(QObject *parent = 0);

    QStringList generate(int genSed);
    QStringList generate();
    void setEvent(bool event_1);
    QStringList pMove(int direction);
    bool getEvent();
    int getSeed();
    QString getTile();
    QString getLocation();

};

#endif // WORDL_H
