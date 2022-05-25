#ifndef HISTORYWIDGET_H
#define HISTORYWIDGET_H

#include <QWidget>
#include <QTableWidget>
#include <QHeaderView>
#include <QDate>
#include <QLabel>
#include <QGroupBox>
#include <QLineEdit>
#include "src/ui/history/historybar.h"

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
    BrowserWindow* root;
    HistoryBar* historyBar;
    QTableWidget* historyTable;
    QLineEdit* name;
    QLineEdit* tag;
    QLineEdit* url;
    int index;
    ~HistoryWidget();

private:
    Ui::HistoryWidget *ui;
    void initTable();
    void paintEvent(QPaintEvent *event);
    void loadData(int index);

private slots:
    void getItem(QTableWidgetItem* item);
    void accept_dateBtn_signal(int index);

};

#endif // HISTORYWIDGET_H
