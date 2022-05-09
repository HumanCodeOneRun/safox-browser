#include "historywidget.h"
#include "ui_historywidget.h"

//todo: add TableWidget

HistoryWidget::HistoryWidget(QWidget *parent,int x,int y,int width,int height) :
    QWidget(parent),
    ui(new Ui::HistoryWidget)
{
    ui->setupUi(this);
    this->setGeometry(x,y,width,height);

//  todo：获取userid
    int userid = 11111111;
//
    QList<qint64> userHistoryList = loadHistory(userid);

//    遍历QList：
//    QList<qint64>::iterator i = userHistoryList.begin();
//    while(i!=userHistoryList.end()){
//        qDebug()<<*i;
//        i++;
//    }

    this->historyBar = new HistoryBar(this,0,0,399,980,userid);
    QTableWidget* historyTable=new QTableWidget(this);
    historyTable->setGeometry(400,0,1520,600);
    historyTable->setColumnCount(3);
    historyTable->setRowCount(userHistoryList.length());
    QStringList strs = {"名称", "标签", "网址"};
    historyTable->setHorizontalHeaderLabels(strs);
    historyTable->setColumnWidth(0,505);
    historyTable->setColumnWidth(1,133);
    historyTable->setColumnWidth(2,880);

}

HistoryWidget::~HistoryWidget()
{
    delete ui;
}

QList<qint64> HistoryWidget::loadHistory(const int &userid){
    History* userHistory = new History(userid);
    // 测试添加历史
    // WebView* userWebview = new WebView(this);
    // userWebview->load(QUrl("https://doc.qt.io/qt-5/qwebengineview.html"));
    // userWebview->show();
    // userHistory->addHistoryEntry(userWebview);
    QList<qint64> res = userHistory->queryDayTimestamp();
    return res;
}
