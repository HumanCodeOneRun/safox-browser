//#include "browserwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>

//test lib used by cuddly
//#include "history/historymodel.h"
#include <iostream>
#include <QObject>
#include <QList>
#include <string>
#include <QString>
#include <QDateTime>
#include <QDate>
#include <QDebug>
#include <QMainWindow>
#include <QWebEnginePage>

//#include "webengine/webview.h"
//#include "history/history.h"
#include "history/historymodel.h"
#include <QHash>



int main(int argc, char *argv[])
{
    //just test code
    QApplication a(argc, argv);
    History* history = new History();
    
    WebView* webview = new WebView();
    webview->load(QUrl("https://doc.qt.io/qt-5/qwebengineview.html"));
    history->addHistoryEntry(webview);
    
    

    WebView* webview1 = new WebView();
    webview1->load(QUrl("https://www.baidu.com"));
    history->addHistoryEntry(webview1);

    WebView* webview2 = new WebView();
    webview2->load(QUrl("https://www.taobao.com"));
    history->addHistoryEntry(webview2);

    a.exec();    
}


/*
oringinal code in main():
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
    BrowserWindow w;
    w.show();
    return a.exec();


*/


