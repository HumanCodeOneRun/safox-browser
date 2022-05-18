#ifndef ADBLOCK_REQUEST_INTERCEPTOR_H
#define ADBLOCK_REQUEST_INTERCEPTOR_H


#include <QtWebEngineCore>
#include <QWebEngineView>
#include <QThread>
#include <QFile>

#include "../third_party/ad-block/ad_block_client.h"

class AdblockRequestInterceptor : public QWebEngineUrlRequestInterceptor {
Q_OBJECT
public:
    AdblockRequestInterceptor(QObject *parent = nullptr);

    void interceptRequest(QWebEngineUrlRequestInfo &info);

private:
    AdBlockClient client;
};

#endif
/*
*/
