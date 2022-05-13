#include "downloadmanager.h"

DownloadManager::DownloadManager(){

}

QVector< std::unique_ptr<DownloadItem> > DownloadManager::get_items(){
    return download_items;
}




// slots
void DownloadManager::on_requested(QWebEngineDownloadRequest* request, const QUrl& url, const QUrl& icon, const QString& save_path,const QString& download_path, const QString& name){
    // create a download task
    auto item = std::make_unique<DownloadItem>(name, icon, request, download_path, save_path);
    download_items.emplace_back(item);

    
}