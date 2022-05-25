#include "iconmanager.h"

bool IconManager::check_local_cache(const QUrl& url, const QIcon& icon){
    QString local_path = ICON_SAVE_DIR + url.host()+QString(".png");
    if(QFile::exists(local_path))
        return true;
    else
        return IconManager::save_icon(url, icon);
}

/*
QString IconManager::get_local_cache(const QUrl& url){
    QString local_path = ICON_SAVE_DIR + url.host()+QString(".png");
    if(!IconManager::check_local_cache(url)){
        return "./default.ico";
    }

    return ICON_SAVE_DIR + url.host()+QString(".png");
}
*/

bool IconManager::save_icon(const QUrl& url, const QIcon& icon){
    qDebug() << "enter download";
    QDir dir;
    if(!dir.exists(ICON_SAVE_DIR)){
        dir.mkdir(ICON_SAVE_DIR);
    }
    
    QString local_path = ICON_SAVE_DIR + url.host()+QString(".png");

    QImage image(icon.pixmap(20, 20).toImage());
    image.save(local_path);

    return true;
}

bool IconManager::download_from_url(const QUrl& url){
    qDebug() << "enter download";
    QDir dir;
    if(!dir.exists(ICON_SAVE_DIR)){
        dir.mkdir(ICON_SAVE_DIR);
    }
    
    QString local_path = ICON_SAVE_DIR + url.host()+QString(".png");

    QFile file(local_path);
    if(!file.open(QIODevice::WriteOnly)){
        
        qDebug() << "fail to open" << file.errorString();
        return false;
    }
    

    QNetworkAccessManager manager;
    QNetworkRequest request(url);
    auto reply = manager.get(request);

    QObject::connect(reply, &QNetworkReply::finished, [reply, &file, &url](){
        qDebug() << "enter connect";
        auto byte_array =  reply->readAll();
        auto image = QImage::fromData(byte_array);
        qDebug() << image;
        image.save(ICON_SAVE_DIR + url.host()+QString(".png"), "PNG");

        //file.write(byte_array);
        file.close();
    });
    return true;
}   