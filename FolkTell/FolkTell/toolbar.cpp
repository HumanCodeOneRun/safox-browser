#include "toolbar.h"

Toolbar::Toolbar(QWidget* parent,int x,int y,int width,int height)
{
    init_x = x;
    init_y = y;
    width = width;
    height = height;

    /* 书签按钮 */
    bookmarker = new QToolButton(parent);
    bookmarker->setGeometry(x+150,y+10,45,30);

    /* 首页按钮 */

    /* 历史按钮 */
}
