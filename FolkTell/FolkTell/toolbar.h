#ifndef TOOLBAR_H
#define TOOLBAR_H
#include<QToolButton>


class Toolbar
{
public:
    Toolbar(QWidget *parent = nullptr,int x = 0,int y = 0,int width = 0,int height = 0);
    QToolButton* bookmarker;
private:
    int init_x;
    int init_y;
    int width;
    int height;
};

#endif // TOOLBAR_H
