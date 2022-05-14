
#ifndef HISTORYDAO_H
#define HISTORYDAO_H

#include "../dao/basedao.h"
#include <QDateTime>
#include <QUrl>
#include <QString>

#define HISTORYDAO_TABLE_NAME "history"


struct HistoryEntry{
    unsigned int urlid;
    QString title;
    QDateTime date;
    QUrl url;
    QUrl iconUrl;
};

class HistoryDao:BaseDao {

    public:
    HistoryDao(const int& _userid, const QString& _db_path = DEFAULT_DB_PATH, const QString& _table_name = HISTORYDAO_TABLE_NAME);

    bool insertHistoryEntry(const unsigned int& id, const QString &title, const QUrl& url, const QUrl& iconUrl, const qint64& timestamp);
    bool createTable();
    bool deleteByUrlid();
    bool deleteByPriKey( const unsigned int& urlid, const QUrl& url);
    bool clearTable();

    bool queryByUserid();
    QList<qint64> queryDayTimestamp();
    QList<HistoryEntry> queryHistoryEntry();

    private://just for test and it should be changed to private
    unsigned int userid;
};

#endif