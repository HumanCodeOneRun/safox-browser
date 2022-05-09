#ifndef BOOKMARKWIDGET_H
#define BOOKMARKWIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QIcon>
#include <QAction>
#include <QGroupBox>
#include <QStyleOption>
#include <QPainter>

namespace Ui {
class BookmarkWidget;
}

class BookmarkWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BookmarkWidget(QWidget *parent = nullptr,int x=0,int y=0,int width=0,int height=0);
    int width,height;
    ~BookmarkWidget();

private:
    Ui::BookmarkWidget *ui;
    QLineEdit* searchKey;
    void paintEvent(QPaintEvent *event);

};

#endif // BOOKMARKWIDGET_H
