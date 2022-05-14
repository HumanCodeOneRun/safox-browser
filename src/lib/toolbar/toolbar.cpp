/*
 * @Author: your name
 * @Date: 2022-05-03 11:39:08
 * @LastEditTime: 2022-05-03 11:39:32
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \FolkTell\FolkTell\src\toolbar.cpp
 */
#include "toolbar.h"


Toolbar::Toolbar(QWidget* parent,int x,int y,int width,int height):
    QWidget(parent)
{
    this->init_x = x;
    this->init_y = y;
    this->width = width;
    this->height = height;
    this->setGeometry(x,y,width,height);

    /* 后退按钮 */
    backBtn = new QToolButton(parent);
    backBtn->setGeometry(x+30,y+10,45,30);
    backBtn->setStyleSheet("QToolButton{background-color:rgba(96, 100, 101, 100);border-radius:8px;}");
    QIcon back = QIcon(":/icon/image/arrow-left-allow.png");
    backBtn->setIcon(back);

    /* 前进按钮 */
    goBtn = new QToolButton(parent);
    goBtn->setGeometry(x+73,y+10,45,30);
    goBtn->setStyleSheet("QToolButton{background-color:rgba(96, 100, 101, 100);border-radius:8px;}");
    QIcon go = QIcon(":/icon/image/arrow-right-allow.png");
    goBtn->setIcon(go);

    /* 书签按钮 */
    bookmarkerBtn = new QToolButton(parent);
    bookmarkerBtn->setGeometry(x+150,y+10,45,30);
    bookmarkerBtn->setStyleSheet("QToolButton{background-color:rgba(96, 100, 101, 100);border-radius:8px;}");
    QIcon bookmaker = QIcon(":/icon/image/bookmaker.png");
    bookmarkerBtn->setIcon(bookmaker);
    connect(bookmarkerBtn,&QToolButton::clicked,this,&Toolbar::on_bookmarkerBtn_clicked);

    /* 首页按钮 */
    homeBtn = new QToolButton(parent);
    homeBtn->setGeometry(x+232,y+10,45,30);
    homeBtn->setStyleSheet("QToolButton{background-color:rgba(96, 100, 101, 100);border-radius:8px;}");
    QIcon homepage = QIcon(":/icon/image/homepage.png");
    homeBtn->setIcon(homepage);

    /* 下载按钮 */
    downloadBtn = new QToolButton(parent);
    downloadBtn->setGeometry(x+1575,y+10,45,30);
    downloadBtn->setStyleSheet("QToolButton{background-color:rgba(96, 100, 101, 100);border-radius:8px;}");
    QIcon download = QIcon(":/icon/image/download.png");
    downloadBtn->setIcon(download);

    /* 历史按钮 */
    historyBtn = new QToolButton(parent);
    historyBtn->setGeometry(x+1640,y+10,45,30);
    historyBtn->setStyleSheet("QToolButton{background-color:rgba(96, 100, 101, 100);border-radius:8px;}");
    QIcon history = QIcon(":/icon/image/history.png");
    historyBtn->setIcon(history);
    connect(historyBtn,&QToolButton::clicked,this,&Toolbar::on_historyBtn_clicked);


    /* 账户按钮 */
    accountBtn = new QToolButton(parent);
    accountBtn->setGeometry(x+1705,y+10,45,30);
    accountBtn->setStyleSheet("QToolButton{background-color:rgba(96, 100, 101, 100);border-radius:8px;}");
    QIcon account = QIcon(":/icon/image/account.png");
    accountBtn->setIcon(account);


    /* 设置按钮 */
    settingBtn = new QToolButton(parent);
    settingBtn->setGeometry(x+1770,y+10,45,30);
    settingBtn->setStyleSheet("QToolButton{background-color:rgba(96, 100, 101, 100);border-radius:8px;}");
    QIcon setting = QIcon(":/icon/image/setting.png");
    settingBtn->setIcon(setting);

    /* 添加按钮 */
    addBtn = new QToolButton(parent);
    addBtn->setGeometry(x+1770,y+10,45,30);
    addBtn->setStyleSheet("QToolButton{background-color:rgba(96, 100, 101, 100);border-radius:8px;}");
    QIcon add = QIcon(":/icon/image/add.png");
    addBtn->setIcon(add);

    /* 网址 */
    urlBar = new QLineEdit(parent);
    urlBar->setGeometry(x+460,y+10,1000,30);
    urlBar->setStyleSheet("QLineEdit{background-color:rgba(35, 38, 43, 100);border-radius:8px;color:rgba(136, 136, 136, 100);font-size:14px;}");
    urlBar->setText("www.baidu.com");
    urlBar->setAlignment(Qt::AlignHCenter);
    QAction * pActLeft = new QAction(this);
    pActLeft->setIcon(QIcon(":/icon/image/search.png"));
    urlBar->addAction(pActLeft,QLineEdit::LeadingPosition);
}

void Toolbar::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);

    /* 绘制Toolbar背景 */
    p.setPen(Qt::NoPen);
    p.setBrush(QColor(50, 54, 64, 100));
    p.drawRect(0,0,this->width,this->height);
}

void Toolbar::on_historyBtn_clicked(){
    emit on_historyBtn_passSignal();
}

void Toolbar::on_bookmarkerBtn_clicked(){
    qDebug("click");
    emit on_bookmarkerBtn_passSignal();
}
