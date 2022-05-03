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
//include "history/historymodel.h"
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include "dao/basedao.h"
#include "browserwindow/browserwindow.h"


int main(int argc, char *argv[])
{
    //just test code
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
}







