#include <ctime>
#include "webview.h"
#include <QApplication>
#include <QWebEngineView>
#include "adblock_request_interceptor.h"

void setAdblockRequestInterceptorTest() {
    /*
    WebView* webview = new WebView();
    webview->setAdblockRequestInterceptor("../../dependent_files/easylist.txt");
    webview->load(QUrl("https://www.douban.com"));
    webview->show();
    */
    

    WebView* webview1 = new WebView();
    WebView* webview2 = new WebView();
    AdblockRequestInterceptor* m_adblockRequestInterceptor = new AdblockRequestInterceptor("../../dependent_files/easylist.txt");
    webview1->setAdblockRequestInterceptor(m_adblockRequestInterceptor);
    webview2->setAdblockRequestInterceptor(m_adblockRequestInterceptor);
    webview2->load(QUrl("https://blog.csdn.net/heybeaman/article/details/90896663?utm_medium=distribute.pc_relevant.none-task-blog-2%7Edefault%7EBlogCommendFromMachineLearnPai2%7Edefault-2.control&dist_request_id=&depth_1-utm_source=distribute.pc_relevant.none-task-blog-2%7Edefault%7EBlogCommendFromMachineLearnPai2%7Edefault-2.control"));
    delete webview1;
    webview2->show();
    /*
    confused
    auto webview3 = std::make_shared<WebView> ();
    webview3->load(QUrl("https://www.douban.com"));
    webview3->show();
    */
    
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