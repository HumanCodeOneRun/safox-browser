/*
 * @Author: your name
 * @Date: 2022-05-03 11:39:07
 * @LastEditTime: 2022-05-17 16:23:22
 * @LastEditors: SC-WSKun 540610423@qq.com
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \FolkTell\FolkTell\src\browserwindow.cpp
 */
#include "browserwindow.h"
#include "./ui_browserwindow.h"



BrowserWindow::BrowserWindow(QWidget *parent)
//    :QMainWindow()
    : QMainWindow(parent),Browser(11111111)
    , ui(new Ui::BrowserWindow)
    ,my_tab(new tabwidget(this))
{




    m_taskScheduler = new DatabaseTaskScheduler();
    ui->setupUi(this);

    /* 隐藏默认标题栏 */
    setWindowFlags(Qt::FramelessWindowHint|Qt::Tool|Qt::WindowStaysOnTopHint);

    //todo: 获取屏幕分辨率并赋值给curHeight,curWidth，默认1920*1080
    //todo: 窗口拖拽

    //...

    this->curHeight=1920,this->curWidth=1080;
    this->scale = 1.0;
    QMainWindow::resize(this->curHeight*this->scale,this->curWidth*this->scale);

    CreateSystemTrayIcon();


    //设置背景颜色
    this->setStyleSheet("QMainWindow{background-color: rgba(46, 50, 53, 100)}");


    QWidget *centralwidget=new QWidget(this);
    QVBoxLayout *layout=new QVBoxLayout;
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    centralwidget->setLayout(layout);
    centralwidget->setGeometry(0,100,1920,980);


    /* toolbar */


    this->tb= new Toolbar(this,0,50,1920,980);
    layout->addWidget(tb);

    /* 关闭按钮 */
    QToolButton* closeBtn = new QToolButton(this);
    closeBtn->setStyleSheet("QToolButton{background-color:rgba(235, 106, 99, 100);border-radius:10px;}");
    closeBtn->setGeometry(20,15,20,20);
    connect(closeBtn,&QToolButton::clicked,this,&BrowserWindow::on_closeBtn_clicked);

    /* 放大缩小按钮 */
    QToolButton* minBtn = new QToolButton(this);
    minBtn->setStyleSheet("QToolButton{background-color:rgba(241, 195, 78, 100);border-radius:10px;}");
    minBtn->setGeometry(50,15,20,20);
    connect(minBtn,&QToolButton::clicked,this,&BrowserWindow::on_minBtn_clicked);

    /* 最小化按钮 */
    QToolButton* hidBtn = new QToolButton(this);
    hidBtn->setStyleSheet("QToolButton{background-color:rgba(57, 194, 77, 100);border-radius:10px;}");
    hidBtn->setGeometry(80,15,20,20);
    connect(hidBtn,&QToolButton::clicked,this,&BrowserWindow::on_hidBtn_clicked);


    // 初始化历史界面并隐藏
    qDebug()<<"[test] browserwindown slot1 init";
    this->historyTest = new HistoryWidget(this,0,100,1920,980,this);
    qDebug()<<"[test] browserwindown slot2 init";
    this->historyTest->hide();
    if(tb){
       connect(tb,&Toolbar::on_historyBtn_passSignal,this,&BrowserWindow::accept_history_signal);
    }

    // 初始化书签界面并隐藏
    this->bookmarkTest = new BookmarkWidget(this,0,100,300,980,this);
    this->bookmarkTest->hide();
    if(tb){
       connect(tb,&Toolbar::on_bookmarkerBtn_passSignal,this,&BrowserWindow::accept_bookmarker_signal);
    }


    tb->setParentWindow(this);
    /*tabwidget*/

    layout->addWidget(my_tab);
    my_tab->setParentWindow(this);
    my_tab->move(0, 100);
    my_tab->setGeometry(0,100,1920,980);
    my_tab->setTabPosition(QTabWidget::North);
    my_tab->setTabShape(QTabWidget::Triangular);
    my_tab->setTabsClosable(true);
    my_tab->createTab();


    my_tab->setUrl(my_tab->returnHomePage());

    DownloadManager* manager=new DownloadManager;

    connect(tb->addBtn,&QToolButton::clicked,my_tab,&tabwidget::createTab);
    /*
    connect(tb->urlBar, &QLineEdit::returnPressed, [this]() {
        QUrl *search =new QUrl;
        search->fromUserInput(tb->urlBar->text());
        if(search->isValid()){
            qDebug()<<"错误判断";
        }else if(!search->isValid()){
            qDebug()<<"成功判断";
        }
        my_tab->setUrl(QUrl::fromUserInput(tb->urlBar->text()));
    });
    */
    connect(my_tab, &tabwidget::urlChanged, [this](const QUrl &url) {
        tb->urlBar->setText(url.toDisplayString());
    });
    connect(tb,&Toolbar::on_goBtn_passSignal,this,&BrowserWindow::accept_go_signal);
    connect(tb,&Toolbar::on_backBtn_passSignal,this,&BrowserWindow::accept_back_signal);
    connect(tb,&Toolbar::on_homeBtn_passSignal,this,&BrowserWindow::accept_home_signal);

    connect(my_tab->currentWebView()->page()->profile(), &QWebEngineProfile::downloadRequested,
        [manager](QWebEngineDownloadRequest* request){
            qDebug() << "emit request";
            QUrl url = request->url();
            QUrl icon("icon.com");
            QString save_path = "~/Downloads";
            QString name = request->downloadFileName();
            qDebug() << "name is " << name;
            manager->on_requested(request, url, icon, save_path, name);
        }
        );

}

