#ifndef PAGEVIEW_H
#define PAGEVIEW_H

#include <QWidget>

namespace Ui {
class PageView;
}

class PageView : public QWidget
{
    Q_OBJECT

public:
    explicit PageView(QWidget *parent = nullptr);
    ~PageView();

private:
    Ui::PageView *ui;
};

#endif // PAGEVIEW_H
