#include "browserwindow.h"
#include "./ui_browserwindow.h"

BrowserWindow::BrowserWindow(QWidget *parent, const int & window_id)
    : QMainWindow(parent)
    , ui(new Ui::BrowserWindow)
    , id(window_id)
{
    ui->setupUi(this);

    /* 隐藏默认标题栏 */
    setWindowFlags(Qt::FramelessWindowHint|Qt::Tool|Qt::WindowStaysOnTopHint);

    //todo:获取屏幕分辨率并赋值给curHeight,curWidth，默认1920*1080

    //...

    this->curHeight=1920,this->curWidth=1080;
    QMainWindow::resize(this->curHeight,this->curWidth);


    //设置背景颜色
    this->setStyleSheet("QMainWindow{background-color: rgba(46, 50, 53, 100)}");

    /* toolbar */
    this->tb = new Toolbar(this,0,50,1920,50);

    /* 关闭按钮 */
    QToolButton* closeBtn = new QToolButton(this);
    closeBtn->setStyleSheet("QToolButton{background-color:rgba(235, 106, 99, 100);border-radius:10px;}");
    closeBtn->setGeometry(20,15,20,20);
    connect(closeBtn,&QToolButton::clicked,this,&BrowserWindow::on_closeBtn_clicked);

    /* 放大缩小按钮 */
    QToolButton* minBtn = new QToolButton(this);
    minBtn->setStyleSheet("QToolButton{background-color:rgba(241, 195, 78, 100);border-radius:10px;}");
    minBtn->setGeometry(50,15,20,20);
    connect(minBtn,&QToolButton::clicked,this,&BrowserWindow::on_minBtn_clicked);

    /* 最小化按钮 */
    QToolButton* hidBtn = new QToolButton(this);
    hidBtn->setStyleSheet("QToolButton{background-color:rgba(57, 194, 77, 100);border-radius:10px;}");
    hidBtn->setGeometry(80,15,20,20);
    connect(hidBtn,&QToolButton::clicked,this,&BrowserWindow::on_hidBtn_clicked);
}

int BrowserWindow::get_windowid(){
    return this->id;
}

bool BrowserWindow::set_windowid(const int & window_id){
    assert(window_id >= 0);
    
    this->id = window_id;
    return true;
}

BrowserWindow::~BrowserWindow()
{
    delete ui;
}


void BrowserWindow::on_closeBtn_clicked()
{
    this->close();
}


void BrowserWindow::on_minBtn_clicked()
{

}

void BrowserWindow::on_hidBtn_clicked()
{

}

