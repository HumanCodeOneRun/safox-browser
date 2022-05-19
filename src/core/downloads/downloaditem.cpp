#include "downloaditem.h"

DownloadItem::DownloadItem()
:   name(""),
    save_path(""),
    download_path(QUrl("")),
    Icon(QUrl("")),
    bytes_received(0),
    bytes_total(0),
    finished(false),
    inprogress(false),
    download_request(nullptr)
{
}

DownloadItem::DownloadItem(const QString& _name, const QUrl& icon, QWebEngineDownloadRequest* _reply, const QString& d_path, const QString& s_path)
:   name(_name),
    save_path(s_path),
    download_path(d_path),
    Icon(icon),
    bytes_received(0),
    bytes_total(0),
    finished(false),
    inprogress(false),
    download_request(_reply)
{
}

DownloadItem::~DownloadItem(){
    
}

