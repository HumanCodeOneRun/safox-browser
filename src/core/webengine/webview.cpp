/*
 * @Author: SC-WSKun 540610423@qq.com
 * @Date: 2022-05-14 11:54:54
 * @LastEditors: SC-WSKun 540610423@qq.com
 * @LastEditTime: 2022-05-17 16:26:16
 * @FilePath: \safox\src\core\webengine\webview.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include "webview.h"
#include "browserwindow.h"
#include "../core/adblock/adblock_request_interceptor.h"
#include "../core/adblock/default_request_interceptor.h"


void WebView::changeTitle(const QString& newTitle) {
    title = newTitle;
    //qDebug()<<"title in changeTitle: "<<title;
    emit(sendChangedWebView(this));
    
}

void WebView::changeUrl(const QUrl& newUrl) {
    url = newUrl;
    emit(sendChangedWebView(this));
    //qDebug()<<"url in changeUrl: "<<url;
}

void WebView::changeIconUrl(const QUrl& newIconUrl) {
    iconUrl = newIconUrl;
    emit(sendChangedWebView(this));
    //qDebug()<<"changeIconUrl test "<<iconUrl.toString();
}


WebView::WebView(QWidget* parent):
QWebEngineView(parent)
{
    QObject::connect(this, &QWebEngineView::titleChanged, this, &WebView::changeTitle);
    QObject::connect(this, &QWebEngineView::urlChanged, this, &WebView::changeUrl);
    QObject::connect(this, &QWebEngineView::iconUrlChanged, this, &WebView::changeIconUrl);
    connectedToHistory = 0;
    m_adblockRequestInterceptor = NULL;
    m_defaultRequestInterceptor = NULL;

}




QString WebView::getTitle() {
    if(title.isEmpty())
        title = url.host();
    if(title.isEmpty())
        title = "Empty Page";
    return title;
}

QUrl WebView::getUrl() {
    return url;
}

QUrl WebView::getIconUrl() {
    return iconUrl;
}

bool WebView::getConnectedToHistory() {
    return connectedToHistory;
}

void WebView::setConnectedToHistory(bool _connectedToHistory) {
    connectedToHistory = _connectedToHistory;
}

void WebView::setAdblockRequestInterceptor(const QString _easylist_path) {
    if(!m_adblockRequestInterceptor)
        m_adblockRequestInterceptor = new AdblockRequestInterceptor(_easylist_path);
    this->page()->setUrlRequestInterceptor(m_adblockRequestInterceptor);
    this->reload();
}

void WebView::setDefaultRequestInterceptor() {
    if(!m_defaultRequestInterceptor)
        m_defaultRequestInterceptor = new DefaultRequestInterceptor();
    this->page()->setUrlRequestInterceptor(m_defaultRequestInterceptor);
    this->reload();
}

/*
something to optimize:
1, maybe when changed happening, we don't have to send the entire webview*?
but compare to do, not to do seems to have no advantage.
*/

bool WebView::isWebActionEnabled(QWebEnginePage::WebAction webAction) const
{
    return this->page()->action(webAction)->isEnabled();
}



QIcon WebView::favIcon() const
{
    QIcon favIcon = icon();
        return favIcon;
}
QWebEngineView* WebView::createWindow(QWebEnginePage::WebWindowType type){
    BrowserWindow *mainWindow = qobject_cast<BrowserWindow*>(window());
    if (!mainWindow)
        return nullptr;

    switch (type) {
        case QWebEnginePage::WebBrowserTab: {
            return mainWindow->my_tab->createTab();
        }
        case QWebEnginePage::WebBrowserBackgroundTab: {
            return mainWindow->my_tab->createView();
        }

    }
    return nullptr;
}
