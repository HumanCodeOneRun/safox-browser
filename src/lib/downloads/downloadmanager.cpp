#include "downloadmanager.h"

DownloadManager::DownloadManager(){
    //load_download_items();
}

QVector< std::shared_ptr<DownloadItem> > DownloadManager::get_items(){
    return download_items.values();
}




// slots
void DownloadManager::on_requested(QWebEngineDownloadRequest* request, const QUrl& url, const QUrl& icon, const QString& save_path,const QString& name){
    // create a download task
    auto item = std::make_shared<DownloadItem>(name, icon, request, url.toString(), save_path);
    download_items[url.toString()] = item;

    connect(request, &QWebEngineDownloadRequest::totalBytesChanged, 
        [item, request](){
            item->set_total(request->totalBytes());
        });
    connect(request, &QWebEngineDownloadRequest::receivedBytesChanged, 
        [item, request](){
            item->set_received(request->receivedBytes());
        });
    connect(request, &QWebEngineDownloadRequest::isFinishedChanged, 
        [item, request](){
            item->set_finished(request->isFinished());

            if(request->state() == QWebEngineDownloadRequest::DownloadCompleted)
                qDebug() << "[info] download succeeded!";
            else if(request->state() == QWebEngineDownloadRequest::DownloadInterrupted)
                qDebug() << "[warning] download was interrupted.";
            request->cancel();

        });

    request->setDownloadDirectory(save_path);
    request->setDownloadFileName(name);
    emit download_items_num_changed();
    request->accept();
}

void DownloadManager::on_delete(const QString& url){
    auto item = this->download_items[url];
    item->on_cancel();
    (this->download_items).remove(url);

    emit download_items_num_changed();
}

void DownloadManager::on_pause(const QString& url){
    auto item = this->download_items[url];
    item->on_pause();
    
}
void DownloadManager::on_resume(const QString& url){
    auto item = this->download_items[url];
    item->on_resume();
}

DownloadManager::~DownloadManager(){
    
}