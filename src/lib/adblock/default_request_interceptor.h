#ifndef DEFAULT_REQUEST_INTERCEPTOR_H
#define DEFAULT_REQUEST_INTERCEPTOR_H

#include <QtWebEngineCore>
#include <QWebEngineView>

class DefaultRequestInterceptor : public QWebEngineUrlRequestInterceptor {
    public:
    DefaultRequestInterceptor(QObject* parent = nullptr);
    void interceptRequest(QWebEngineUrlRequestInfo &info);
};

#endif