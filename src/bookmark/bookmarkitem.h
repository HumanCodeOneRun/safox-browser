#ifndef BOOKMARKITEM_H
#define BOOKMARKITEM_H

#include <QWidget>

namespace Ui {
class BookmarkItem;
}

class BookmarkItem : public QWidget
{
    Q_OBJECT

public:
    explicit BookmarkItem(QWidget *parent = nullptr,int x=0,int y=0,QString url=nullptr,QString title = "title_load_error",QString description = "description_load_error");
    ~BookmarkItem();

private:
    Ui::BookmarkItem *ui;
};

#endif // BOOKMARKITEM_H
