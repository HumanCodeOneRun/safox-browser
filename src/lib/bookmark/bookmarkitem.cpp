#include "bookmarkitem.h"
#include "ui_bookmarkitem.h"

BookmarkItem::BookmarkItem(QWidget *parent,int x,int y,QString url,QString title,QString description) :
    QWidget(parent),
    ui(new Ui::BookmarkItem)
{
    ui->setupUi(this);

}

BookmarkItem::~BookmarkItem()
{
    delete ui;
}
