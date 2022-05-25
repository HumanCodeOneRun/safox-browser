#include "src/ui/bookmark/bookmarkitem.h"
#include "ui_bookmarkitem.h"

BookmarkItem::BookmarkItem(QWidget *parent,int x,int y,QString url,QString title,QString description) :
    QWidget(parent),
    ui(new Ui::BookmarkItem)
{
    ui->setupUi(this);
    QLabel* iconLabel = new QLabel(parent);
    iconLabel->setPixmap(QPixmap(url));
    iconLabel->show();
    iconLabel->setGeometry(x+16,y+25,80,80);
    iconLabel->setStyleSheet("QLabel{background-color:grey;}");

    QLabel* titleLabel = new QLabel(parent);
    titleLabel->setStyleSheet("QLabel{background-color:transparent;color:white;font-size:14px;}");
    titleLabel->setText(title);
    titleLabel->setGeometry(x+106,y+25,126,20);

    QLabel* descriptionLabel = new QLabel(parent);
    descriptionLabel->setStyleSheet("QLabel{background-color:transparent;color:white;font-size:14px;}");
    descriptionLabel->setText(description);
    descriptionLabel->setAlignment(Qt::AlignLeft|Qt::AlignTop);
    descriptionLabel->setGeometry(x+106,y+55,126,50);
}

BookmarkItem::~BookmarkItem()
{
    delete ui;
}
