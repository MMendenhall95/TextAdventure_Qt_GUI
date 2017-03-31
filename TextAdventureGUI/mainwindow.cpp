#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "world.h"
#include "attack.h"
#include <QInputDialog>
#include <QTimer>
#include <QDebug>
////////////////////////////////////////////
/// MAP DOES NOT DISPLAY PROPERLY ON WINDOWS
////////////////////////////////////////////
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    map = new World();
    pStat = new Stats();
    atk = new Attack();
    monster = new Attack();
    //background = new QMediaPlayer();
    //dead = new QMediaPlayer();
    //button = new QMediaPlayer();
    //purchase = new QMediaPlayer();


   // background->setMedia(QUrl("qrc:/sounds/Hungarian.ogg"));
    //background->play();
    //dead->setMedia(QUrl("qrc:/sounds/dead.wav"));
    //button->setMedia(QUrl("qrc:/sounds/button.wav"));
    //purchase->setMedia(QUrl("qrc:/sounds/kaching.ogg"));
    ui->textMap->setAutoFillBackground(false);
    ui->textMap->setFrameStyle(QFrame::NoFrame);
//asks for entry then generates map based on input (default is 0) and then sets everything else up
    for(auto &data : map->generate(QInputDialog::getText(this, "SET SEED", "Enter Map Generation Seed: ").toInt())){
        ui->textMap->append(data);
        qDebug() << endl << data;
    }
    ui->lvlSed->setText(QString::number(map->getSeed()));
    ui->mpSeedLbl->setText(QString("Map Seed: %1").arg(map->getSeed()));

    ui->tileLbl->setText("Current Tile: " + map->getTile());
    ui->pLoc->setText(map->getLocation());

    ui->healthBar->setMaximum(pStat->getMaxHealth());
    ui->healthBar->setMinimum(0);
    ui->healthBar->setValue(pStat->getHealth());

    ui->wallet->setText("Wallet: $" + QString::number(pStat->getWallet()));
    ui->difLbl->setText("Difficulty: " + QString::number(atk->getDif()));
    ui->HeUp->setText("Health Potion: $" + QString::number(atk->getDif() * 10));

    ui->rnBtn->setDisabled(true);
    ui->figBtn->setDisabled(true);
    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()), this, SLOT(difManage()));
    timer->start(10000);
}

void MainWindow::difManage(){
    atk->incDif(map->getTile());
    ui->difLbl->setText("Difficulty: " + QString::number(atk->getDif()));
    pStat->setWallet(pStat->getWallet() + 10);
    ui->wallet->setText("Wallet: $" + QString::number(pStat->getWallet()));
    ui->HeUp->setText("Health Potion: $" + QString::number(atk->getDif() * 10));
    /*
    map->setEvent(false);
    if (map->getEvent()){
        ui->eveTxt->setText("A MONSTER HAS ATTACKED!");

    }else{
        ui->eveTxt->setText("");
    }
    */
}

MainWindow::~MainWindow()
{
    delete ui;
}

//generates a new map and resets your stats
void MainWindow::on_mapGen_clicked()
{
    /*if(button->state() == QMediaPlayer::PlayingState)
    {
        button->setPosition(0);
    }
    else if(button->state() == QMediaPlayer::StoppedState)
    {
        button->play();
    }
    */ui->textMap->setText("");

    if (ui->rdmCb->checkState()){

        for (auto &data : map->generate()){
            ui->textMap->append(data);
        }
    }
    else{
        for (auto &data : map->generate(ui->lvlSed->text().toInt())){
            ui->textMap->append(data);
            qDebug() << endl << data;
        }
    }
    ui->mpSeedLbl->setText(QString("Map Seed: %1").arg(map->getSeed()));

    ui->tileLbl->setText("Current Tile: " + map->getTile());
    ui->pLoc->setText(map->getLocation());

    ui->healthBar->setValue(100);

    pStat->resetStat();

    ui->healthBar->setMaximum(pStat->getMaxHealth());
    ui->healthBar->setMinimum(0);
    ui->healthBar->setValue(pStat->getHealth());

    atk->reset();

    ui->difLbl->setText("Difficulty: " + QString::number(atk->getDif()));
    ui->wallet->setText("Wallet: $" + QString::number(pStat->getWallet()));
}


