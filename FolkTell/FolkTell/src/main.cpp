#include "browserwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QtWebEngineCore/QtWebEngineCore>
#include <QtWebEngineWidgets/QWebEngineView>
#include <QDebug>
#include <QObject>
#include "src/BookmarkModel.h"

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
    BrowserWindow w;

    BookmarkModel* model = new BookmarkModel();
    qDebug() << model->initGetGroups();
    model->addBookmark("必应", QUrl("www.bing.com"), "test");


    //w.show();
    //return a.exec();
    return 1;

}
