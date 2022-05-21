#include "src/ui/bookmark/bookmarkitem.h"
#include "ui_bookmarkitem.h"

BookmarkItem::BookmarkItem(QWidget *parent,int x,int y,QString url,QString title,QString description) :
    QWidget(parent),
    ui(new Ui::BookmarkItem)
{
    ui->setupUi(this);
    QLabel* iconLabel = new QLabel(this);
    iconLabel->setPixmap(QPixmap(url));
    iconLabel->show();
//    iconLabel->setGeometry()
}

BookmarkItem::~BookmarkItem()
{
    delete ui;
}
