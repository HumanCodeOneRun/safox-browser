#include "iconmanager.h"

bool IconManager::check_local_cache(const QUrl& url, const QIcon& icon){
    QString local_path = ICON_SAVE_DIR + url.host()+QString(".png");
    if(QFile::exists(local_path))
        return true;
    else
        return IconManager::save_icon(url, icon);
}


QString IconManager::get_local_cache(const QUrl& url){
    QString local_path = ICON_SAVE_DIR + url.host()+QString(".png");
    if(QFile::exists(local_path))
        return local_path;
    else
        return ICON_SAVE_DIR + QString("default_icon.png");
}


bool IconManager::save_icon(const QUrl& url, const QIcon& icon){
    QDir dir;
    if(!dir.exists(ICON_SAVE_DIR)){
        dir.mkdir(ICON_SAVE_DIR);
    }
    
    QString local_path = ICON_SAVE_DIR + url.host()+QString(".png");

    QImage image(icon.pixmap(20, 20).toImage());
    image.save(local_path);

    return true;
}

