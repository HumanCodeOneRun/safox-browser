//
// Created by Howell Young on 2022/5/27.
//

#ifndef SAFOX_UASERAGENT_H
#define SAFOX_UASERAGENT_H
#include "QString"
#include "tabwidget.h"


class UserAgentManager : public QObject{
public:
    explicit UserAgentManager();

    ~UserAgentManager();

    void addUserAgent(QString name, QString value);

    void deleteUserAgent(QString name);

    void setUserAgent(tabwidget * tabwidget, const QString name);


};
#endif //SAFOX_UASERAGENT_H
