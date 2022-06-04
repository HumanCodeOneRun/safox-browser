#include "iconmanager.h"
#include <QApplication>
#include <unistd.h>
bool icon_test(){
    QWebEngineView* view = new QWebEngineView();
    auto page = view->page();
    QObject::connect(page, &QWebEnginePage::iconChanged, [view](const QIcon& icon){
        auto url = view->url();
        IconManager::check_local_cache(url, icon);
        
    });

    page->load(QUrl("https://www.baidu.com"));
    view->show();

    return true;
}

bool get_icon_test(){
    QString local_path = IconManager::get_local_cache(QUrl("https://www.baidu.com"));
    QString local_path2 = IconManager::get_local_cache(QUrl("https://www.baidu.com/s?wd=测试&rsv_spt=1&rsv_iqid=0xae20bd6700101980&issp=1&f=8&rsv_bp=1&rsv_idx=2&ie=utf-8&tn=baiduhome_pg&rsv_enter=1&rsv_dl=tb&rsv_sug3=5&rsv_sug2=0&rsv_btype=i&inputT=732&rsv_sug4=732"));
    qDebug() << local_path;
    qDebug() << local_path2;

    return 1;
}


int main(int argc, char** argv){
    QApplication app(argc, argv);
    
    icon_test();

    sleep(5);

    get_icon_test();

    return app.exec();
}