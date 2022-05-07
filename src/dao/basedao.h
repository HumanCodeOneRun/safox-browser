#ifndef BASEDAO_H
#define BASEDAO_H

#include <QDebug>
#include <QUrl>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QReadWriteLock>
#include <QtSql/QSqlError>
#include <QtSql/QSqlRecord>

#define DEFAULT_DB_PATH "./.folktell.db"
#define DEFAULT_TABLE_NAME "dummy_table"

class BaseDao {
public:
    explicit BaseDao(const QString& _db_path=DEFAULT_DB_PATH, const QString& _table_name=DEFAULT_TABLE_NAME);  
    static BaseDao& getDao();


    bool isconnected();
    void close();

    bool isTableExist();
    virtual bool createTable();


    QString getTableName();
    QString getDbPath();

    // for debug purpose
    virtual void printInfo();
    QVector<QVariant> getcolumns();
    ~BaseDao();

protected:
    bool checkdbpath(const QString& _db_path);
    QString db_path;
    QString table_name;
    QSqlDatabase db;


};


#endif
