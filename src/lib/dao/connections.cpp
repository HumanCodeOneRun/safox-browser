#include "connections.h"
#include <QDebug>
#include <QSqlError>
int DbConnection::conn_count = 0;

bool DbConnection::checkdbpath(const QString& _db_path){
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

DbConnection::DbConnection(const QString& _db_path):db_path(_db_path){
    if(!this->checkdbpath(db_path))
        return;

    // open a connection, each thread get one connection
    this->conn_name = "conn_"+QString::number(DbConnection::conn_count);
    if (!QSqlDatabase::contains(this->conn_name))
        DbConnection::conn_count++;
        auto db = QSqlDatabase::addDatabase("QSQLITE", this->conn_name);
    
        (db).setDatabaseName(this->db_path);
        if(!db.open()){
            qDebug() << "[error]fail to open db! " << db.lastError().text();
        }

}

QSqlDatabase DbConnection::get_db_connection(){
    return QSqlDatabase::database(this->conn_name);
}

DbConnection::~DbConnection(){
    QSqlDatabase::removeDatabase(this->conn_name);
}