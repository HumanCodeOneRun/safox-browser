#ifndef BROWSERWINDOW_H
#define BROWSERWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include "toolbar.h"
#include <cassert>

QT_BEGIN_NAMESPACE
namespace Ui { class BrowserWindow; }
QT_END_NAMESPACE

class BrowserWindow : public QMainWindow
{
    Q_OBJECT

public:
    BrowserWindow(QWidget *parent = nullptr, const int & window_id=0);
    int curHeight,curWidth;
    ToolBar* tb;
    ~BrowserWindow();

    int get_windowid();
    bool set_windowid(const int & window_id);

private:
    Ui::BrowserWindow *ui;
    
    // for multi-window purpose
    int id;
};
#endif // BROWSERWINDOW_H
