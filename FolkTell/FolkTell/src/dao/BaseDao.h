#ifndef BASEDAO_H
#define BASEDAO_H

#include <QDebug>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QReadWriteLock>
#include <QtSql/QSqlError>
#define DEFAULT_DB_PATH "./.folktell.db"

class BaseDao {
public:
    explicit BaseDao(const QString& _db_path=DEFAULT_DB_PATH);  
    static BaseDao& getDao();


    bool isconnected();
    void close();

    bool isTableExist();
    virtual bool createTable();

    // you need to parse the query result yourself
    QSqlQuery RunQuery(const QString& cmd);
    bool RunInsert(QString& cmd);
    bool RunDelete(QString& cmd);
    bool RunUpdate(QString& cmd);

    // for debug purpose
    void printInfo();
    ~BaseDao();

private:

    QString db_path;
    QString table_name;
    QSqlDatabase db;

    bool checkdbpath(const QString& _db_path);

};


#endif