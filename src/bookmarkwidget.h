#ifndef BOOKMARKWIDGET_H
#define BOOKMARKWIDGET_H

#include <QWidget>

namespace Ui {
class BookmarkWidget;
}

class BookmarkWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BookmarkWidget(QWidget *parent = nullptr);
    ~BookmarkWidget();

private:
    Ui::BookmarkWidget *ui;
};

#endif // BOOKMARKWIDGET_H
