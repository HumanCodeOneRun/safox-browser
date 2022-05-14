//
// Created by Howell Young on 2022/5/13.
//
#include <QUrl>
#include <QString>
#include "homepage.h"
#include <fstream>
#include "config.h"


QUrl getHomePage() {
    Config con;
    QString hpStr = Config().Get("homepage").toString();
    QUrl hpUrl(hpStr);
    return hpUrl;
}
bool setHomePage(QUrl homepage) {
    Config con;
    QString hpStr = homepage.toString();
    con.Set("homepage",hpStr);
    if (getHomePage() == homepage) {
        return true;
    }else {
        return false;
    }

}
