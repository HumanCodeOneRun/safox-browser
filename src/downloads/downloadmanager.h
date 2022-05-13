#ifndef DOWNLOADMANAGER_H_
#define DOWNLOADMANAGER_H_
#include <QObject>
#include <QVector>
#include <memory>
#include "downloaditem.h"

class DownloadItem;

class DownloadManager: public QObject{
    Q_OBJECT


public Q_SLOTS:
    void on_requested(QWebEngineDownloadRequest* request, const QUrl& url, const QUrl& icon,const QString& save_path, const QString& download_path, const QString& name);


    void pauseDownload();
    void deleteDownload();
    void resumeDownload();

signals:
    

public:
    DownloadManager();
    ~DownloadManager();

    QVector< std::unique_ptr<DownloadItem> > get_items();
    
private:
    QVector< std::unique_ptr<DownloadItem> > download_items;

    
};

#endif