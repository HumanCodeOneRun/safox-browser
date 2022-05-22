/*
 * @Author: your name
 * @Date: 2022-05-03 11:39:08
 * @LastEditTime: 2022-05-17 16:23:32
 * @LastEditors: SC-WSKun 540610423@qq.com
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \FolkTell\FolkTell\src\browserwindow.h
 */
#ifndef BROWSERWINDOW_H
#define BROWSERWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QVBoxLayout>
#include "tabwidget.h"
#include "toolbar.h"
#include "historywidget.h"
#include "bookmarkwidget.h"
#include "toolbar.h"
#include "historywidget.h"
#include "bookmarkwidget.h"
#include "databasetaskscheduler.h"
#include "browser.h"
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

    tabwidget *returnTab() const;

private slots:
    void on_closeBtn_clicked();

    void on_minBtn_clicked();

    void on_hidBtn_clicked();

    void accept_history_signal();

    void accept_bookmarker_signal();

private:
    Ui::BrowserWindow *ui;
    tabwidget *my_tab;
};
#endif // BROWSERWINDOW_H
