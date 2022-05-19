/*
 * @Author: SC-WSKun 540610423@qq.com
 * @Date: 2022-05-18 10:23:02
 * @LastEditors: SC-WSKun 540610423@qq.com
 * @LastEditTime: 2022-05-18 19:54:36
 * @FilePath: \FolkTell\src\core\history\historybar.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include "src/ui/history/historybar.h"
#include "ui_historybar.h"
#include <src/ui/history/historywidget.h>
#include "src/ui/browserwindow/browserwindow.h"

HistoryBar::HistoryBar(QWidget *parent,int x,int y,int width,int height,BrowserWindow* root) :
    QWidget(parent),x(x),y(y),width(width),height(height)
{
    this->setGeometry(x,y,width,height);
    this->setStyleSheet("QToolButton{background-color:rgba(46, 50, 53, 100);padding-left:55px;border:none;color:white;font-size:14px;}");

    QIcon clock(":/icon/image/clock.png");
    QIcon down(":/icon/image/down.png");

    QToolButton* historyBtn = new QToolButton(this);
    historyBtn->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    historyBtn->setGeometry(0,0,398,50);
    historyBtn->setText("历史记录");
    historyBtn->setStyleSheet("QToolButton{background-color:rgba(46, 50, 53, 100);padding-left:10px;border:none;color:white;font-size:14px;}");
    historyBtn->setIcon(down);
    historyBtn->setIconSize(QSize(20,20));


//    QToolButton* today = new QToolButton(this);
//    today->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
//    today->setGeometry(0,50,398,50);
//    today->setText("今天");
//    today->setIcon(clock);
//    today->setIconSize(QSize(20,20));

//    QToolButton* yesterday = new QToolButton(this);
//    yesterday->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
//    yesterday->setGeometry(0,100,398,50);
//    yesterday->setText("昨天");
//    yesterday->setIcon(clock);
//    yesterday->setIconSize(QSize(20,20));


//    QToolButton* passSevenDay = new QToolButton(this);
//    passSevenDay->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
//    passSevenDay->setGeometry(0,150,398,50);
//    passSevenDay->setText("过去7天");
//    passSevenDay->setIcon(clock);
//    passSevenDay->setIconSize(QSize(20,20));

    /*------------------------------------*/
        QList<qint64> historyDateList = root->Browser::m_history->queryDayTimestamp();
//        QDateTime today = QDateTime::currentDateTime();

    /*--------遍历QList：------------------*/
        QList<qint64>::iterator i = historyDateList.begin();
        int btnY = 50;
        int listIndex = 0;
        while(i!=historyDateList.end()){
            QDateTime time = QDateTime::fromMSecsSinceEpoch(*i);
            qDebug()<<time.toString("yyyy-MM-dd");
            QToolButton* tempBtn = new QToolButton(this);
            connect(tempBtn,&QToolButton::clicked,this,[=](){HistoryBar::on_test_clicked(listIndex);});
            tempBtn->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
            tempBtn->setIcon(clock);
            tempBtn->setIconSize(QSize(20,20));
            tempBtn->setGeometry(0,btnY,398,50);
            tempBtn->setText(time.toString("yyyy-MM-dd"));
            btnY+=50;
            i++;
            listIndex++;
        }
    /*-------------------------------------*/

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

void HistoryBar::on_test_clicked(int index){
    emit on_dateBtn_passSignal(index);
}
