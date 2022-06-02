#ifndef DOWNLOADWIDGET_H
#define DOWNLOADWIDGET_H

#include <QWidget>
#include <QToolButton>
#include <QStyleOption>
#include <QPainter>
#include <QLabel>
#include <QProgressBar>
#include <QToolButton>
#include <QTimer>
#include <QScrollArea>
#include <QHBoxLayout>
#include <downloadmanager.h>

namespace Ui {
class DownloadWidget;
}
class BrowserWindow;
class DownloadWidget;
class DownloadItemWidget : public QWidget{
    Q_OBJECT
public:
    explicit DownloadItemWidget(QWidget* parent=nullptr,QString iconUrl="",QString title="",QString downloadUrl=nullptr,BrowserWindow* root=nullptr);
    ~DownloadItemWidget();
private:
    BrowserWindow* root;
    QTimer* timer;
    QString downloadUrl;
    QToolButton* startBtn;
    QToolButton* deleteBtn;
    QProgressBar* progress;
private slots:
    void go();
    void del();
    void timeoutslots();
signals:
    void on_del_passSignal();
};

class DownloadWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DownloadWidget(QWidget *parent = nullptr,QToolButton* btn=nullptr,BrowserWindow* root=nullptr);
    BrowserWindow* root;
    ~DownloadWidget();

private:
    QScrollArea* items;
    QVBoxLayout *labelLayout;
    QWidget* scrollWidget;
    int index;
    Ui::DownloadWidget *ui;
    void paintEvent(QPaintEvent *event);
private slots:
    void addItem(QString url,QString name);
};

#endif // DOWNLOADWIDGET_H
