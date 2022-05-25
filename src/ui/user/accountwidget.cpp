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
                        "QLineEdit{background-color:rgba(255,255,255,40);color:rgba(0,1,0,60);font-size:15px;padding-left:10px;}");
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
    this->login->setGeometry(56,284,88,32);
    this->login->setStyleSheet("QPushButton{background-color:rgba(0,52,181,100);border-radius:5px;color:white;}");
    this->login->setText("登录");
    connect(this->login,&QPushButton::clicked,this,&AccountWidget::on_loginBtn_clicked);

    this->registerBtn = new QPushButton(this);
    this->registerBtn->setGeometry(156,284,88,32);
    this->registerBtn->setStyleSheet("QPushButton{background-color:rgba(0,52,181,100);border-radius:5px;color:white;}");
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
    p.setBrush(QColor(35, 38, 43, 100));
    p.drawRect(0,0,this->width(),this->height());
}

void AccountWidget::on_loginBtn_clicked(){
    QString username = this->account->text();
    QString userpass = this->password->text();
    bool isExist = this->root->Browser::m_user->queryUserName(username);
    if(!isExist){
        //todo: 弹窗显示用户不存在
        qDebug("user not exist");
        return;
    }
//    bool canLog = this->root->Browser::m_user->queryUserPassword(username,userpass);
//    if(!canLog){
//        //todo: 弹窗显示密码错误
//        return;
//    }
//    int newid = this->root->Browser::m_user->getUserIdByName(username);
//    this->root->Browser::changeUser(newid);
    qDebug("log success");
}

void AccountWidget::on_registerBtn_clicked(){
    QString username = this->account->text();
    QString userpass = this->password->text();
    qDebug()<<username;
    bool isExist = this->root->Browser::m_user->queryUserName(username);
    if(isExist){
        //todo: 弹窗显示已存在用户
        qDebug("user exist");
        return;
    }
    this->root->Browser::m_user->addRegisterUser(username,userpass);
    //todo：弹窗显示注册成功
    qDebug("register success");
}
