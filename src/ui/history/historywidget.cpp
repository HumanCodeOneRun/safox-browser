/*
 * @Author: SC-WSKun 540610423@qq.com
 * @Date: 2022-05-18 10:23:02
 * @LastEditors: SC-WSKun 540610423@qq.com
 * @LastEditTime: 2022-05-18 19:54:14
 * @FilePath: \FolkTell\src\core\history\historywidget.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include "src/ui/history/historywidget.h"
#include "ui_historywidget.h"
#include "src/ui/browserwindow/browserwindow.h"
//todo: add TableWidget

HistoryWidget::HistoryWidget(QWidget *parent,int x,int y,int width,int height,BrowserWindow* root) :
    QWidget(parent),width(width),height(height),root(root),
    ui(new Ui::HistoryWidget)
{
    ui->setupUi(this);
    this->setGeometry(x,y,width,height);
    this->index = 0;
    this->setStyleSheet("QTableWidget{background:rgba(46, 50, 53, 100);gridline-color:rgba(219,219,219,100);}"
                        "QHeaderView::section{background:rgba(46, 50, 53, 100);color:white;border: 1px solid rgba(219,219,219,100);font-size:20px;}"
                        "QTableWidget::item{color:white;font-size:14px;border:0;padding-left:20px;}");

    initTable();
//    loadData(this->index);


    this->historyBar = new HistoryBar(this,0,0,399,980,root);
    connect(this->historyBar,&HistoryBar::on_dateBtn_passSignal,this,&HistoryWidget::accept_dateBtn_signal);


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

    connect(this->historyTable,&QTableWidget::itemClicked,this,&HistoryWidget::getItem);
}

HistoryWidget::~HistoryWidget()
{
    delete ui;
}


void HistoryWidget::initTable(){
//    qDebug("initTable");
    this->historyTable=new QTableWidget(this);
    this->historyTable->setGeometry(400,0,1520,578);
    this->historyTable->verticalHeader()->setVisible(false);
    this->historyTable->setColumnCount(3);
    this->historyTable->setRowCount(11);
    QStringList strs = {"名称", "标签", "网址"};
    this->historyTable->setHorizontalHeaderLabels(strs);
    this->historyTable->horizontalHeader()->setFixedHeight(48);
    this->historyTable->verticalHeader()->setDefaultSectionSize(48);
    this->historyTable->setColumnWidth(0,505);
    this->historyTable->setColumnWidth(1,133);
    this->historyTable->setColumnWidth(2,880);
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

void HistoryWidget::loadData(int index){
//    qDebug("loadData");
    this->historyTable->clearContents();
    QList<HistoryEntry> testHistory = root->Browser::m_history->queryDayHistoryEntry(index);
    if(testHistory.length()>11){
        this->historyTable->setRowCount(testHistory.length());
    }
    QList<HistoryEntry>::iterator i = testHistory.begin();
    int rowIndex = 0;
    while(i!=testHistory.end()){
        QTableWidgetItem *item0 = new QTableWidgetItem(i->title);
        QIcon itemIcon(i->iconUrl.toDisplayString());
        item0->setIcon(itemIcon);
//        QTableWidgetItem *item1 = new QTableWidgetItem(i->url.tag());
        QTableWidgetItem *item2 = new QTableWidgetItem(i->url.toDisplayString());
        this->historyTable->setItem(rowIndex,0,item0);
//        this->historyTable->setItem(rowIndex,1,item1);
        this->historyTable->setItem(rowIndex,2,item2);
        rowIndex++;
        i++;
    }
}

void HistoryWidget::getItem(QTableWidgetItem* item){
    qDebug()<<item->text();
}

void HistoryWidget::accept_dateBtn_signal(int index){
    qDebug("receive signal");
    qDebug()<<index;
    loadData(index);
}



