#include "bookmarkwidget.h"
#include "ui_bookmarkwidget.h"

BookmarkWidget::BookmarkWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BookmarkWidget)
{
    ui->setupUi(this);
}

BookmarkWidget::~BookmarkWidget()
{
    delete ui;
}
