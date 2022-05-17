#include "basedao.h"
#include <string>
#include <fstream>
#include <iostream>

QThreadStorage< DbConnection* > BaseDao::db_connection;

BaseDao::BaseDao(std::shared_ptr<DatabaseTaskScheduler> _scheduler, const QString& _table_name):table_name(_table_name){
    this->scheduler = _scheduler;

}

void BaseDao::check_thread_connection(){
    
    if(!BaseDao::db_connection.hasLocalData()){
        BaseDao::db_connection.setLocalData(new DbConnection());
    }
}

bool BaseDao::isconnected(){
    return (BaseDao::db_connection.localData()->get_db_connection()).isOpen();
}

void BaseDao::close(){
    (BaseDao::db_connection.localData()->get_db_connection()).close();
}

bool BaseDao::isTableExist(){
    return (BaseDao::db_connection.localData()->get_db_connection()).tables().contains(this->table_name);
}

bool BaseDao::createTable(){
    QString cmd = "CREATE TABLE IF NOT EXISTS " + this->table_name +
                " (ID INTEGER PRIMARY KEY, NAME TEXT UNIQUE)";

    QSqlQuery query(cmd);

    if(!query.exec()){
        qDebug() << "[error] fail to create dummy table " << query.lastError().text();
        return false;
    }

    return true;
}


QString BaseDao::getTableName(){
    return this->table_name;
}


void BaseDao::printInfo(){
    if (!(BaseDao::db_connection.localData()->get_db_connection()).open()){
        qDebug() <<"[error] db is not connected yet.\n";
        return;
    }

    qDebug() << "[info] database name is: "+(BaseDao::db_connection.localData()->get_db_connection()).databaseName();
    qDebug() << "[info] connection name is: "+(BaseDao::db_connection.localData()->get_db_connection()).connectionName();
    qDebug() << "[info] current table name is: " +(this->table_name);
}

QVector<QVariant> BaseDao::getcolumns(){
    QString cmd = "PRAGMA  table_info("+this->table_name+")";
    QSqlQuery query(BaseDao::db_connection.localData()->get_db_connection());
    query.prepare(cmd);
    
    QVector<QVariant> ret;
    if(!query.exec()){
        qDebug() << "[error] fail to query by id,  " << query.lastError().text();
        return ret;
    }
    
    while(query.next()){
        ret.append({query.value(0), query.value(1),query.value(2),query.value(3),query.value(4)});
    }

    return ret;
}

BaseDao::~BaseDao(){
    this->close();
}
