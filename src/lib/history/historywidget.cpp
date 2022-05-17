#include "historywidget.h"
#include "ui_historywidget.h"
#include <browserwindow/browserwindow.h>
//todo: add TableWidget

HistoryWidget::HistoryWidget(QWidget *parent,int x,int y,int width,int height,BrowserWindow* root) :
    QWidget(parent),
    ui(new Ui::HistoryWidget)
{
    qDebug()<<"[test] slot1 in historywidget";
    ui->setupUi(this);
    this->setGeometry(x,y,width,height);
    this->width = width;
    this->height = height;
    this->setStyleSheet("QTableWidget{background:rgba(46, 50, 53, 100);gridline-color:rgba(219,219,219,100);}"
                        "QHeaderView::section{background:rgba(46, 50, 53, 100);color:white;border: 1px solid rgba(219,219,219,100);font-size:20px;}");



/*--------todo：获取userid-------------*/
    int userid = root->Browser::userid;
/*------------------------------------*/
    qDebug()<<"[test] slot2 in historywidget";
    QList<qint64> historyDateList = root->Browser::baseHistory->queryDayTimestamp();
    QDateTime today = QDateTime::currentDateTime();
    qDebug()<<"[test] slot3 in historywidget";

/*--------遍历QList：------------------*/
    QList<qint64>::iterator i = historyDateList.begin();
    while(i!=historyDateList.end()){
        QDateTime time = QDateTime::fromMSecsSinceEpoch(*i);
        qDebug()<<time;
        i++;
    }
/*-------------------------------------*/

    this->historyBar = new HistoryBar(this,0,0,399,980,userid);
    initTable();

    QLabel* nameTitle = new QLabel(this);
    nameTitle->setText("名称");
    nameTitle->setGeometry(460,622,268,20);
    nameTitle->setStyleSheet("QLabel{background-color:rgba(46, 50, 53, 100);color:white;}");

    QLabel* urlTitle = new QLabel(this);
    urlTitle->setText("网址");
    urlTitle->setGeometry(460,717,268,20);
    urlTitle->setStyleSheet("QLabel{background-color:rgba(46, 50, 53, 100);color:white;}");

    QLabel* tagTitle = new QLabel(this);
    tagTitle->setText("标签");
    tagTitle->setGeometry(460,822,268,20);
    tagTitle->setStyleSheet("QLabel{background-color:rgba(46, 50, 53, 100);color:white;}");

}

HistoryWidget::~HistoryWidget()
{
    delete ui;
}


void HistoryWidget::initTable(){
    QTableWidget* historyTable=new QTableWidget(this);
    historyTable->setGeometry(400,0,1520,578);
    historyTable->verticalHeader()->setVisible(false);
    historyTable->setColumnCount(3);
//    historyTable->setRowCount(userHistoryList.length());
    historyTable->setRowCount(11);
    QStringList strs = {"名称", "标签", "网址"};
    historyTable->setHorizontalHeaderLabels(strs);
    historyTable->horizontalHeader()->setFixedHeight(48);
    historyTable->verticalHeader()->setDefaultSectionSize(48);
    historyTable->setColumnWidth(0,505);
    historyTable->setColumnWidth(1,133);
    historyTable->setColumnWidth(2,880);
}

void HistoryWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);

    /* 绘制historyWidget背景 */
    p.setPen(Qt::NoPen);
    p.setBrush(QColor(46, 50, 53, 100));
    p.drawRect(0,0,this->width,this->height);
}
