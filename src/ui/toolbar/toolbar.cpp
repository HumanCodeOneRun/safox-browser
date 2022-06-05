/*
 * @Author: your name
 * @Date: 2022-05-03 11:39:08
 * @LastEditTime: 2022-05-28 01:30:56
 * @LastEditors: SC-WSKun 540610423@qq.com
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \safox\safox\src\toolbar.cpp
 */
#include "toolbar.h"
#include "browserwindow.h"
#include "core/searchengine/searchengineMgr.h"
#include "browserwindow.h"
#include "useragent.h"

SeachBar::SeachBar(QWidget* parent):QLineEdit(parent){

}

void SeachBar::focusInEvent(QFocusEvent* event){
    QLineEdit::focusInEvent(event);
    QTimer::singleShot(0, this, &QLineEdit::selectAll);
}

Toolbar::Toolbar(QWidget* parent,int x,int y,int width,int height,BrowserWindow* root):
    QWidget(parent),root(root)
{
    this->init_x = x;
    this->init_y = y;
    this->width = width;
    this->height = height;
    this->setGeometry(x,y,width,height);

    /* 后退按钮 */
    backBtn = new QToolButton(parent);
    backBtn->setGeometry(x+30,y+10,45,30);
    backBtn->setStyleSheet("QToolButton{background-color:rgba(96, 100, 101, 100);border-radius:8px;}");
    QIcon back = QIcon(":/icon/image/arrow-left-allow.png");
    backBtn->setIcon(back);
    connect(backBtn,&QToolButton::clicked,this,&Toolbar::back_page);

    /* 前进按钮 */
    goBtn = new QToolButton(parent);
    goBtn->setGeometry(x+73,y+10,45,30);
    goBtn->setStyleSheet("QToolButton{background-color:rgba(96, 100, 101, 100);border-radius:8px;}");
    QIcon go = QIcon(":/icon/image/arrow-right-allow.png");
    goBtn->setIcon(go);
    connect(goBtn,&QToolButton::clicked,this,&Toolbar::front_page);

    /* 书签按钮 */
    bookmarkerBtn = new QToolButton(parent);
    bookmarkerBtn->setGeometry(x+150,y+10,45,30);
    bookmarkerBtn->setStyleSheet("QToolButton{background-color:rgba(96, 100, 101, 100);border-radius:8px;}");
    QIcon bookmaker = QIcon(":/icon/image/bookmaker.png");
    bookmarkerBtn->setIcon(bookmaker);
    connect(bookmarkerBtn,&QToolButton::clicked,this,&Toolbar::on_bookmarkerBtn_clicked);

    /* 首页按钮 */
    homeBtn = new QToolButton(parent);
    homeBtn->setGeometry(x+232,y+10,45,30);
    homeBtn->setStyleSheet("QToolButton{background-color:rgba(96, 100, 101, 100);border-radius:8px;}");
    QIcon homepage = QIcon(":/icon/image/homepage.png");
    homeBtn->setIcon(homepage);
    connect(homeBtn,&QToolButton::clicked,this,&Toolbar::home_page);

    /* 下载按钮 */
    downloadBtn = new QToolButton(parent);
    downloadBtn->setGeometry(x+1575,y+10,45,30);
    downloadBtn->setStyleSheet("QToolButton{background-color:rgba(96, 100, 101, 100);border-radius:8px;}");
    QIcon download = QIcon(":/icon/image/download.png");
    downloadBtn->setIcon(download);
    connect(downloadBtn,&QToolButton::clicked,this,&Toolbar::on_downloadBtn_clicked);

    /* 历史按钮 */
    historyBtn = new QToolButton(parent);
    historyBtn->setGeometry(x+1640,y+10,45,30);
    historyBtn->setStyleSheet("QToolButton{background-color:rgba(96, 100, 101, 100);border-radius:8px;}");
    QIcon history = QIcon(":/icon/image/history.png");
    historyBtn->setIcon(history);
    connect(historyBtn,&QToolButton::clicked,this,&Toolbar::on_historyBtn_clicked);


    /* 账户按钮 */
    accountBtn = new QToolButton(parent);
    accountBtn->setGeometry(x+1705,y+10,45,30);
    accountBtn->setStyleSheet("QToolButton{background-color:rgba(96, 100, 101, 100);border-radius:8px;}");
    QIcon account = QIcon(":/icon/image/account.png");
    accountBtn->setIcon(account);
    connect(accountBtn,&QToolButton::clicked,this,&Toolbar::on_accountBtn_clicked);


    /* 设置按钮 */
    settingBtn = new QToolButton(parent);
    settingBtn->setGeometry(x+1770,y+10,45,30);
    settingBtn->setStyleSheet("QToolButton{background-color:rgba(96, 100, 101, 100);border-radius:8px;}"
                              "QToolButton::menu-indicator{image:none;}");
    QIcon setting = QIcon(":/icon/image/setting.png");
    settingBtn->setIcon(setting);
    QMenu* settingMenu = new PopupMenu(settingBtn);
    QAction* setting1=new QAction("启用广告拦截",this);
    QAction* setting2=new QAction("禁用广告拦截",this);
    QAction* setting3=new QAction("保存当前页为主页",this);
    settingMenu->addAction(setting1);
    settingMenu->addAction(setting2);
    setting1->setCheckable(true);
    setting2->setEnabled(false);
    setting2->setCheckable(true);
    setting2->setChecked(true);
    settingMenu->addAction(setting3);
    connect(setting1, &QAction::triggered, this, [=]() {
        qDebug()<<"adblock 1";
        m_window->my_tab->AdblockOpen=true;
        setting1->setEnabled(false);
        setting2->setEnabled(true);
        setting1->setChecked(true);
        setting2->setChecked(false);
        qDebug()<<"adblock open";
        //this->setStyleSheet("QMenu{background-color:rgba(35,38,43,100);width:200px;height:290px;}"
        //                    "QMenu::item{color:white;margin:35px 30px 0px 30px;}");
        //setAdblockRequestInterceptor("../../dependent_files/easylist.txt");
    });
    connect(setting2, &QAction::triggered, this, [=]() {
        qDebug()<<"adblock 2";
        m_window->my_tab->AdblockOpen=false;
        setting1->setEnabled(true);
        setting2->setEnabled(false);
        setting1->setChecked(false);
        setting2->setChecked(true);
        qDebug()<<"adblock close";
        //setDefaultRequestInterceptor();
    });
    connect(setting3, &QAction::triggered, this, [=]() {
        QUrl CurrentUrl=m_window->my_tab->currentWebView()->getUrl();
        m_window->my_tab->changeHomePage(CurrentUrl);
    });

    //setting4切换搜索引擎
    QMenu *SearchMenu=new QMenu;
    SearchMenu->setStyleSheet("QMenu{background-color:rgba(35,38,43,100);width:120px;height:180px;}"
                            "QMenu::item{color:white;margin:25px 30px 0px 30px;font-size:15px;}");
    QActionGroup *SearchGroup=new QActionGroup(parent);
    QAction *BaiduSearch=new QAction(tr("百度"), SearchMenu);
    QAction *BingSearch=new QAction(tr("Bing"), SearchMenu);
    QAction *GoogleSearch=new QAction(tr("Google"), SearchMenu);
    SearchMenu->addAction(BaiduSearch);
    SearchMenu->addAction(BingSearch);
    SearchMenu->addAction(GoogleSearch);
    BaiduSearch->setCheckable(true);
    BingSearch->setCheckable(true);
    GoogleSearch->setCheckable(true);
    m_searchManager=new SearchEngineManager;
    connect(BaiduSearch, &QAction::triggered, this, [=]() {
        this->m_searchManager->changeDefaultSearchEngine("baidu");
    } );
    connect(BingSearch, &QAction::triggered, this, [=]() {
        this->m_searchManager->changeDefaultSearchEngine("bing");
    } );
    connect(GoogleSearch, &QAction::triggered, this, [=]() {
        this->m_searchManager->changeDefaultSearchEngine("google");
    } );
    SearchGroup->addAction(BaiduSearch);
    SearchGroup->addAction(BingSearch);
    SearchGroup->addAction(GoogleSearch);
    settingMenu->addMenu(SearchMenu)->setText(tr("切换搜索引擎"));

    //setting5切换UA
    QMenu *UAMenu = new QMenu;
    UAMenu->setStyleSheet("QMenu{background-color:rgba(35,38,43,100);width:120px;height:180px;}"
                            "QMenu::item{color:white;margin:10px 20px;font-size:15px;}");
    QActionGroup *UAGroup=new QActionGroup(parent);
    QAction *Chrome=new QAction(tr("Chrome"), UAMenu);
    QAction *Opera=new QAction(tr("Opera"), UAMenu);
    QAction *Safari=new QAction(tr("Safari"), UAMenu);
    QAction *IE=new QAction(tr("IE"), UAMenu);
    UAGroup->addAction(Chrome);
    UAGroup->addAction(Opera);
    UAGroup->addAction(Safari);
    UAGroup->addAction(IE);
    Chrome->setCheckable(true);
    Opera->setCheckable(true);
    Safari->setCheckable(true);
    IE->setCheckable(true);
    connect(Chrome, &QAction::triggered, this, [=]() {
        root->Browser::m_uaMgr->setUserAgent(root->my_tab,"Chrome");
        qDebug()<<"UA changeto:"<<root->my_tab->getProfile()->httpUserAgent();
    } );
    connect(Opera, &QAction::triggered, this, [=]() {
        root->Browser::m_uaMgr->setUserAgent(root->my_tab,"Opera");
        qDebug()<<"UA changeto:"<<root->my_tab->getProfile()->httpUserAgent();
    } );
    connect(Safari, &QAction::triggered, this, [=]() {
        root->Browser::m_uaMgr->setUserAgent(root->my_tab,"Safari");
        qDebug()<<"UA changeto:"<<root->my_tab->getProfile()->httpUserAgent();
    } );
    connect(IE, &QAction::triggered, this, [=]() {
        root->Browser::m_uaMgr->setUserAgent(root->my_tab,"IE");
        qDebug()<<"UA changeto:"<<root->my_tab->getProfile()->httpUserAgent();
    } );
    UAMenu->addAction(Chrome);
    UAMenu->addAction(Opera);
    UAMenu->addAction(Safari);
    UAMenu->addAction(IE);
    settingMenu->addMenu(UAMenu)->setText(tr("切换UA"));

//    settingMenu->addSeparator();
    settingMenu->setWindowFlags(settingMenu->windowFlags()|Qt::FramelessWindowHint);
    settingBtn->setMenu(settingMenu);
    settingBtn->setPopupMode(QToolButton::InstantPopup);
    connect(settingBtn,&QToolButton::clicked,this,&Toolbar::on_settingBtn_clicked);

    /* 添加按钮 */
    addBtn = new QToolButton(parent);
    addBtn->setGeometry(x+1835,y+10,45,30);
    addBtn->setStyleSheet("QToolButton{background-color:rgba(96, 100, 101, 100);border-radius:8px;}");
    QIcon add = QIcon(":/icon/image/add.png");
    addBtn->setIcon(add);

    /* 网址 */
    urlBar = new SeachBar(parent);
    urlBar->setGeometry(x+460,y+10,1000,30);
    urlBar->setStyleSheet("QLineEdit{background-color:rgba(35, 38, 43, 100);border-radius:8px;color:rgba(136, 136, 136, 100);font-size:14px;}");
    urlBar->setText("www.baidu.com");
    urlBar->setAlignment(Qt::AlignHCenter);
    QAction * pActLeft = new QAction(this);
    pActLeft->setIcon(QIcon(":/icon/image/search.png"));
    urlBar->addAction(pActLeft,QLineEdit::LeadingPosition);
    connect(urlBar,&QLineEdit::returnPressed,this,&Toolbar::start_search);
    connect(pActLeft,&QAction::triggered,this,&Toolbar::start_search);
            QTimer::singleShot(0,urlBar,&QLineEdit::selectAll);
}

