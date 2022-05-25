#include "bookmarkboxgroup.h"

BookmarkBoxGroup::BookmarkBoxGroup(QWidget *parent)
    : QWidget{parent}
{

}
void BookmarkBoxGroup::onClicked(bool)
{
    bool v = !isVisible();
    setVisible(v);
    btn.setArrowType(v?Qt::DownArrow:Qt::RightArrow);
}
