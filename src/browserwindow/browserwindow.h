/*
 * @Author: your name
 * @Date: 2022-05-03 11:39:08
 * @LastEditTime: 2022-05-03 11:41:06
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \FolkTell\FolkTell\src\browserwindow.h
 */
#ifndef BROWSERWINDOW_H
#define BROWSERWINDOW_H

#include <QMainWindow>
#include <QWidget>
<<<<<<< HEAD
<<<<<<< HEAD
#include "../toolbar/toolbar.h"
#include "../history/historywidget.h"
=======
#include "..\toolbar\toolbar.h"
#include "..\history\historywidget.h"
#include "..\bookmark\bookmarkwidget.h"
>>>>>>> 3eaab7e (add bookmarkWidget)
=======
#include "../lib/toolbar/toolbar.h"
#include "../lib/history/historywidget.h"
#include "../lib/bookmark/bookmarkwidget.h"
#include "../lib/taskscheduler/databasetaskscheduler.h"
#include "../browser.h"
>>>>>>> 950f40a (edit browser)
#include <QToolButton>
#include <QSystemTrayIcon>
#include <QAction>
#include <QMenu>

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
    int userid;
    DatabaseTaskScheduler* m_taskScheduler;
    BrowserWindow(QWidget *parent = nullptr);
    void CreateSystemTrayIcon();
    ~BrowserWindow();

private slots:
    void on_closeBtn_clicked();

    void on_minBtn_clicked();

    void on_hidBtn_clicked();

    void accept_history_signal();

    void accept_bookmarker_signal();

private:
    Ui::BrowserWindow *ui;
};
#endif // BROWSERWINDOW_H
