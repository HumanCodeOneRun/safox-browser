#include "bookmarkbox.h"

BookmarkBox::BookmarkBox(QWidget* parent,int width,int height)
{
    qDebug()<<width;
    this->setGeometry(0,100,width,height);
    this->setStyleSheet("QScrollArea{border:none;background-color:red;}");
    QWidget* mubu = new QWidget();
    this->setWidget(mubu);
    this->vlayout = new QVBoxLayout();
    QToolButton* temp = new QToolButton(mubu);
    temp->setGeometry(0,0,40,20);
//    BookmarkItem temp(mubu,20,0,":/icon/../image/setting.png","test_title","test_description");
    this->widget()->setLayout(this->vlayout);
//    this->setWidget(parent);
}
