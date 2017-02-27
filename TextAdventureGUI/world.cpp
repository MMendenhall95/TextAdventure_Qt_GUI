#include "world.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <QDebug>

World::World(QObject *parent) : QObject(parent)
{
    currentSeed = 0;
}


QStringList World::generate(int genSed){
    QString temp;
    int seed;
    currentSeed = genSed;
    srand(genSed);

    //clears out map in in the event of a reset/new map

    while(!world_map.empty())
    {
        world_map.clear();
    }
    //generates the randomly geerated map
    world_map << "XXXXXXXXXXXXXXXXXXXXXX";
    qDebug() << genSed;
    temp += "X";
    unsigned j = 0;
    unsigned i = 0;
    while (j < 18)
    {
        if (i == 20) {
            temp += "X";
            world_map << temp;
            temp = "";
            ++j;
            if (j == 18)
            {
                break;
            }
            i = 0;
            temp += "X";
        }
        seed = rand() % 10 + 1;
        if (seed <= 7)
        {
            ++i;
            temp += "-";      //grass
        }
        else if (seed == 10)
        {
            ++i;
            temp += "O";      //trees
        }
        else if (seed == 8 || seed == 9)
        {
            ++i;
            temp += "^";      //thick grass
        }
    }
    world_map << "XXXXXXXXXXXXXXXXXXXXXX";
    //adds the player character to the map at a random spot and sets the active tile
    //player starts on grass by default
    int location;
    location = rand() % 100 + 1;
    int count = 0;

    for (int i = 0; i < 20; i++){
        for (int j = 0; j < 22; j++){
            if (world_map[i].at(j) == '-' ){
                count++;
            }
            if (count == location){
                  tile = world_map[i].at(j);
                  world_map[i].replace(j, 1, "A");
                  x = j;
                  y = i;
                  return world_map;
            }
        }
    }


    return world_map;
}

QStringList World::generate(){
    QString temp;
    int seed;
    currentSeed = time(NULL);
    srand(currentSeed);

    //clears out map in in the event of a reset/new map

    while (!world_map.empty())
    {
        world_map.clear();
    }
    //generates the randomly geerated map
    world_map << "XXXXXXXXXXXXXXXXXXXXXX";
    qDebug() << time(NULL);
    temp += "X";
    unsigned j = 0;
    unsigned i = 0;
    while (j < 18)
    {
        if (i == 20) {
            temp += "X";
            world_map << temp;
            temp = "";
            ++j;
            if (j == 18)
            {
                break;
            }
            i = 0;
            temp += "X";
        }
        seed = rand() % 10 + 1;
        if (seed <= 7)
        {
            ++i;
            temp += "-";      //grass
        }
        else if (seed == 10)
        {
            ++i;
            temp += "O";      //trees
        }
        else if (seed == 8 || seed == 9)
        {
            ++i;
            temp += "^";      //thick grass
        }
    }
    world_map << "XXXXXXXXXXXXXXXXXXXXXX";
    //adds the player character to the map at a random spot and sets the active tile
    //player starts on grass by default
    int location;
    location = rand() % 100 + 1;
    int count = 0;

    for (int i = 0; i < 20; i++){
        for (int j = 0; j < 22; j++){
            if (world_map[i].at(j) == '-' ){
                count++;
            }
            if (count == location){
                  tile = world_map[i].at(j);
                  world_map[i].replace(j, 1, "A");
                  x = j;
                  y = i;
                  return world_map;
            }
        }
    }


    return world_map;
}
int World::getSeed(){
    return currentSeed;
}

QString World::getTile(){
    return tile;
}
bool World::getEvent(){
    return event;
}
void World::setEvent(bool event_1){
    event = event_1;
}

QString World::getLocation(){
    return QString("Location- X: %1 | Y: %2").arg(x).arg(y);
}

//moves the player throughout the array and changes character
//to match direction heading
QStringList World::pMove(int direction){
    
    currentSeed = time(NULL);
    srand(currentSeed);
    
    switch (direction){

    case 0: if (y >= 2){
            world_map[y].replace(x, 1, tile);
            tile = world_map[y - 1].at(x);
            world_map[--y].replace(x, 1, "A");

            if (getTile() == "-"){
                //10% chance
                if(rand()%10 + 1 == 1){
                    //window popup
                    //trigger event
                    event = true;
                    
                }
            }
            else if (getTile() == "^"){
                //50% chance
                if(rand()%10 + 1 < 6){
                    //window popup
                    //trigger event
                    event = true;
                }
            }
                //90% chance
            else if (getTile() == "O"){
                if (rand()%10 + 1 < 10){
                    //window popup
                    //trigger event
                    event = true;
                }
            }
        }
        break;
    case 1: if (y <= 17){
            world_map[y].replace(x, 1, tile);
            tile = world_map[y + 1].at(x);
            world_map[++y].replace(x, 1, "V");

            if (getTile() == "-"){
                //10% chance
                if(rand()%10 + 1 == 1){
                    event = true;
                }
            }
            else if (getTile() == "^"){
                //50% chance
                if (rand()%10 + 1 < 6){
                    event = true;
                }
            }
                //90% chance
            else if (getTile() == "O"){
                if (rand()%10 + 1 < 10){
                    //window popup
                    //trigger event
                    event = true;
                }
            }
        }

        break;
    case 2: if (x >= 2){
            world_map[y].replace(x, 1, tile);
            tile = world_map[y].at(x - 1);
            world_map[y].replace(--x, 1, "<");

            if (getTile() == "-"){
                //10% chance
                if (rand()%10 + 1 == 1){
                    //window popup
                    //trigger event
                    event = true;
                }
            }
            else if (getTile() == "^"){
                //50% chance
                if (rand()%10 + 1 < 6){
                    //window popup
                    //trigger event
                    event = true;
                }
            }
                //90% chance
            else if (getTile() == "O"){
                if (rand()%10 + 1 < 10){
                    //window popup
                    //trigger event
                    event = true;
                }
            }
        }
        break;
    case 3: if (x <= 19){
            world_map[y].replace(x, 1, tile);
            tile = world_map[y].at(x + 1);
            world_map[y].replace(++x, 1, ">");

            if (getTile() == "-"){
                //10% chance
                if (rand()%10 + 1 == 1){
                    //window popup
                    //trigger event
                    event = true;
                }
            }
            else if (getTile() == "^"){
                //50% chance
                if (rand()%10 + 1 < 6){
                    //window popup
                    //trigger event
                    event = true;
                }
            }
                //90% chance
            else if (getTile() == "O"){
                if (rand()%10 + 1 < 10){
                    //window popup
                    //trigger event
                    event = true;
                }
            }
        }
        break;
    };
    return world_map;
}
