#include "historybar.h"
#include "ui_historybar.h"

HistoryBar::HistoryBar(QWidget *parent,int x,int y,int width,int height,int userid) :
    QWidget(parent),
    ui(new Ui::HistoryBar)
{
    ui->setupUi(this);
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->setGeometry(x,y,width,height);
    this->setStyleSheet("QToolButton{background-color:rgba(46, 50, 53, 100);padding-left:55px;border:none;color:white;font-size:14px;}");

    QIcon clock(":/icon/image/clock.png");
    QIcon down(":/icon/image/down.png");

    QToolButton* historyBtn = new QToolButton(this);
    historyBtn->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    historyBtn->setGeometry(0,0,398,50);
    historyBtn->setText("历史记录");
    historyBtn->setIcon(down);
    historyBtn->setIconSize(QSize(20,20));


    QToolButton* today = new QToolButton(this);
    today->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    today->setGeometry(0,50,398,50);
    today->setText("今天");
    today->setIcon(clock);
    today->setIconSize(QSize(20,20));

    QToolButton* yesterday = new QToolButton(this);
    yesterday->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    yesterday->setGeometry(0,100,398,50);
    yesterday->setText("昨天");
    yesterday->setIcon(clock);
    yesterday->setIconSize(QSize(20,20));


    QToolButton* passSevenDay = new QToolButton(this);
    passSevenDay->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    passSevenDay->setGeometry(0,150,398,50);
    passSevenDay->setText("过去7天");
    passSevenDay->setIcon(clock);
    passSevenDay->setIconSize(QSize(20,20));

    loadHistory(userid);

}

HistoryBar::~HistoryBar()
{
    delete ui;
}


void HistoryBar::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);

    /* 绘制historyWidget背景 */
    p.setPen(Qt::NoPen);
    p.setBrush(QColor(46, 50, 53, 70));
    p.drawRect(0,0,this->width,this->height);
}

void HistoryBar::loadHistory(const int &userid){

}
