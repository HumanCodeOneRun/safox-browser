#include "popupmenu.h"

PopupMenu::PopupMenu(QToolButton*btn,QWidget* parent):btn(btn)
{
    this->setStyleSheet("QMenu{background-color:rgba(35,38,43,100);width:200px;height:245px;}"
                        "QMenu::item{color:white;padding:35px 30px 0px 30px;}");
}
void PopupMenu::showEvent(QShowEvent* event)
{
    QPoint p = this->pos();
    QRect geo = btn->geometry();
    this->move(p.x()+geo.width()-this->geometry().width()/2, p.y());
}

