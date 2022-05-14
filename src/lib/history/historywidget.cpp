#include "historywidget.h"
#include "ui_historywidget.h"

//todo: add TableWidget

HistoryWidget::HistoryWidget(QWidget *parent,int x,int y,int width,int height) :
    QWidget(parent),
    ui(new Ui::HistoryWidget)
{
    ui->setupUi(this);
    this->setGeometry(x,y,width,height);
    this->setStyleSheet("QTableWidget{background:rgba(46, 50, 53, 100);gridline-color:rgba(219,219,219,100);}"
                        "QHeaderView::section{background:rgba(46, 50, 53, 100);color:white;border: 1px solid rgba(219,219,219,100);font-size:20px;}");



/*--------todo：获取userid-------------*/
    int userid = 11111111;
/*------------------------------------*/

    QList<qint64> historyDateList = loadHistory(userid);
    QDateTime today = QDateTime::currentDateTime();

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


}

HistoryWidget::~HistoryWidget()
{
    delete ui;
}

QList<qint64> HistoryWidget::loadHistory(const int &userid){
    History* userHistory = new History(userid);
    // 测试添加历史
//     WebView* userWebview = new WebView(this);
//     userWebview->load(QUrl("https://doc.qt.io/qt-5/qwebengineview.html"));
//     userWebview->show();
//     userHistory->addHistoryEntry(userWebview);
    QList<qint64> res = userHistory->queryDayTimestamp();
    return res;
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