BrowserWindow::~BrowserWindow()
{
    delete ui;
}

/* 关闭窗口 */
void BrowserWindow::on_closeBtn_clicked()
{
    qDebug()<<"exit";
    QApplication::exit(0);
}


void BrowserWindow::on_minBtn_clicked()
{
    this->scale = this->scale == 1.0 ? 0.5 : 1.0;
    QMainWindow::resize(this->curHeight*this->scale,this->curWidth*this->scale);
}

void BrowserWindow::on_hidBtn_clicked()
{
    this->hide();
}

void BrowserWindow::CreateSystemTrayIcon(){
    //初始化两个项目
    QAction* showAction = new QAction(QStringLiteral("显示"));//项1
    QAction* exitAction = new QAction(QStringLiteral("退出"));//项2
    //项1的点击槽函数
    connect(showAction, &QAction::triggered, this, [=]()
    {
        this->show();
    });
    //项2的点击槽函数
    connect(exitAction , &QAction::triggered, this, [=]()
    {
        qDebug()<<"exit";
        QApplication::exit(0);
    });

    //初始化菜单并添加项
    QMenu* trayMenu = new QMenu(this);//菜单
    trayMenu->addAction(showAction);
    trayMenu->addAction(exitAction );
    QSystemTrayIcon* trayIcon = new QSystemTrayIcon(this);
    trayIcon->setIcon(QIcon(":/icon/image/download.png"));    //设置托盘图标
    trayIcon->setContextMenu(trayMenu);                                     //设置菜单
    trayIcon->show();
}

void BrowserWindow::accept_history_signal(){
    if(this->historyTest->isVisible()){
        this->historyTest->hide();
    }else{
        this->historyTest->show();
    }
}

void BrowserWindow::accept_bookmarker_signal(){
    qDebug("receive signal");
    if(this->bookmarkTest->isVisible()){
        this->bookmarkTest->hide();
    }else{
        this->bookmarkTest->show();
    }
}

void BrowserWindow::accept_go_signal(){
    my_tab->triggerWebPageAction(QWebEnginePage::Forward);
};

void BrowserWindow::accept_home_signal(){
    my_tab->setUrl(my_tab->returnHomePage());
};

void BrowserWindow::accept_back_signal(){
    my_tab->triggerWebPageAction(QWebEnginePage::Back);
};
