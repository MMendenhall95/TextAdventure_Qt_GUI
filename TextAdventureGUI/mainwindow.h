#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "world.h"
#include "stats.h"
#include "attack.h"
#include <QMainWindow>
//#include <QMediaPlayer>
#include <QUrl>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    World *map;
    Attack *atk; //may want to rename this later on
    QString te;
    Attack *monster;
    Stats *pStat;
   // QMediaPlayer *button;
   // QMediaPlayer *background;
   // QMediaPlayer *dead;
   // QMediaPlayer *purchase;
    enum direction{up, down, left, right};

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void on_mapGen_clicked();

    void difManage();

    void on_pbUp_clicked();

    void on_pbDown_clicked();

    void on_pbLeft_clicked();

    void on_pbRight_clicked();

    void on_rdmCb_clicked();

    void on_figBtn_clicked();

    void on_rnBtn_clicked();

    void on_hePurBtn_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
