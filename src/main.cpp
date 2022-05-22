#include "browserwindow/browserwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QtWebEngineCore/QtWebEngineCore>
#include <QtWebEngineWidgets/QWebEngineView>
#include <QDebug>
#include <QObject>
#include <QUrl>


/*
 * QUrl CommandUrl()
{
    //if 搜索栏输入url 返回搜索栏url
    return QUrl (QStringLiteral("https://www.bing.com"));
}
*/
int main(int argc, char *argv[])
{
    
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

//    QUrl url = CommandUrl();


    BrowserWindow w;
    //w.returnTab()->setUrl(url);
    w.show();
    return a.exec();
}

