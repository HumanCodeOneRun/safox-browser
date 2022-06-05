#include "accountwidget.h"
#include "ui_accountwidget.h"
#include "src/ui/browserwindow/browserwindow.h"

AccountWidget::AccountWidget(QWidget *parent,QToolButton* btn,BrowserWindow* root) :
    QWidget(parent),root(root),
    ui(new Ui::AccountWidget)
{
    ui->setupUi(this);
    this->setStyleSheet("QWidget{width:300px;height:400px;}"
                        "QLabel{font-size:15px;color:white;background-color:transparent;}"
                        "QLineEdit{background-color:rgba(255,255,255,102);color:rgba(0,1,0,153);font-size:15px;padding-left:10px;}");
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

    accountLabel = new QLabel(this);
    accountLabel->setText("当前账号： 默认账户");
    accountLabel->setAlignment(Qt::AlignCenter);
    accountLabel->setGeometry(20,230,268,20);

    this->login = new QPushButton(this);
    this->login->setGeometry(56,284,88,32);
    this->login->setStyleSheet("QPushButton{background-color:rgba(0,52,181,255);border-radius:5px;color:white;}");
    this->login->setText("登录");
    connect(this->login,&QPushButton::clicked,this,&AccountWidget::on_loginBtn_clicked);

    this->registerBtn = new QPushButton(this);
    this->registerBtn->setGeometry(156,284,88,32);
    this->registerBtn->setStyleSheet("QPushButton{background-color:rgba(0,52,181,255);border-radius:5px;color:white;}");
    this->registerBtn->setText("注册");
    connect(this->registerBtn,&QPushButton::clicked,this,&AccountWidget::on_registerBtn_clicked);
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

    /* 绘制accountWidget背景 */
    p.setPen(Qt::NoPen);
    p.setBrush(QColor(35,35,43));
    p.drawRect(0,0,this->width(),this->height());
}

void AccountWidget::on_loginBtn_clicked(){
    QString username = this->account->text();
    QString userpass = this->password->text();
    bool isExist = this->root->Browser::m_user->queryUserName(username);
    if(!isExist){
        this->root->popMessageBox("该用户不存在","错误");
        return;
    }
    bool canLog = this->root->Browser::m_user->queryUserPassword(username,userpass);
    if(!canLog){
        //todo: 弹窗显示密码错误
        return;
    }
    int newid = this->root->Browser::m_user->getUserIdByName(username);
    this->root->Browser::changeUser(newid);
    this->accountLabel->setText("当前账号： "+username);
    this->root->popMessageBox("登录成功","成功");
}

void AccountWidget::on_registerBtn_clicked(){
    QString username = this->account->text();
    QString userpass = this->password->text();
    bool isExist = this->root->Browser::m_user->queryUserName(username);
    if(isExist){
        this->root->popMessageBox("该用户已存在","错误");
        return;
    }
    this->root->Browser::m_user->addRegisterUser(username,userpass);
    this->root->popMessageBox("注册成功","成功");
}

