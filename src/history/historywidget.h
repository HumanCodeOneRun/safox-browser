#ifndef HISTORYWIDGET_H
#define HISTORYWIDGET_H

#include <QWidget>
#include <QTableWidget>
#include "historybar.h"

namespace Ui {
class HistoryWidget;
}

class HistoryWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HistoryWidget(QWidget *parent = nullptr,int x=0,int y=0,int width=0,int height=0);
    HistoryBar* historyBar;
    ~HistoryWidget();

private:
    Ui::HistoryWidget *ui;
    QList<qint64> loadHistory(const int &userid);
};

#endif // HISTORYWIDGET_H
