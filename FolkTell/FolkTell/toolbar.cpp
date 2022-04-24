#include "toolbar.h"

Toolbar::Toolbar(QWidget* parent,int x,int y,int width,int height):
    QWidget(parent)
{
    init_x = x;
    init_y = y;
    width = width;
    height = height;
    this->setGeometry(x,y,width,height);
    //todo:组件背景颜色设置
    this->setStyleSheet("Toolbar{background-color:white;}");


    /* 书签按钮 */
    bookmarkerBtn = new QToolButton(parent);
    bookmarkerBtn->setGeometry(x+150,y+10,45,30);
    bookmarkerBtn->setStyleSheet("QToolButton{background-color:rgba(96, 100, 101, 100);border-radius:8px;}");

    /* 首页按钮 */
    homeBtn = new QToolButton(parent);
    homeBtn->setGeometry(x+232,y+10,45,30);
    homeBtn->setStyleSheet("QToolButton{background-color:rgba(96, 100, 101, 100);border-radius:8px;}");

    /* 下载按钮 */
    downloadBtn = new QToolButton(parent);
    downloadBtn->setGeometry(x+1575,y+10,45,30);
    downloadBtn->setStyleSheet("QToolButton{background-color:rgba(96, 100, 101, 100);border-radius:8px;}");

    /* 历史按钮 */
    historyBtn = new QToolButton(parent);
    historyBtn->setGeometry(x+1640,y+10,45,30);
    historyBtn->setStyleSheet("QToolButton{background-color:rgba(96, 100, 101, 100);border-radius:8px;}");

    /* 账户按钮 */
    accountBtn = new QToolButton(parent);
    accountBtn->setGeometry(x+1705,y+10,45,30);
    accountBtn->setStyleSheet("QToolButton{background-color:rgba(96, 100, 101, 100);border-radius:8px;}");

    /* 设置按钮 */
    settingBtn = new QToolButton(parent);
    settingBtn->setGeometry(x+1770,y+10,45,30);
    settingBtn->setStyleSheet("QToolButton{background-color:rgba(96, 100, 101, 100);border-radius:8px;}");

    /* 添加按钮 */
    addBtn = new QToolButton(parent);
    addBtn->setGeometry(x+1770,y+10,45,30);
    addBtn->setStyleSheet("QToolButton{background-color:rgba(96, 100, 101, 100);border-radius:8px;}");

    /* 网址 */
    urlBar = new QLineEdit(parent);
    urlBar->setGeometry(x+460,y+10,1000,30);
    urlBar->setStyleSheet("QLineEdit{background-color:rgba(35, 38, 43, 100);border-radius:8px;}");
}
