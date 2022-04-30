/*
 * @Author: your name
 * @Date: 2022-04-30 09:27:17
 * @LastEditTime: 2022-04-30 09:29:24
 * @LastEditors: your name
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \FolkTell\FolkTell\FolkTell\src\browserwindow.h
 */
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
    BrowserWindow(QWidget *parent = nullptr, const int & window_id=0);
    int curHeight,curWidth;
    Toolbar* tb;
    ~BrowserWindow();

private slots:
    void on_closeBtn_clicked();

    void on_minBtn_clicked();

    void on_hidBtn_clicked();

    int get_windowid();
    
    bool set_windowid(const int & window_id);

private:
    Ui::BrowserWindow *ui;
    
    // for multi-window purpose
    int id;
};
#endif // BROWSERWINDOW_H
