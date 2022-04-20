#include "browserwindow.h"
#include "./ui_browserwindow.h"
#include <QPushButton>
#include <QToolButton>

BrowserWindow::BrowserWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::BrowserWindow)
{
    ui->setupUi(this);

    /*隐藏默认标题栏*/
    //setWindowFlags(Qt::FramelessWindowHint|Qt::Tool|Qt::WindowStaysOnTopHint);

    //todo:获取屏幕分辨率并赋值给curHeight,curWidth，默认1920*1080
    this->curHeight=1920,this->curWidth=1080;
    QMainWindow::resize(this->curHeight,this->curWidth);

    /*toolbar*/
    this->tb = new ToolBar(this);
    tb->height = 100;
    tb->width = this->curWidth;
    tb->resize(tb->width,tb->height);

    QToolButton* closeBtn = new QToolButton(this);
    closeBtn->setGeometry(100,100,20,20);
    connect(closeBtn,&QToolButton::clicked,this,&BrowserWindow::on_closeBtn_clicked);
}

BrowserWindow::~BrowserWindow()
{
    delete ui;
}


void BrowserWindow::on_closeBtn_clicked()
{
    qDebug("bbbbbbb");
    this->close();
}


void BrowserWindow::on_minBtn_clicked()
{

}

