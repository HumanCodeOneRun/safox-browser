//#include "browserwindow/browserwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QtWebEngineCore/QtWebEngineCore>
#include <QtWebEngineWidgets/QWebEngineView>
#include <QDebug>
#include <QObject>

#include "./lib/webengine/webview.h"
#include "lib/history/historymodel.h"


int main(int argc, char *argv[])
{
    
    
    QApplication a(argc, argv);
    WebView* webview = new WebView();
    //AdblockRequestInterceptor interceptor;
    //webview->page()->setUrlRequestInterceptor(&interceptor);
    webview->setAdblockRequestInterceptor();
    webview->setDefaultRequestInterceptor();
    webview->load(QUrl("https://www.douban.com"));
    webview->show();
    
    return a.exec();
}

