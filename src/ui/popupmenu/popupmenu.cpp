#include "popupmenu.h"

PopupMenu::PopupMenu(QToolButton*btn,QWidget* parent):btn(btn)
{
    this->setStyleSheet("QMenu{background-color:rgba(35,38,43,255);width:180px;height:290px;}"
                        "QMenu::item{color:white;margin:15px 15px 15px 15px;padding:5px;}"
                        "QMenu::item:selected{background-color: rgba(52,52,52,255);}");
}
void PopupMenu::showEvent(QShowEvent* event)
{
    QPoint p = this->pos();
    QRect geo = btn->geometry();
    this->move(geo.x()-this->geometry().width()+btn->width(), p.y());
}

