#include "accountwidget.h"
#include "ui_accountwidget.h"

AccountWidget::AccountWidget(QWidget *parent,QToolButton* btn) :
    QWidget(parent),
    ui(new Ui::AccountWidget)
{
    ui->setupUi(this);
    this->setStyleSheet("QWidget{width:300px;height:400px;}"
                        "QLabel{font-size:15px;color:white;background-color:transparent;}"
                        "QLineEdit{background-color:rgba(255,255,255,40);color:rgba(0,1,0,60);font-size:15px;padding-left:10px;}");
    qDebug()<<btn->width();
    qDebug()<<btn->height();
    int x = btn->x()-300+btn->width();
    int y = btn->y()+btn->height();
    this->setGeometry(x,y,300,400);
    QLabel* accountTitle = new QLabel(this);
    accountTitle->setText("Account");
    accountTitle->setGeometry(20,54,268,20);

    this->account = new QLineEdit(this);
    this->account->setGeometry(20,82,268,32);
    this->account->setText("Please input your account");

    QLabel* passwordTitle = new QLabel(this);
    passwordTitle->setText("Password");
    passwordTitle->setGeometry(20,140,268,20);

    this->password = new QLineEdit(this);
    this->password->setGeometry(20,168,268,32);
    this->password->setText("Please input your password");

    this->login = new QPushButton(this);
    this->login->setGeometry(106,284,88,32);
    this->login->setStyleSheet("QPushButton{background-color:rgba(0,52,181,100);border-radius:5px;color:white;}");
    this->login->setText("登录");
}

AccountWidget::~AccountWidget()
{
    delete ui;
}

void AccountWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);

    /* 绘制historyWidget背景 */
    p.setPen(Qt::NoPen);
    p.setBrush(QColor(35, 38, 43, 100));
    p.drawRect(0,0,this->width(),this->height());
}
