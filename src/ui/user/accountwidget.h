#ifndef ACCOUNTWIDGET_H
#define ACCOUNTWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QToolButton>
#include <QStyleOption>
#include <QPainter>

namespace Ui {
class AccountWidget;
}

class AccountWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AccountWidget(QWidget *parent = nullptr,QToolButton* btn=nullptr);
    QLineEdit* account;
    QLineEdit* password;
    QPushButton* login;
    ~AccountWidget();

private:
    Ui::AccountWidget *ui;
    void paintEvent(QPaintEvent *event);
};

#endif // ACCOUNTWIDGET_H
