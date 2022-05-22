#include "adblock_request_interceptor.h"


AdblockRequestInterceptor::AdblockRequestInterceptor(QObject *parent) : QWebEngineUrlRequestInterceptor(parent) {
    QThread *thread = QThread::create([this]{
        QFile file("../dependent_files/easylist.txt");
        QString easyListTxt;

        if(!file.exists()) {
            qDebug() << "No easylist.txt file found.";
        } else {
            if (file.open(QIODevice::ReadOnly | QIODevice::Text)){
                easyListTxt = file.readAll();
            }
            file.close();
            client.parse(easyListTxt.toStdString().c_str());
        }
        //qDebug()<<"test cuddly terrible things happen";
    });
    thread->start();
}

void AdblockRequestInterceptor::interceptRequest(QWebEngineUrlRequestInfo &info) {
    if (client.matches(info.requestUrl().toString().toStdString().c_str(), 
        FONoFilterOption, info.requestUrl().host().toStdString().c_str())) {
            qDebug() << "Blocked: " << info.requestUrl();
            info.block(true);
    }
}

/*



AdblockRequestInterceptor::AdblockRequestInterceptor(QObject *parent) : QWebEngineUrlRequestInterceptor(parent)
{
    QThread *thread = QThread::create([this]{
        QFile file("../easylist.txt");
        QString easyListTxt;

        if(!file.exists()) {
            qDebug() << "No easylist.txt file found.";
        } else {
            if (file.open(QIODevice::ReadOnly | QIODevice::Text)){
                easyListTxt = file.readAll();
            }
            file.close();
            client.parse(easyListTxt.toStdString().c_str());
        }
        qDebug()<<"test cuddly terrible things happen";
    });
    thread->start();
}

void AdblockRequestInterceptor::interceptRequest(QWebEngineUrlRequestInfo &info)
{
    if (client.matches(info.requestUrl().toString().toStdString().c_str(), 
        FONoFilterOption, info.requestUrl().host().toStdString().c_str())) {
            qDebug() << "Blocked: " << info.requestUrl();
            info.block(true);
    }
}
*/
