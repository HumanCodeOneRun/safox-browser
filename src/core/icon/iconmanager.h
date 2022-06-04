#ifndef _ICONMANAGER_H_
#define _ICONMANAGER_H_
#include <QUrl>
#include <QString>
#include <QObject>
#include <QWebEngineView>
#include <QIODevice>
#include <QFile>
#include <QDir> 
#include <QByteArray>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QDebug>
#include <QImage>
#include <QIcon>
#define ICON_SAVE_DIR "./icon_cache/"

class IconManager : public QObject{
public:
    static bool check_local_cache(const QUrl& url, const QIcon& icon);
    static QString get_local_cache(const QUrl& url);
    static bool download_from_url(const QUrl& url);
    static bool save_icon(const QUrl& url, const QIcon& icon);
};


#endif
