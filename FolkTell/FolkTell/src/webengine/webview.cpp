#include "webview.h"



void WebView::changeTitle(const QString& newTitle) {
    title = newTitle;
    //qDebug()<<"title in changeTitle: "<<title;
    emit(sendChangedWebView(this));
    
}

void WebView::changeUrl(const QUrl& newUrl) {
    url = newUrl;
    //qDebug()<<"url in changeUrl: "<<url;
}


WebView::WebView(QWidget* parent):
QWebEngineView(parent)
{
    QObject::connect(this, &QWebEngineView::titleChanged, this, &WebView::changeTitle);
    QObject::connect(this, &QWebEngineView::urlChanged, this, &WebView::changeUrl);
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

bool WebView::getConnectedToHistory() {
    return connectedToHistory;
}

void WebView::setConnectedToHistory(bool _connectedToHistory) {
    connectedToHistory = _connectedToHistory;
}
