/*
 * @Author: SC-WSKun 540610423@qq.com
 * @Date: 2022-05-18 10:23:02
 * @LastEditors: SC-WSKun 540610423@qq.com
 * @LastEditTime: 2022-05-18 19:54:27
 * @FilePath: \safox\src\core\history\historybar.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#ifndef HISTORYBAR_H
#define HISTORYBAR_H

#include <QWidget>
#include <QLabel>
#include <QPainter>
#include <QStyleOption>
#include <QToolButton>
#include <QList>
#include <QObject>
#include "history.h"

class HistoryWidget;
class BrowserWindow;
class HistoryBar : public QWidget
{
    Q_OBJECT

public:
    explicit HistoryBar(QWidget *parent = nullptr,int x=0,int y=0,int width=0,int height=0,BrowserWindow* root=nullptr);
    int x,y,width,height;

private:
    void paintEvent(QPaintEvent *event);
    void loadHistory(const int &userid);

private slots:
    void on_test_clicked(int index);

signals:
    void on_dateBtn_passSignal(int index);
};
#endif // HISTORYBAR_H

