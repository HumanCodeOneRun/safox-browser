#include "pageview.h"
#include "ui_pageview.h"

PageView::PageView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PageView)
{
    ui->setupUi(this);
}

PageView::~PageView()
{
    delete ui;
}
