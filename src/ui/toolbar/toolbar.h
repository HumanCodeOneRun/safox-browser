/*
 * @Author: your name
 * @Date: 2022-05-03 11:39:08
 * @LastEditTime: 2022-05-28 01:31:31
 * @LastEditors: SC-WSKun 540610423@qq.com
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \safox\safox\src\toolbar.h
 */
#ifndef TOOLBAR_H
#define TOOLBAR_H
#include <QMenu>
#include <QHash>
#include <QToolButton>
#include <QLineEdit>
#include <QIcon>
#include <QPointer>
#include<QPainter>
#include<QStyleOption>
#include <QAction>
#include <QTimer>
#include "src/ui/history/historywidget.h"
#include "../popupmenu/popupmenu.h"
#include "searchengineMgr.h"
#include <QUrl>
#include <QRegularExpression>

class Preferences;
class HistoryMenu;
class BookmarksMenu;
class BrowserWindow;

/* 重写QLineEdit,添加点击选取全部文字 */
class SeachBar:public QLineEdit{
    Q_OBJECT
public:
    explicit SeachBar(QWidget *parent = nullptr);
    void focusInEvent(QFocusEvent* event);
};

class Toolbar:public QWidget
{
    Q_OBJECT

public:
    explicit Toolbar(QWidget *parent = nullptr,int x = 0,int y = 0,int width = 0,int height = 0,BrowserWindow* root=nullptr);
    BrowserWindow* root;
    QToolButton* backBtn;
    QToolButton* goBtn;
    QToolButton* bookmarkerBtn;
    QToolButton* historyBtn;
    QToolButton* homeBtn;
    QToolButton* downloadBtn;
    QToolButton* accountBtn;
    QToolButton* settingBtn;
    QToolButton* addBtn;
    QLineEdit* urlBar;
    HistoryWidget* historyTest;
    void setParentWindow(BrowserWindow *Parent);
    bool IsUrl(QString input);

private:
    int init_x;
    int init_y;
    int width;
    int height;
    void init();
    void paintEvent(QPaintEvent *event);
    BrowserWindow* m_window;
    QPalette palette;
    SearchEngineManager* m_searchManager;

private slots:
    void on_historyBtn_clicked();
    void on_bookmarkerBtn_clicked();
    void on_settingBtn_clicked();
    void on_accountBtn_clicked();
    void on_downloadBtn_clicked();
    void home_page();
    void start_search();
    void back_page();
    void front_page();

signals:
    void on_historyBtn_passSignal();
    void on_bookmarkerBtn_passSignal();
    void on_accountBtn_passSignal();
    void on_downloadBtn_passSignal();   
    void on_goBtn_passSignal();
    void on_homeBtn_passSignal();
    void on_backBtn_passSignal();

};

#endif // TOOLBAR_H
