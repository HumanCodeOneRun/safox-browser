#ifndef HISTORYBAR_H
#define HISTORYBAR_H

#include <QWidget>
#include <QLabel>
#include <QPainter>
#include <QStyleOption>
#include <QToolButton>
#include <QList>
#include "history.h"

namespace Ui {
class HistoryBar;
}

class HistoryBar : public QWidget
{
    Q_OBJECT

public:
    explicit HistoryBar(QWidget *parent = nullptr,int x=0,int y=0,int width=0,int height=0,int userid=11111111);
    int x,y,width,height;
    ~HistoryBar();

private:
    Ui::HistoryBar *ui;
    void paintEvent(QPaintEvent *event);
    void loadHistory(const int &userid);
};

#endif // HISTORYBAR_H
