#ifndef TOOLBAR_H
#define TOOLBAR_H
#include <QWidget>
#include<QToolButton>
#include<QLineEdit>

class Toolbar: public QWidget
{
    Q_OBJECT
public:
    explicit Toolbar(QWidget *parent = nullptr,int x = 0,int y = 0,int width = 0,int height = 0);
    QToolButton* bookmarkerBtn;
    QToolButton* historyBtn;
    QToolButton* homeBtn;
    QToolButton* downloadBtn;
    QToolButton* accountBtn;
    QToolButton* settingBtn;
    QToolButton* addBtn;
    QLineEdit* urlBar;
private:
    int init_x;
    int init_y;
    int width;
    int height;
};

#endif // TOOLBAR_H
