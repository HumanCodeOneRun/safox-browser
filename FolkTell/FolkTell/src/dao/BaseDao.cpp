#include "BaseDao.h"
#include <string>
#include <fstream>
#include <iostream>

bool BaseDao::checkdbpath(const QString& _db_path){
    std::string path_string = _db_path.toStdString();
    std::ifstream fin(path_string);
    if(!fin){
        std::ofstream fout;
        fout.open(path_string, std::ios::app|std::ios::out);
        
        if(!fout.is_open()){
            qDebug() << "[error] fail to open/create db file!\n";
            return false;
        }
    }

    return true;
}

BaseDao::BaseDao(const QString& _db_path):db_path(_db_path), table_name("dummy_table"){
    if(!this->checkdbpath(_db_path))
        return;
    
    this->db = QSqlDatabase::addDatabase("QSQLITE");
    (this->db).setDatabaseName(this->db_path);
    if(!(this->db).open()){
        qDebug() << "[error]fail to open db! " << db.lastError().text();
    }

    if(!isTableExist()){
        if(!createTable())
            return;
    }
    
}

BaseDao& BaseDao::getDao(){
    static BaseDao dao;
    return dao;
}

bool BaseDao::isconnected(){
    return (this->db).isOpen();
}

void BaseDao::close(){
    (this->db).close();
}

bool BaseDao::isTableExist(){
    return (this->db).tables().contains(this->table_name);
}

bool BaseDao::createTable(){
    QString cmd = "CREATE TABLE IF NOT EXISTS " + this->table_name +
                " (ID INTEGER PRIMARY KEY, NAME TEXT)";

    QSqlQuery query(cmd);

    if(!query.exec()){
        qDebug() << "[error]fail to create dummy table " << query.lastError().text();
        return false;
    }

    return true;
}

QSqlQuery BaseDao::RunQuery(const QString& cmd){
    QSqlQuery query(cmd);
    query.exec();
    return query;
}

void BaseDao::printInfo(){
    if (!(this->db).open()){
        qDebug() <<"[error] db is not connected yet.\n";
        return;
    }

    qDebug() << "[info] database name is: "+(this->db).databaseName();
    qDebug() << "[info] connection name is: "+(this->db).connectionName();
    qDebug() << "[info] current table name is: " +(this->table_name);
}

BaseDao::~BaseDao(){
    this->close();
}