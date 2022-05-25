#ifndef ACCOUNTWIDGET_H
#define ACCOUNTWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QToolButton>
#include <QStyleOption>
#include <QPainter>
#include "src/core/user/usermodel.h"

namespace Ui {
class AccountWidget;
}
class BrowserWindow;

class AccountWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AccountWidget(QWidget *parent = nullptr,QToolButton* btn=nullptr,BrowserWindow* root=nullptr);
    QLineEdit* account;
    QLineEdit* password;
    BrowserWindow* root;
    QPushButton* login;
    QPushButton* registerBtn;
    ~AccountWidget();

private:
    Ui::AccountWidget *ui;
    void paintEvent(QPaintEvent *event);
private slots:
    void on_loginBtn_clicked();
    void on_registerBtn_clicked();
};

#endif // ACCOUNTWIDGET_H
