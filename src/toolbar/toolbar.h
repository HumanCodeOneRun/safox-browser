/*
 * @Author: your name
 * @Date: 2022-05-03 11:39:08
 * @LastEditTime: 2022-05-03 11:39:41
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \FolkTell\FolkTell\src\toolbar.h
 */
#ifndef TOOLBAR_H
#define TOOLBAR_H
#include <QMenu>
#include <QHash>
#include<QToolButton>
#include<QLineEdit>
#include <QPointer>
#include<QPainter>
#include<QStyleOption>

class Preferences;
class HistoryMenu;
class BookmarksMenu;
class BrowserWindow;

class Toolbar:public QWidget
{
    Q_OBJECT

public:
    explicit Toolbar(QWidget *parent = nullptr,int x = 0,int y = 0,int width = 0,int height = 0);
    QToolButton* bookmarkerBtn;
    QToolButton* historyBtn;
    QToolButton* homeBtn;
    QToolButton* downloadBtn;
    QToolButton* accountBtn;
    QToolButton* settingBtn;
    QToolButton* addBtn;
    QLineEdit* urlBar;

private:
    int init_x;
    int init_y;
    int width;
    int height;
    void init();
    void paintEvent(QPaintEvent *event);
    BrowserWindow* m_window;
    QPalette palette;
};

#endif // TOOLBAR_H
