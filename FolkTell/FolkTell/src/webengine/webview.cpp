#include "webview.h"



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

/*
something to optimize:
1, maybe when changed happening, we don't have to send the entire webview*?
but compare to do, not to do seems to have no advantage.
*/