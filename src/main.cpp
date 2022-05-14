//#include "browserwindow/browserwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QtWebEngineCore/QtWebEngineCore>
#include <QtWebEngineWidgets/QWebEngineView>
#include <QDebug>
#include <QObject>

int main(int argc, char *argv[])
{
    //test for change interceptor
    QApplication a(argc, argv);
    WebView* webview = new WebView();
    //AdblockRequestInterceptor interceptor;
    //webview->page()->setUrlRequestInterceptor(&interceptor);
    webview->setAdblockRequestInterceptor();
    webview->setDefaultRequestInterceptor();
    webview->load(QUrl("https://www.douban.com"));
    webview->show();
    return a.exec();
}

/*
QApplication a(argc, argv);
    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "FolkTell_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    
    //BrowserWindow w;


    //w.show();
    return a.exec();
*/