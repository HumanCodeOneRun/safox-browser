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
#include "..\toolbar\toolbar.h"
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
    Toolbar* tb;
    ~BrowserWindow();

private slots:
    void on_closeBtn_clicked();

    void on_minBtn_clicked();

    void on_hidBtn_clicked();

private:
    Ui::BrowserWindow *ui;
};
#endif // BROWSERWINDOW_H
