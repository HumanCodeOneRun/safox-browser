#ifndef BOOKMARKBOX_H
#define BOOKMARKBOX_H

#include <QScrollArea>
#include <QVBoxLayout>
#include <QToolButton>
#include "bookmarkitem.h"

class BookmarkBox : public QScrollArea
{
public:
     BookmarkBox(QWidget *parent,int width,int height);
//    void addGroup(BookmarkItem* item);
//    BookmarkItem* getItem(QString name);

    QVBoxLayout* vlayout;
};

#endif // BOOKMARKBOX_H
