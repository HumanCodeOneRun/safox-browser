#include <ctime>
#include "webview.h"
#include <QApplication>
#include <QWebEngineView>

void setAdblockRequestInterceptorTest() {
    WebView* webview = new WebView();
    webview->setAdblockRequestInterceptor("../../dependent_files/easylist.txt");
    webview->load(QUrl("https://www.douban.com"));
    webview->show();
}

void setDefaultRequestInterceptorTest() {
    WebView* webview = new WebView();
    webview->setAdblockRequestInterceptor("../../dependent_files/easylist.txt");
    webview->setDefaultRequestInterceptor();
    webview->load(QUrl("https://www.douban.com"));
    webview->show();
}

int main(int argc, char** argv){
    QApplication app(argc, argv);
    setAdblockRequestInterceptorTest();
    //setDefaultRequestInterceptorTest();
    return app.exec();
}