/*
 * @Author: SC-WSKun 540610423@qq.com
 * @Date: 2022-05-18 10:23:02
 * @LastEditors: SC-WSKun 540610423@qq.com
 * @LastEditTime: 2022-05-18 19:54:14
 * @FilePath: \safox\src\core\history\historywidget.cpp
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
    this->setAttribute(Qt::WA_DeleteOnClose,true);
    this->setGeometry(x+1,y,width,height);
    this->index = 0;
    this->setStyleSheet("QTableWidget{background:rgba(46, 50, 53, 255);gridline-color:rgba(219,219,219,255);border: 1px solid rgba(219,219,219,255);}"
                        "QHeaderView::section{background:rgba(46, 50, 53, 255);color:white;border: 1px solid rgba(219,219,219,255);font-size:20px;}"
                        "QTableWidget::item{color:white;font-size:14px;border:0;}");

    initTable();
//    loadData(this->index);


    this->historyBar = new HistoryBar(this,0,0,399,980,root);
    connect(this->historyBar,&HistoryBar::on_dateBtn_passSignal,this,&HistoryWidget::loadData);


    QLabel* nameTitle = new QLabel(this);
    nameTitle->setText("名称");
    nameTitle->setGeometry(460,622,268,20);
    nameTitle->setStyleSheet("QLabel{background-color:transparent;color:white;font-size:15px;color:white;}");
    name = new QLineEdit(this);
    name->setGeometry(460,650,400,32);
    name->setStyleSheet("QLineEdit{background-color:#7A7A7A;color:white;font-size:15px;}");

    QLabel* urlTitle = new QLabel(this);
    urlTitle->setText("网址");
    urlTitle->setGeometry(460,717,268,20);
    urlTitle->setStyleSheet("QLabel{background-color:transparent;color:white;font-size:15px;}");
    url = new QLineEdit(this);
    url->setGeometry(460,755,400,32);
    url->setStyleSheet("QLineEdit{background-color:#7A7A7A;color:white;font-size:15px;}");

    QLabel* tagTitle = new QLabel(this);
    tagTitle->setText("标签");
    tagTitle->setGeometry(460,822,268,20);
    tagTitle->setStyleSheet("QLabel{background-color:transparent;color:white;font-size:15px;}");
    tag = new QLineEdit(this);
    tag->setGeometry(460,850,400,32);
    tag->setStyleSheet("QLineEdit{background-color:#7A7A7A;color:white;font-size:15px;}");

    connect(this->historyTable,&QTableWidget::itemClicked,this,&HistoryWidget::getItem);
    connect(this->historyTable,&QTableWidget::itemDoubleClicked,this,&HistoryWidget::open_new_tab);
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
    this->historyTable->setColumnCount(4);
    this->historyTable->setRowCount(11);
    QStringList strs = {"名称", "图标", "网址",""};
    this->historyTable->setHorizontalHeaderLabels(strs);
    this->historyTable->horizontalHeader()->setFixedHeight(48);
    this->historyTable->verticalHeader()->setDefaultSectionSize(48);
    this->historyTable->setColumnWidth(0,555);
    this->historyTable->setColumnWidth(1,50);
    this->historyTable->setColumnWidth(2,780);
    this->historyTable->setColumnWidth(3,100);
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
        QLabel *iconLabel = new QLabel();
        iconLabel->setPixmap(QPixmap(IconManager::get_local_cache(i->iconUrl.toDisplayString())));
//        iconLabel->setPixmap(QPixmap(":/icon/image/clock.png"));
        iconLabel->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        QTableWidgetItem *item2 = new QTableWidgetItem(i->url.toDisplayString());
        this->historyTable->setItem(rowIndex,0,item0);
        this->historyTable->setCellWidget(rowIndex,1,iconLabel);
        this->historyTable->setItem(rowIndex,2,item2);
        QPushButton* closeBtn = new QPushButton();
        closeBtn->setText("删除历史");
        closeBtn->setStyleSheet("QPushButton{background-color:transparent;color:white;font-size:15px;}");
        connect(closeBtn,&QPushButton::clicked,this,[=](){
            int deleteIndex = historyTable->currentRow();
            if(deleteIndex!=-1){
                historyTable->removeRow(deleteIndex);
                root->Browser::m_history->deleteHistoryEntryHelp(index,deleteIndex);
            }
        });
       this->historyTable->setCellWidget(rowIndex,3,closeBtn);
        rowIndex++;
        i++;
    }
}

void HistoryWidget::getItem(QTableWidgetItem* item){
    int cur_row = item->row();
    std::string tempStr = this->historyTable->item(cur_row,0)->text().toStdString();
    QString itemStr = QString::fromStdString(tempStr);
    this->name->setText(itemStr);
    tempStr = this->historyTable->item(cur_row,2)->text().toStdString();
    itemStr = QString::fromStdString(tempStr);
    this->url->setText(itemStr);
}

void HistoryWidget::open_new_tab(QTableWidgetItem* item){
    int cur_row = item->row();
    std::string tempStr = this->historyTable->item(cur_row,2)->text().toStdString();
    QString itemStr = QString::fromStdString(tempStr);
    root->my_tab->createTab();
    root->my_tab->setUrl(QUrl(itemStr));
    root->my_tab->show();
    root->historyTest = nullptr;
    this->close();
}


