#include "tabwidget.h"
#include "ui_tabwidget.h"
#include "webview.h"
#include "browserwindow.h"
#include <QTabBar>

tabwidget::tabwidget(QWidget *parent) :
    QTabWidget(parent),
    ui(new Ui::tabwidget)
{
    QTabBar *Bar = this->tabBar();
    Bar->setMovable(true);
    //设置tab可移动
    Bar->setTabsClosable(true);
    //设置tab可关闭
    Bar->setSelectionBehaviorOnRemove(QTabBar::SelectPreviousTab);
    //关闭当前选项卡时，将previous选项卡设为当前选项卡

    Bar->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(Bar, &QTabBar::customContextMenuRequested, this, &tabwidget::handleContextMenuRequested);
    //设置tab的右键菜单
    connect(Bar, &QTabBar::tabCloseRequested, this, &tabwidget::closeTab);
    connect(this, &QTabWidget::currentChanged, this, &tabwidget::handleCurrentChanged);
    //currentChanged这个是追踪当前焦点，就是获取当前tab标签的时候执行槽函数
    connect(Bar, &QTabBar::tabBarDoubleClicked, [this](int index) {
        if (index == -1)
            createTab();
    });



    setElideMode(Qt::ElideRight);
    //此属性控制在没有足够空间显示给定选项卡栏大小时省略项目

}

tabwidget::~tabwidget()
{
    delete ui;
}


void tabwidget::setupView(WebView *webView)
{
    QWebEnginePage *webPage = webView->page();

    connect(webView, &QWebEngineView::titleChanged, [this, webView](const QString &title) {
        int index = indexOf(webView);
        if (index != -1)
            setTabText(index, title);
        if (currentIndex() == index)
            emit titleChanged(title);
    });
    connect(webView, &QWebEngineView::urlChanged, [this, webView](const QUrl &url) {
        int index = indexOf(webView);
        if (index != -1)
            tabBar()->setTabData(index, url);
        if (currentIndex() == index)
            emit urlChanged(url);
    });
    connect(webPage, &QWebEnginePage::linkHovered, [this, webView](const QString &url) {
        if (currentIndex() == indexOf(webView))
            emit linkHovered(url);
    });
    connect(webPage, &QWebEnginePage::iconChanged, [this, webView](const QIcon &icon) {
        int index = indexOf(webView);
        QIcon ico = icon.isNull() ? QIcon(QStringLiteral(":defaulticon.png")) : icon;

        if (index != -1)
            setTabIcon(index, ico);
        if (currentIndex() == index)
            emit favIconChanged(ico);
    });
    connect(webPage, &QWebEnginePage::windowCloseRequested, [this, webView]() {
        int index = indexOf(webView);
        if (index >= 0)
            closeTab(index);
    });
}

void tabwidget::closeTab(int index)
{
    if (WebView *view = webView(index)) {
        bool hasFocus = view->hasFocus();
        removeTab(index);
        if (hasFocus && count() > 0)
            currentWebView()->setFocus();
        if (count() == 0)
            createTab();
        view->deleteLater();
    }
}

/*
 * 创建一个tab标签页
 * QWebEngineProfile::defaultProfile()：设置一个默认的缓存，将webview放入其中
 * 创建新的标签页
 * setCurrentWidget(webView)：将webview放入当前的widget中
*/

WebView *tabwidget::createTab(bool makeCurrent){
    WebView *webView = createView();
    if (makeCurrent)
    {
        setCurrentWidget(webView);
    }
    return webView;
}

WebView *tabwidget::createView()
{
    WebView *webView = new WebView;
    QWebEnginePage *webPage = new QWebEnginePage(webView);
    webView->setPage(webPage);
    setupView(webView);
    int index=addTab(webView, tr("新标签页"));
    setTabIcon(index, webView->favIcon());
    webView->resize(currentWidget()->size());
    return webView;
}

