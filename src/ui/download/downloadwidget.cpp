#include "downloadwidget.h"
#include "ui_downloadwidget.h"

DownloadWidget::DownloadWidget(QWidget *parent,QToolButton* btn) :
    QWidget(parent),
    ui(new Ui::DownloadWidget)
{
    ui->setupUi(this);
    this->setStyleSheet("QWidget{width:300px;height:400px;}");
    int x = btn->x()-300+btn->width();
    int y = btn->y()+btn->height();
    this->setGeometry(x,y,300,400);

    //todo: 与download的对接
}

DownloadWidget::~DownloadWidget()
{
    delete ui;
}

void DownloadWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);

    /* 绘制downloadWidget背景 */
    p.setPen(Qt::NoPen);
    p.setBrush(QColor(35, 38, 43, 100));
    p.drawRect(0,0,this->width(),this->height());
}
