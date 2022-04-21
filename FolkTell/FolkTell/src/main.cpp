#include "browserwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QtWebEngineCore/QtWebEngineCore>
#include <QtWebEngineWidgets/QWebEngineView>
#include <QDebug>
#include <QtSql/QSqlDatabase>
#include "dao/BaseDao.h"

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
    BaseDao dao = BaseDao::getDao();
    bool ok = dao.RunInsert("insert into dummy_table (ID, NAME) VALUES (0, test)");
    
    
    w.show();
    return a.exec();
}
