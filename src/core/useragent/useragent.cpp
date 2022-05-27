//
// Created by Howell Young on 2022/5/27.
//
#include "useragent.h"
#include "tabwidget.h"
#include "Config.h"

UserAgentManager::UserAgentManager() {
    addUserAgent("Chrome",
                 "Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/51.0.2704.103 Safari/537.36");
    addUserAgent("Opera",
                 "Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/51.0.2704.106 Safari/537.36 OPR/38.0.2220.41");
    addUserAgent("Safari",
                 "Mozilla/5.0 (iPhone; CPU iPhone OS 10_3_1 like Mac OS X) AppleWebKit/603.1.30 (KHTML, like Gecko) Version/10.0 Mobile/14E304 Safari/602.1");
    addUserAgent("IE", "Mozilla/5.0 (compatible; MSIE 9.0; Windows Phone OS 7.5; Trident/5.0; IEMobile/9.0)");
}

void UserAgentManager::addUserAgent(QString name, QString value) {
    Config con;
    con.Set(name, value);
}

void UserAgentManager::deleteUserAgent(QString name) {
    Config con;
    con.Delete(name);
}

void UserAgentManager::setUserAgent(tabwidget *tabwidget, const QString name) {
    Config con;
    QString value = con.Get(name).toString();
    tabwidget->getProfile()->setHttpUserAgent(value);
    qDebug() << value;
}

UserAgentManager::~UserAgentManager() noexcept {}
