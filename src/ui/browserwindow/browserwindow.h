/*
 * @Author: your name
 * @Date: 2022-05-03 11:39:08
 * @LastEditTime: 2022-05-17 16:23:32
 * @LastEditors: SC-WSKun 540610423@qq.com
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath:
 */
#ifndef BROWSERWINDOW_H
#define BROWSERWINDOW_H

#include <QMainWindow>
#include <QWidget>

#include "toolbar.h"
#include "src/ui/history/historywidget.h"
#include "src/ui/bookmark/bookmarkwidget.h"
#include "src/ui/user/accountwidget.h"
#include "src/ui/download/downloadwidget.h"
#include "databasetaskscheduler.h"
#include "src/core/browser/browser.h"
#include <QToolButton>
#include <QSystemTrayIcon>
#include <QMouseEvent>
#include <QAction>
#include <QMenu>
#include "service.h"
QT_BEGIN_NAMESPACE
class HistoryBar;
namespace Ui { class BrowserWindow; }
QT_END_NAMESPACE

class BrowserWindow : public QMainWindow, public Browser
{
    Q_OBJECT

public:
    int curHeight,curWidth;
    double scale;
    Toolbar* tb;
    HistoryWidget* historyTest;
    BookmarkWidget* bookmarkTest;
    AccountWidget* accountTest;
    DownloadWidget* downloadTest;
    BrowserWindow(int userid, const MyServiceLocator &serviceLocator, QWidget *parent = NULL);
    void CreateSystemTrayIcon();
    void paintEvent(QPaintEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    ~BrowserWindow();

private slots:
    void on_closeBtn_clicked();

    void on_minBtn_clicked();

    void on_hidBtn_clicked();

    void accept_history_signal();

    void accept_bookmarker_signal();

    void accept_account_signal();

    void accept_download_signal();

private:
    Ui::BrowserWindow *ui;
};
#endif // BROWSERWINDOW_H
