/*
 * @Author: SC-WSKun 540610423@qq.com
 * @Date: 2022-05-14 22:01:55
 * @LastEditors: SC-WSKun 540610423@qq.com
 * @LastEditTime: 2022-05-17 17:56:24
 * @FilePath: \safox\src\core\bookmark\bookmarkwidget.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#ifndef BOOKMARKWIDGET_H
#define BOOKMARKWIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QIcon>
#include <vector>
#include <QAction>
#include <QScrollArea>
#include <QStyleOption>
#include <QVBoxLayout>
#include <QPainter>
#include <QVector>
#include <QVariant>
#include <QComboBox>
#include <QScrollBar>
#include "bookmarkmodel.h"
#include "bookmarkitem.h"
#include "databasetaskscheduler.h"

namespace Ui {
class BookmarkWidget;
}
class BrowserWindow;

class BookmarkWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BookmarkWidget(QWidget *parent = nullptr,int x=0,int y=0,int width=0,int height=0,BrowserWindow* root=nullptr);
    int width,height;
    QWidget* scrollWidget;
    BrowserWindow* root;
    QScrollArea* scrollView;
    std::vector<int> gidArr;
    QVector<QVector<QVariant>> userBookmark;
    ~BookmarkWidget();

private:
    Ui::BookmarkWidget *ui;
    QLineEdit* searchKey;
    void paintEvent(QPaintEvent *event);
private slots:
    void on_clicked_bookmarkerGroup(int);

};

#endif // BOOKMARKWIDGET_H
