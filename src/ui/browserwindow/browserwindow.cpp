/*
 * @Author: your name
 * @Date: 2022-05-03 11:39:07
 * @LastEditTime: 2022-05-17 16:23:22
 * @LastEditors: SC-WSKun 540610423@qq.com
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \safox\safox\src\browserwindow.cpp
 */
#include "browserwindow.h"
#include "./ui_browserwindow.h"
#include "../core/service/service.h"


BrowserWindow::BrowserWindow(int userid, const MyServiceLocator &serviceLocator, QWidget *parent)
    : QMainWindow(parent),
    Browser(userid, serviceLocator),
    ui(new Ui::BrowserWindow)
{
//    m_taskScheduler = new DatabaseTaskScheduler();
    ui->setupUi(this);

    /* 隐藏默认标题栏 */
    setWindowFlags(Qt::FramelessWindowHint|Qt::WindowSystemMenuHint|Qt::WindowMinimizeButtonHint);

    //todo: 获取屏幕分辨率并赋值给curHeight,curWidth，默认1920*1080

    //...

    this->curHeight=1920,this->curWidth=1050;
    this->scale = 1.0;
    QMainWindow::resize(this->curHeight*this->scale,this->curWidth*this->scale);

    CreateSystemTrayIcon();


    //设置背景颜色
//    this->setStyleSheet("QMainWindow{background-color: rgba(46, 50, 53, 100)}");

    /* toolbar */
    this->tb = new Toolbar(this,0,50,1920,50);

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
    this->historyTest->hide();
    if(tb){
       connect(tb,&Toolbar::on_historyBtn_passSignal,this,&BrowserWindow::accept_history_signal);
    }

    // 初始化书签界面并隐藏
    qDebug()<<"[test] browserwindown slot2 init";
    this->bookmarkTest = new BookmarkWidget(this,0,100,300,980,this);
    this->bookmarkTest->hide();
    if(tb){
       connect(tb,&Toolbar::on_bookmarkerBtn_passSignal,this,&BrowserWindow::accept_bookmarker_signal);
    }

    // 初始化账户界面并隐藏
    qDebug()<<"[test] browserwindown slot3 init";
    this->accountTest = new AccountWidget(this,tb->accountBtn,this);
    this->accountTest->hide();
    if(tb){
       connect(tb,&Toolbar::on_accountBtn_passSignal,this,&BrowserWindow::accept_account_signal);
    }

    // 初始化下载界面并隐藏
    qDebug()<<"[test] browserwindown slot4 init";
    this->downloadTest = new DownloadWidget(this,tb->downloadBtn);
    this->downloadTest->hide();
    if(tb){
       connect(tb,&Toolbar::on_downloadBtn_passSignal,this,&BrowserWindow::accept_download_signal);
    }


    /*tabwidget*/
    my_tab=new tabwidget(this);
    tb->setParentWindow(this);
    my_tab->setParentWindow(this);
    my_tab->move(0, 100);
    my_tab->setGeometry(0,110,1920,980);
    my_tab->setTabPosition(QTabWidget::North);
    my_tab->setTabShape(QTabWidget::Triangular);
    my_tab->setTabsClosable(true);
    my_tab->createTab();
    my_tab->setUrl(my_tab->returnHomePage());
    connect(tb->addBtn,&QToolButton::clicked,my_tab,[=]{
        my_tab->createTab();
        my_tab->setUrl(my_tab->returnHomePage());
    });
    connect(my_tab, &tabwidget::urlChanged, [this](const QUrl &url) {
        tb->urlBar->setText(url.toDisplayString());
    });
    connect(tb,&Toolbar::on_goBtn_passSignal,this,&BrowserWindow::accept_go_signal);
    connect(tb,&Toolbar::on_backBtn_passSignal,this,&BrowserWindow::accept_back_signal);
    connect(tb,&Toolbar::on_homeBtn_passSignal,this,&BrowserWindow::accept_home_signal);
    DownloadManager* manager=new DownloadManager;
    connect(my_tab->currentWebView()->page()->profile(), &QWebEngineProfile::downloadRequested,
        [manager](QWebEngineDownloadRequest* request){
            qDebug() << "emit request";
            QUrl url = request->url();
            QUrl icon("icon.com");
            QString save_path = "~/Downloads";
            QString name = request->downloadFileName();
            qDebug() << "name is " << name;
            manager->on_requested(request, url, icon, save_path, name);
        });

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

/* 最小化 */
void BrowserWindow::on_minBtn_clicked()
{
    this->showMinimized();
}

/* 放大缩小 */
void BrowserWindow::on_hidBtn_clicked()
{
    if(this->scale==0.5){
        this->showNormal();
        this->scale = 1;
    }else{
        this->scale = 0.5;
        this->showFullScreen();
    }
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
    trayIcon->setIcon(QIcon(":/icon/image/browser.png"));//设置托盘图标
    trayIcon->setContextMenu(trayMenu);
    trayIcon->show();
}

void BrowserWindow::popMessageBox(QString text,QString title){
    QMessageBox box;
    box.setStyleSheet("QMessageBox{"
                      "width:300px;"
                      "height:200px;"
                      "background:rgba(57,52,58,100);}"
                      "QLabel{"
                      "min-width: 300px;"
                      "min-height: 200px; "
                      "font-size:20px;"
                      "color:white;"
                      "}"
                      "QPushButton {"
                      "background-color:rgba(54,112,209,100);"
                      " border-style: outset;"
                      " border-radius: 20px;"
                      " font: bold 15px;"
                      " color:white;"
                      " min-width: 150px;"
                      " min-height: 40px;"
                      "}"
                      "");
    box.setText(text);//设置显示文本
    box.setWindowTitle(title);//设置弹窗标题
//    box.setWindowIcon(QIcon(":/new/prefix1/h8.ico"));//弹窗左上角图标
//    box.setIconPixmap(QPixmap(":/new/prefix1/gg.ico"));//弹窗提示图
    box.exec();
}

void BrowserWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);

    /* 绘制historyWidget背景 */
    p.setPen(Qt::NoPen);
    p.setBrush(QColor(46, 50, 53, 100));
    p.drawRect(0,0,this->width(),this->height());
}


