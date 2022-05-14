#include "downloadmanager.h"
#include <QApplication>
#include <QWebEngineView>
#include <unistd.h>

void download_test(){
    
    auto view = std::make_shared<QWebEngineView>();
    auto manager = std::make_shared<DownloadManager>();

    QObject::connect(view.get()->page()->profile(), &QWebEngineProfile::downloadRequested,
    [manager](QWebEngineDownloadRequest* request){
        qDebug() << "emit request";
        QUrl url = request->url();
        QUrl icon("icon.com");
        QString save_path = "~/Downloads";
        QString name = request->downloadFileName();
        qDebug() << "name is " << name;
        manager->on_requested(request, url, icon, save_path, name);
    }
    );

    view->page()->download(QUrl("https://repo.anaconda.com/miniconda/Miniconda3-py39_4.11.0-MacOSX-arm64.sh"));
    
}

void pause_and_resume_test(){
    auto view = std::make_shared<QWebEngineView>();
    auto manager = std::make_shared<DownloadManager>();

    QObject::connect(view.get()->page()->profile(), &QWebEngineProfile::downloadRequested, 
    [manager](QWebEngineDownloadRequest* request){
        QUrl url = request->url();
        QUrl icon("icon.com");
        QString save_path = "~/";
        QString name = "test.sh";
        qDebug() << "name is " << name;
        manager->on_requested(request, url, icon, save_path, name);

        manager->on_pause(url.toString());

        sleep(5);

        manager->on_resume(url.toString());
    }
    ); 

    view->page()->download(QUrl("https://repo.anaconda.com/miniconda/Miniconda3-py39_4.11.0-MacOSX-arm64.sh"));
    
}

void delete_test(){
    auto view = std::make_shared<QWebEngineView>();
    auto manager = std::make_shared<DownloadManager>();

    QObject::connect(view.get()->page()->profile(), &QWebEngineProfile::downloadRequested, 
    [manager](QWebEngineDownloadRequest* request){
        QUrl url = request->url();
        QUrl icon("icon.com");
        QString save_path = "~/";
        QString name = "test.sh";
        manager->on_requested(request, url, icon, save_path, name);
        
        manager->on_delete(url.toString());
    }
    ); 

    view->page()->download(QUrl("https://repo.anaconda.com/miniconda/Miniconda3-py39_4.11.0-MacOSX-arm64.sh"));
}

int main(int argc, char** argv){
    QApplication app(argc, argv);

    pause_and_resume_test();
    return app.exec();
}
