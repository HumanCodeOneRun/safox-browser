#ifndef BOOKMARKITEM_H
#define BOOKMARKITEM_H

#include <QWidget>
#include <QPixmap>
#include <QLabel>
#include <QMenu>
#include <QStyleOption>
#include <QPainter>

namespace Ui {
class BookmarkItem;
}
class BrowserWindow;
class BookmarkItem : public QWidget
{
    Q_OBJECT

public:
    explicit BookmarkItem(QWidget *parent = nullptr,int id=0,QString url=nullptr,QString title = "title_load_error",QString description = "description_load_error",BrowserWindow* root=nullptr);
    ~BookmarkItem();

private:
    int id;
    BrowserWindow* root;
    Ui::BookmarkItem *ui;
    QMenu *cmenu;
    void paintEvent(QPaintEvent *event);

private slots:
    void contextMenuEvent(QContextMenuEvent *event);
    void editItem();
    void deleteItem();

signals:
    void on_deleteItem_passSignals();

};

#endif // BOOKMARKITEM_H
