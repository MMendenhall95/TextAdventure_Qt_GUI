#include "attack.h"
#include "stats.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <QTimer>

Attack::Attack(QObject *parent) : QObject(parent)
{
    diff = 1;
    monster = new Stats;
}

void Attack::incDif(QString tile){
    if (tile == "-"){
        diff++;
    }
    else if (tile == "^"){
        diff += 2;
    }else{
        diff +=3;
    }
}

void Attack::reset(){
    diff = 1;
}

int Attack::getDif(){
    return diff;
}

void Attack::genMonster(int difficulty){

    int seed;
    seed = time(NULL);
    srand(seed);
    
    monster->setWallet(rand() % 6 + difficulty);
}

bool Attack::run(){

    seed = time(NULL);
    srand(seed);
    
    if (rand() % 2 + 1 == 1)
        return true;
    else
        return false;
}

int Attack::monsterWallet(){
    return monster->getWallet();
}