/*实现窗口拖拽*/

QPoint winP;

void BrowserWindow::mouseReleaseEvent(QMouseEvent *event)
{
    QWidget::mouseReleaseEvent(event);
    winP=QPoint();//释放鼠标，清空数据
}

void BrowserWindow::mousePressEvent(QMouseEvent *event)
{
    winP=QPoint();
    QWidget::mousePressEvent(event);
    //获取鼠标点击时相对于屏幕的坐标
    QPoint mouseP = event->globalPos();
    //窗口相对于屏幕的坐标
    int x = this->geometry().topLeft().x();
    int y = this->geometry().topLeft().y();
    //求出鼠标相对于应用窗口的坐标
    int x_w=mouseP.x()-x;
    int y_w=mouseP.y()-y;
    //将鼠标相对于窗口的坐标保存
    winP.setX(x_w);
    winP.setY(y_w);
}

void BrowserWindow::mouseMoveEvent(QMouseEvent *event)
{
    QWidget::mouseMoveEvent(event);
    //获取鼠标移动时相对于屏幕的坐标
    QPoint mouseP = event->globalPos();
    //求出窗口相对于桌面的坐标
    QPoint endP(mouseP.x()-winP.x(),mouseP.y()-winP.y());
    //窗口移动
    this->move(endP);
}

void BrowserWindow::accept_history_signal(){
//    qDebug("receive history signal");
    if(this->historyTest->isVisible()){
        this->historyTest->hide();
    }else{
        this->historyTest->show();
        this->historyTest->raise();
        this->bookmarkTest->hide();
        this->accountTest->hide();
        this->downloadTest->hide();
        this->my_tab->hide();
    }
}

void BrowserWindow::accept_bookmarker_signal(){
//    qDebug("receive bookmarker signal");
    if(this->bookmarkTest->isVisible()){
        this->bookmarkTest->hide();
    }else{
        this->bookmarkTest->show();
        this->historyTest->hide();
        this->accountTest->hide();
        this->downloadTest->hide();
        this->my_tab->stackUnder(this->bookmarkTest);
    }
    bookmarkTest->bookmarkerReload();
}

void BrowserWindow::accept_account_signal(){
 //    qDebug("receive account signal");
    if(this->accountTest->isVisible()){
        this->accountTest->hide();
    }else{
        this->accountTest->show();
        this->my_tab->stackUnder(this->accountTest);
        this->downloadTest->hide();
    }
}

void BrowserWindow::accept_download_signal(){
 //    qDebug("receive download signal");
    if(this->downloadTest->isVisible()){
        this->downloadTest->hide();
    }else{
        this->downloadTest->show();
        this->my_tab->stackUnder(this->downloadTest);
        this->accountTest->hide();

    }
}

void BrowserWindow::accept_go_signal(){
    my_tab->triggerWebPageAction(QWebEnginePage::Forward);
};

void BrowserWindow::accept_home_signal(){
    this->my_tab->show();
    this->historyTest->hide();
    this->accountTest->hide();
    this->downloadTest->hide();
    this->bookmarkTest->hide();
    my_tab->setUrl(my_tab->returnHomePage());
};

void BrowserWindow::accept_back_signal(){
    my_tab->triggerWebPageAction(QWebEnginePage::Back);
};
