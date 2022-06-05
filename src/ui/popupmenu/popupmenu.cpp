#include "popupmenu.h"

PopupMenu::PopupMenu(QToolButton*btn,QWidget* parent):btn(btn)
{
    this->setStyleSheet("QMenu{background-color:rgba(35,38,43,100);width:200px;height:290px;}"
                        "QMenu::item{color:white;margin:35px 30px 0px 30px;}");
}
void PopupMenu::showEvent(QShowEvent* event)
{
    QPoint p = this->pos();
    QRect geo = btn->geometry();
    this->move(p.x()+2*btn->width()-this->geometry().width(), p.y());
}

