#ifndef POPUPMENU_H
#define POPUPMENU_H

#include <QMenu>
#include <QToolButton>
#include <QStyleOption>
#include <QPainter>

class PopupMenu : public QMenu
{
public:
    PopupMenu(QToolButton* btn,QWidget*parent=nullptr);
private:
    void showEvent(QShowEvent* event);
    QToolButton* btn;
};

#endif // POPUPMENU_H
