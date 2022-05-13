#ifndef DOWNLOADITEM_H_
#define DOWNLOADITEM_H_
#include <QWebEngineDownloadRequest>
#include <QString>
#include <QUrl>
#include <QFile>
#include <QStandardPaths>
#include <QObject>
#include <QWebEnginePage>
#include <QWebEngineProfile>

// describe a download item (a single row in download managment)
class DownloadItem: public QObject{
    Q_OBJECT

public:
    DownloadItem();
    DownloadItem(const QString& _name, const QUrl& icon, QWebEngineDownloadRequest* _request, const QString& d_path, const QString& s_path);
    
    ~DownloadItem();

    inline QWebEngineDownloadRequest* get_request() { return this->download_request; }
    
public Q_SLOTS:
    void set_received(qint64 bytes);

private:
    QString name;
    QString save_path;
    QUrl download_path;
    QUrl Icon;

    QWebEngineDownloadRequest* download_request;
    
    qint64 bytes_received;
    qint64 bytes_total;
    // flags
    bool finished;
    bool inprogress;
    bool pause;
};



#endif