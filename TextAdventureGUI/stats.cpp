#include "stats.h"

Stats::Stats(QObject *parent) : QObject(parent)
{
    health = 10;
    def = 1;
    att = 1;
    wallet = 0;
    maxHealth = health;
}
int Stats::getHealth(){
    return health;
}
int Stats::getMaxHealth(){
    return maxHealth;
}

int Stats::getDef(){
    return def;
}

int Stats::getAtt(){
    return att;
}

int Stats::getWallet(){
    return wallet;
}

void Stats::setWallet(int amnt){
    wallet = amnt;
}

void Stats::setHealth(int heal){
    health = heal;
}

void Stats::setDef(int def){
    this->def = def;
}

void Stats::setAtt(int att){
    this->att = att;
}

void Stats::resetStat(){
    health = 10;
    def = 1;
    att = 1;
    wallet = 0;
}
