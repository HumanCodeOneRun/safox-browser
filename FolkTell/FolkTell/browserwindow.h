#ifndef BROWSERWINDOW_H
#define BROWSERWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include "toolbar.h"
#include <QToolButton>

QT_BEGIN_NAMESPACE
namespace Ui { class BrowserWindow; }
QT_END_NAMESPACE

class BrowserWindow : public QMainWindow
{
    Q_OBJECT

public:
    BrowserWindow(QWidget *parent = nullptr);
    int curHeight,curWidth;
    ToolBar* tb;
    ~BrowserWindow();

private slots:
    void on_closeBtn_clicked();

    void on_minBtn_clicked();

private:
    Ui::BrowserWindow *ui;
};
#endif // BROWSERWINDOW_H
