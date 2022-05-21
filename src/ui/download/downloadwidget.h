#ifndef DOWNLOADWIDGET_H
#define DOWNLOADWIDGET_H

#include <QWidget>
#include <QToolButton>
#include <QStyleOption>
#include <QPainter>

namespace Ui {
class DownloadWidget;
}

class DownloadWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DownloadWidget(QWidget *parent = nullptr,QToolButton* btn=nullptr);
    ~DownloadWidget();

private:
    Ui::DownloadWidget *ui;
    void paintEvent(QPaintEvent *event);
};

#endif // DOWNLOADWIDGET_H
