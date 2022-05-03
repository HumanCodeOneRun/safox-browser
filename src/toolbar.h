#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <QWidget>

namespace Ui {
class ToolBar;
}

class ToolBar : public QWidget
{
    Q_OBJECT

public:
    explicit ToolBar(QWidget *parent = nullptr);
    int height,width;
    ~ToolBar();

private:
    Ui::ToolBar *ui;
};

#endif // TOOLBAR_H
