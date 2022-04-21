#ifndef BASEDAO_H
#define BASEDAO_H

#include <QDebug>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QReadWriteLock>
#include <QtSql/QSqlError>
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

    // you need to parse the query result yourself
    QSqlQuery RunQuery(const QString& cmd);
    bool RunInsert(const QString& cmd);
    bool RunDelete(const QString& cmd);
    bool RunUpdate(const QString& cmd);

    QString getTableName();
    QString getDbPath();

    // for debug purpose
    void printInfo();
    ~BaseDao();

protected:
    bool checkdbpath(const QString& _db_path);

private:
    QString db_path;
    QString table_name;
    QSqlDatabase db;

};


#endif