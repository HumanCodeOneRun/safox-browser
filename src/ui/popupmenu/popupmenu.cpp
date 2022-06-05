#include "popupmenu.h"

PopupMenu::PopupMenu(QToolButton*btn,QWidget* parent):btn(btn)
{
    this->setStyleSheet("QMenu{background-color:rgba(35,38,43,255);width:200px;height:290px;}"
                        "QMenu::item{color:white;margin:25px 25px 0px 25px;padding:5px;}"
                        "QMenu::item:selected{background-color: rgba(52,52,52,255);}");
}
void PopupMenu::showEvent(QShowEvent* event)
{
    QPoint p = this->pos();
    QRect geo = btn->geometry();
    this->move(p.x()+2*btn->width()-this->geometry().width(), p.y());
}

