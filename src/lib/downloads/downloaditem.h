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
    
    inline QString get_name() { return this->name; }
    inline QString get_save_path() {return this->save_path; }
    inline QString get_download_path () { return this->download_path.toString();}
    inline QString get_icon() { return this->Icon.toString(); }

public Q_SLOTS:
    inline void set_received(qint64 bytes) {
        this->bytes_received = bytes; 
        //qDebug() << "received bytes: " << this->bytes_received;
        emit bytes_received_changed(this->bytes_received);
    }
    inline void set_total(qint64 bytes) {
        this->bytes_total = bytes; 
        //qDebug() << "total bytes: " << this->bytes_total;
        emit bytes_total_changed(this->bytes_total);
    }

    inline void set_finished(bool ok){
        this->finished = ok;
        emit finish_changed(ok);
    }

    inline void on_pause(){
        qDebug() << "[info] download pause";
        this->pause = true;
        this->download_request->pause();
    }

    inline void on_resume(){
        qDebug() << "[info] download resume";
        this->pause = false;
        this->download_request->resume();
    }

    inline void on_cancel(){
        qDebug() << "[info] download cancel";
        this->pause = false;
        this->download_request->cancel();
    }


signals:
    void bytes_received_changed(qint64);
    void bytes_total_changed(qint64);
    void finish_changed(bool);

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