//movement
void MainWindow::on_pbUp_clicked()
{
    /*if(button->state() == QMediaPlayer::PlayingState)
    {
        button->setPosition(0);
    }
    else if(button->state() == QMediaPlayer::StoppedState)
    {
        button->play();
    }
    */ui->textMap->setText("");
    map->setEvent(false);
    for (auto &data : map->pMove(up)){
        ui->textMap->append(data);
        qDebug() << endl << data;
    }

    ui->tileLbl->setText("Current Tile: " + map->getTile());
    ui->pLoc->setText(map->getLocation());

    if(map->getEvent()){
        ui->eveTxt->setText("A MONSTER HAS ATTACKED!");
        ui->pbUp->setDisabled(true);
        ui->pbDown->setDisabled(true);
        ui->pbLeft->setDisabled(true);
        ui->pbRight->setDisabled(true);
        ui->figBtn->setDisabled(false);
        ui->rnBtn->setDisabled(false);
        monster->genMonster(atk->getDif());
    }else{
        ui->eveTxt->setText("");
    }
}

//move down
void MainWindow::on_pbDown_clicked()
{
    /*if(button->state() == QMediaPlayer::PlayingState)
    {
        button->setPosition(0);
    }
    else if(button->state() == QMediaPlayer::StoppedState)
    {
        button->play();
    }
    */ui->textMap->setText("");
    map->setEvent(false);
    for (auto &data : map->pMove(down)){
        ui->textMap->append(data);
        qDebug() << endl << data;
    }

    ui->tileLbl->setText("Current Tile: " + map->getTile());
    ui->pLoc->setText(map->getLocation());

    if (map->getEvent()){
        ui->eveTxt->setText("A MONSTER HAS ATTACKED!");
        ui->pbUp->setDisabled(true);
        ui->pbDown->setDisabled(true);
        ui->pbLeft->setDisabled(true);
        ui->pbRight->setDisabled(true);
        ui->figBtn->setDisabled(false);
        ui->rnBtn->setDisabled(false);
        monster->genMonster(atk->getDif());
    }else{
        ui->eveTxt->setText("");
    }
}

//move left
void MainWindow::on_pbLeft_clicked()
{
    /*if(button->state() == QMediaPlayer::PlayingState)
    {
        button->setPosition(0);
    }
    else if(button->state() == QMediaPlayer::StoppedState)
    {
        button->play();
    }
    */ui->textMap->setText("");
    map->setEvent(false);
    for (auto &data : map->pMove(left)){
        ui->textMap->append(data);
        qDebug() << endl << data;
    }

    ui->tileLbl->setText("Current Tile: " + map->getTile());
    ui->pLoc->setText(map->getLocation());

    if (map->getEvent()){
        ui->eveTxt->setText("A MONSTER HAS ATTACKED!");
        ui->pbUp->setDisabled(true);
        ui->pbDown->setDisabled(true);
        ui->pbLeft->setDisabled(true);
        ui->pbRight->setDisabled(true);
        ui->figBtn->setDisabled(false);
        ui->rnBtn->setDisabled(false);
        monster->genMonster(atk->getDif());
    }else{
        ui->eveTxt->setText("");
    }
}

//move right
void MainWindow::on_pbRight_clicked()
{
    /*if(button->state() == QMediaPlayer::PlayingState)
    {
        button->setPosition(0);
    }
    else if(button->state() == QMediaPlayer::StoppedState)
    {
        button->play();
    }
    */ui->textMap->setText("");
    map->setEvent(false);
    for (auto &data : map->pMove(right)){
        ui->textMap->append(data);
        qDebug() << endl << data;
    }

    ui->tileLbl->setText("Current Tile: " + map->getTile());
    ui->pLoc->setText(map->getLocation());

    if (map->getEvent()){
        ui->eveTxt->setText("A MONSTER HAS ATTACKED!");
        ui->pbUp->setDisabled(true);
        ui->pbDown->setDisabled(true);
        ui->pbLeft->setDisabled(true);
        ui->pbRight->setDisabled(true);
        ui->figBtn->setDisabled(false);
        ui->rnBtn->setDisabled(false);

        monster->genMonster(atk->getDif());


    }else{

        ui->eveTxt->setText("");
    }
}

