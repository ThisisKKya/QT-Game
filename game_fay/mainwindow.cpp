#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include<QKeyEvent>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    this->player = new hero(this);

    resize(WidgetWidth,WidgetHeight);


///////////////////////////////人物////////////////////////////////////////////////
    connect(player,&hero::UpDatePainter,[=](){
        update();
    });
    connect(player,&hero::StartTimer,[=](){
        FallTimer->start();
    });
    connect(player,&hero::StopTimer,[=](){
        FallTimer->stop();
    });
    connect(JumpTimer,&QTimer::timeout,[=](){ //跳跃的函数, 降落到地面的时候停止定时器
        update();
        if(player->HeroJump())
        {
            JumpTimer->stop();
        }
    });


////////////////////////////////背景///////////////////////////////////////////////






////////////////////////////////怪物//////////////////////////////////////////////
}

void MainWindow::paintEvent(QPaintEvent *)
{

        //实例化画家对象  this指定的是绘图设备
        QPainter painter(this);
        //画地面
        painter.drawLine(QPoint(0,GroundY),QPoint(WidgetWidth,GroundY));
        //画人
        painter.drawPixmap(player->heroPosX,player->heroPosY,QPixmap(":/hero/adventurer-run-04.png"));
}
void MainWindow::timerEvent(QTimerEvent *ev)
{
    if(ev->timerId() == JumpTimer->timerId())
    {
        update();
        player->HeroJump();
    }
    if(ev->timerId() == FallTimer->timerId())
    {
        update();
        if(player->HeroFallDown())
        {
            FallTimer->stop();
        }
    }

}

void MainWindow::keyPressEvent(QKeyEvent *ev)
{
    if(ev->key() == Qt::Key_J ) //跳跃
    {
        player->flag = 0;//把跳跃的方向置为向上
        JumpTimer->start(50);//每50ms更新一次人物的位置
    }
    if(ev->key() == Qt::Key_A)//左移
    {
        player->HeroGoLeft(); //人向左运动
        update();
    }
    if(ev->key() == Qt::Key_D)//右移
    {
        player->HeroGoRight();//人向右运动
        update();
    }
}
MainWindow::~MainWindow()
{
    delete ui;
}
