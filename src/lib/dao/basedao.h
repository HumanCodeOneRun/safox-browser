#ifndef BASEDAO_H
#define BASEDAO_H

#include <QDebug>
#include <QUrl>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QReadWriteLock>
#include <QtSql/QSqlError>
#include <QtSql/QSqlRecord>
#include <QThreadStorage>
#include <memory>
#include "connections.h"
#include "taskscheduler/databasetaskscheduler.h"

#define DEFAULT_TABLE_NAME "dummy_table"

class BaseDao {
public:
    explicit BaseDao(std::shared_ptr<DatabaseTaskScheduler> _scheduler, const QString& _table_name=DEFAULT_TABLE_NAME);  

    bool isconnected();
    void close();

    bool isTableExist();
    virtual bool createTable();


    QString getTableName();

    // for debug purpose
    virtual void printInfo();
    QVector<QVariant> getcolumns();
    virtual ~BaseDao();

    

protected:
    QString table_name;
    static QThreadStorage< DbConnection* > db_connection;

    std::shared_ptr<DatabaseTaskScheduler> scheduler;

    static void check_thread_connection();

};


#endif
