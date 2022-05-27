//
// Created by Howell Young on 2022/5/27.
//
#include "QDebug"
#include "Config.h"
#include "QString"
#include "core/useragent/useragent.h"
#include "QApplication"
#include <QtWebEngineCore/QtWebEngineCore>
#include <QtWebEngineWidgets/QWebEngineView>
#include "tabwidget.h"
#include "core/webengine/webview.h"
#include "browserwindow/browserwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QtWebEngineCore/QtWebEngineCore>
#include <QtWebEngineWidgets/QWebEngineView>
#include <QDebug>
#include <QObject>
#include "src/core/app/mainapplication.h"
int main(int argc, char *argv[]){

    MainApplication a(argc, argv);
    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "safox_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    std::shared_ptr<BrowserWindow> w = a.getNewWindow();
    UserAgentManager ua;
    QString name = "Safari";
    ua.setUserAgent(w->my_tab, name);
    qDebug()<<w->my_tab->getProfile()->httpUserAgent();
    return a.exec();


}