void Toolbar::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);

    /* 绘制Toolbar背景 */
    p.setPen(Qt::NoPen);
    p.setBrush(QColor(50, 54, 64, 100));
    p.drawRect(0,0,this->width,this->height);
}

void Toolbar::on_historyBtn_clicked(){
    emit on_historyBtn_passSignal();
}

void Toolbar::on_bookmarkerBtn_clicked(){
    emit on_bookmarkerBtn_passSignal();
}

void Toolbar::on_settingBtn_clicked(){


}

void Toolbar::on_accountBtn_clicked(){
    emit on_accountBtn_passSignal();
}

void Toolbar::on_downloadBtn_clicked(){
    emit on_downloadBtn_passSignal();
}

void Toolbar::start_search(){
    qDebug("search");
    if(this->urlBar->hasFocus()){
        // todo: 触发搜索
        SearchEngineManager seMgr;
        QString Bartext=seMgr.getSearchEngineUrl()+urlBar->text();
        if(IsUrl(urlBar->text())){
            qDebug()<<"成功跳转";
            m_window->my_tab->setUrl(QUrl::fromUserInput(this->urlBar->text()));
        }else if(!IsUrl(urlBar->text())){
            qDebug()<<"成功搜索";
            m_window->my_tab->setUrl(QUrl(Bartext));
        }
    }
}

void Toolbar::home_page(){
    // todo: 前往首页
    emit on_homeBtn_passSignal();
}

void Toolbar::back_page(){
    // todo: 返回上一个页面
    emit on_backBtn_passSignal();
}

void Toolbar::front_page(){
    // todo: 前往下一个页面
    emit on_goBtn_passSignal();
}

void Toolbar::setParentWindow(BrowserWindow *Parent){
    m_window=Parent;
};

bool Toolbar::IsUrl(const QString input){
    const QString url="^http:.*|^https:.*|^www\..*";
    QRegularExpression trueUrl;
    trueUrl.setPattern(url);
    QRegularExpressionMatch match = trueUrl.match(input);
    if(match.hasMatch()){
        qDebug()<<"匹配成功";
        return (true);
    } else {
        qDebug()<<"匹配失败";
        return (false);
    }
}