void tabwidget::handleCurrentChanged(int index)
{
    if (index != -1) {
        WebView *view = webView(index);
        if (!view->getUrl().isEmpty())
        {
            view->setFocus();
        }
        emit titleChanged(view->getTitle());
        emit urlChanged(view->getUrl());

        QIcon pageIcon = view->page()->icon();
        if (!pageIcon.isNull())
        {
            emit favIconChanged(pageIcon);
        }
        emit webActionEnabledChanged(QWebEnginePage::Back, view->isWebActionEnabled(QWebEnginePage::Back));
        emit webActionEnabledChanged(QWebEnginePage::Forward, view->isWebActionEnabled(QWebEnginePage::Forward));
        emit webActionEnabledChanged(QWebEnginePage::Stop, view->isWebActionEnabled(QWebEnginePage::Stop));
        emit webActionEnabledChanged(QWebEnginePage::Reload,view->isWebActionEnabled(QWebEnginePage::Reload));
    } else {
        emit titleChanged(QString());
        emit urlChanged(QUrl());
        emit favIconChanged(QIcon());
        emit webActionEnabledChanged(QWebEnginePage::Back, false);
        emit webActionEnabledChanged(QWebEnginePage::Forward, false);
        emit webActionEnabledChanged(QWebEnginePage::Stop, false);
        emit webActionEnabledChanged(QWebEnginePage::Reload, true);
    }
}

WebView *tabwidget::currentWebView() const
{
    return webView(currentIndex());
}
WebView *tabwidget::webView(int index) const
{
    return qobject_cast<WebView*>(widget(index));
}

//view设置url地址，并且获取焦点
void tabwidget::setUrl(const QUrl &url)
{
    if (WebView *view = currentWebView()) {
        view->setUrl(url);
        view->setFocus();
        BrowserPoint->m_history->addHistoryEntry(view);
    }
}
void tabwidget::nextTab()
{
    int next = currentIndex() + 1;
    if (next == count())
        next = 0;
    setCurrentIndex(next);
}

void tabwidget::previousTab()
{
    int next = currentIndex() - 1;
    if (next < 0)
        next = count() - 1;
    setCurrentIndex(next);
}
void tabwidget::triggerWebPageAction(QWebEnginePage::WebAction action)
{
    if (WebView *webView = currentWebView()) {
        webView->triggerPageAction(action);
        webView->setFocus();
    }
}

void tabwidget::reloadTab(int index){
    int i=0;
    for (i = 0; i < count(); ++i)
        webView(i)->reload();
};
void tabwidget::cloneTab(int index){
    if (WebView *view = webView(index)) {
        WebView *tab = createTab();
        tab->setUrl(view->getUrl());
    }
};
void tabwidget::closeOtherTabs(int index){
    int i=0;
    for (i = count() - 1; i > index; --i)
        closeTab(i);
    for (i = index - 1; i >= 0; --i)
        closeTab(i);
};
void tabwidget::reloadAllTabs(){
    for (int i = 0; i < count(); ++i)
        webView(i)->reload();
};
void tabwidget::addbookmark(int index){
    WebView * view=webView(index);
    BrowserPoint->Browser::m_bookmark->addBookmark(BrowserPoint->Browser::userid,view->getTitle(),view->getUrl(),"默认收藏夹",view->getIconUrl());

};
void tabwidget::setParentWindow(BrowserWindow *ParentWindow)
{
    BrowserPoint=ParentWindow;
};
void tabwidget::handleContextMenuRequested(const QPoint &pos)
{

    QMenu menu;
    int index=-1;
    menu.addAction(tr("新增标签页"), this, &tabwidget::createTab, QKeySequence::AddTab);
    index=tabBar()->tabAt(pos);
    if(index !=-1){
        QAction *action = menu.addAction(tr("刷新标签页"));
        action->setShortcut(QKeySequence::Refresh);
        connect(action, &QAction::triggered, this, [this,index]() {
            reloadTab(index);
        });
        action = menu.addAction(tr("复制标签页"));
        connect(action, &QAction::triggered, this, [this,index]() {
            cloneTab(index);
        });
        menu.addSeparator();
        action = menu.addAction(tr("关闭标签页"));
        action->setShortcut(QKeySequence::Close);
        connect(action, &QAction::triggered, this, [this,index]() {
            closeTab(index);
        });
        action = menu.addAction(tr("关闭其他标签页"));
        connect(action, &QAction::triggered, this, [this,index]() {
            closeOtherTabs(index);
        });
        menu.addSeparator();
        action = menu.addAction(tr("添加书签"));
        connect(action, &QAction::triggered, this, [this,index]() {
            addbookmark(index);
        });
        menu.addSeparator();
    }else{
        menu.addSeparator();
    }
    menu.addAction(tr("重新加载所有标签页"), this, &tabwidget::reloadAllTabs);
    menu.exec(QCursor::pos());

};
QUrl tabwidget::returnHomePage(){
    return homepage;
};
void tabwidget::changeHomePage(QUrl changemain){
    homepage=changemain;
};
