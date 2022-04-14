#include "browserwindow.h"
#include "./ui_browserwindow.h"

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


}

BrowserWindow::~BrowserWindow()
{
    delete ui;
}

