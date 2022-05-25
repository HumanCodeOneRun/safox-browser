#include "iconmanager.h"
#include <QApplication>
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

int main(int argc, char** argv){
    QApplication app(argc, argv);
    
    icon_test();
    
    app.exec();
    return 0;
}