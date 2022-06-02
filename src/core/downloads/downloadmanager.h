#ifndef DOWNLOADMANAGER_H_
#define DOWNLOADMANAGER_H_

#include <QObject>
#include <QVector>
#include <memory>
#include "downloaditem.h"

#define DOWNLOAD_JSON "download_items.json"

class DownloadItem;

class DownloadManager : public QObject {
Q_OBJECT


public Q_SLOTS:

    void on_requested(QWebEngineDownloadRequest *request, const QUrl &url, const QUrl &icon, const QString &save_path,
                      const QString &name);

    void on_delete(const QString &url);

    void on_pause(const QString &url);

    void on_resume(const QString &url);


signals:

    void download_items_num_changed();

public:
    DownloadManager();

    ~DownloadManager();

    QMap<QString, std::shared_ptr<DownloadItem>> get_items();

    //void save_download_items();
    //void load_download_items();
private:
    QMap<QString, std::shared_ptr<DownloadItem>> download_items;

};

#endif