//set random generation
void MainWindow::on_rdmCb_clicked()
{
    /*if(button->state() == QMediaPlayer::PlayingState)
    {
        button->setPosition(0);
    }
    else if(button->state() == QMediaPlayer::StoppedState)
    {
        button->play();
    }
    ui->lvlSed->setDisabled(ui->rdmCb->checkState());
*/
}

//combat button
void MainWindow::on_figBtn_clicked()
{
  /*  if(button->state() == QMediaPlayer::PlayingState)
    {
        button->setPosition(0);
    }
    else if(button->state() == QMediaPlayer::StoppedState)
    {
        button->play();
    }
*/
    ui->healthBar->setValue(pStat->getHealth() - monster->getDif());
    pStat->setHealth(pStat->getHealth() - monster->getDif());
    ui->pbUp->setDisabled(false);
    ui->pbDown->setDisabled(false);
    ui->pbLeft->setDisabled(false);
    ui->pbRight->setDisabled(false);
    ui->figBtn->setDisabled(true);
    ui->rnBtn->setDisabled(true);
   // qDebug() << monster->monsterWallet();

    pStat->setWallet((pStat->getWallet() + monster->monsterWallet()));
    ui->wallet->setText("Wallet: $" + QString::number(pStat->getWallet()));
    if(pStat->getHealth() == 0){
        ui->pbDown->setDisabled(true);
        ui->pbUp->setDisabled(true);
        ui->pbLeft->setDisabled(true);
        ui->pbRight->setDisabled(true);
        ui->rnBtn->setDisabled(true);
        ui->figBtn->setDisabled(true);
        ui->mapGen->setDisabled(true);
        ui->rdmCb->setDisabled(true);
        ui->lvlSed->setDisabled(true);
        ui->hePurBtn->setDisabled(true);
        ui->eveTxt->setText("GAME OVER\nYOU DIED!");
        /*if(background->state() == QMediaPlayer::PlayingState){
            background->stop();
        }
        dead->play();
*/
}

}

//run away!
void MainWindow::on_rnBtn_clicked()
{
    /*
    if(button->state() == QMediaPlayer::PlayingState)
    {
        button->setPosition(0);
    }
    else if(button->state() == QMediaPlayer::StoppedState)
    {
        button->play();
    }
    */if(monster->run()){
        ui->eveTxt->setText("You Got Away!");
        ui->pbUp->setDisabled(false);
        ui->pbDown->setDisabled(false);
        ui->pbLeft->setDisabled(false);
        ui->pbRight->setDisabled(false);
    }else{
        ui->eveTxt->setText("You FAILED to get Away!");

        ui->healthBar->setValue(pStat->getHealth() - monster->getDif());
        pStat->setHealth(pStat->getHealth() - monster->getDif());
        ui->pbUp->setDisabled(false);
        ui->pbDown->setDisabled(false);
        ui->pbLeft->setDisabled(false);
        ui->pbRight->setDisabled(false);
        if (pStat->getHealth() == 0){
            ui->pbDown->setDisabled(true);
            ui->pbUp->setDisabled(true);
            ui->pbLeft->setDisabled(true);
            ui->pbRight->setDisabled(true);
            ui->rnBtn->setDisabled(true);
            ui->figBtn->setDisabled(true);
            ui->mapGen->setDisabled(true);
            ui->rdmCb->setDisabled(true);
            ui->lvlSed->setDisabled(true);
            ui->hePurBtn->setDisabled(true);
            ui->eveTxt->setText("GAME OVER\nYOU DIED!");
            /*if(background->state() == QMediaPlayer::PlayingState){
                background->stop();
            }
            dead->play();
            */
        }

    }
    ui->figBtn->setDisabled(true);
    ui->rnBtn->setDisabled(true);
}

void MainWindow::on_hePurBtn_clicked()
{
    if (pStat->getWallet() >= atk->getDif() * 10){
        pStat->setWallet(pStat->getWallet() - (atk->getDif() * 10));
       // qDebug() << "Wallet: " << pStat->getWallet();
        ui->wallet->setText("Wallet: $" + QString::number(atk->getDif() * 10));
        pStat->setHealth(10);

        ui->healthBar->setMaximum(pStat->getMaxHealth());
        ui->healthBar->setMinimum(0);
        ui->healthBar->setValue(pStat->getHealth());
        //purchase->play();
    }
    else
        ui->eveTxt->setText("I.S.F.");
}
