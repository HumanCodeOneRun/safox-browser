/*
 * @Author: SC-WSKun 540610423@qq.com
 * @Date: 2022-05-14 11:54:54
 * @LastEditors: SC-WSKun 540610423@qq.com
 * @LastEditTime: 2022-05-17 16:24:44
 * @FilePath: \FolkTell\src\lib\history\historywidget.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#ifndef HISTORYWIDGET_H
#define HISTORYWIDGET_H

#include <QWidget>
#include <QTableWidget>
#include <QHeaderView>
#include <QDate>
#include <QLabel>
#include <QGroupBox>
#include "historybar.h"

namespace Ui {
class HistoryWidget;
}
class BrowserWindow;
class HistoryWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HistoryWidget(QWidget *parent = nullptr,int x=0,int y=0,int width=0,int height=0,BrowserWindow *root=nullptr);
    int width,height;
    HistoryBar* historyBar;
    ~HistoryWidget();

private:
    Ui::HistoryWidget *ui;
    void initTable();
    void paintEvent(QPaintEvent *event);
};

#endif // HISTORYWIDGET_H
