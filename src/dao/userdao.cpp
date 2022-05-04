#include "userdao.h"

UserDao::UserDao(const QString& _db_path, const QString& _table_name )
: BaseDao(_db_path, _table_name){
    createTable();

}
UserDao& UserDao::getDao(){
    static UserDao dao;
    return dao;
}
bool UserDao::createTable(){
    QString cmd = "CREATE TABLE IF NOT EXISTS " + this->getTableName() +
                " (ID INTEGER PRIMARY KEY AUTOINCREMENT, NAME TEXT, PASSWORD TEXT);";
    QSqlQuery query(this->db);
    bool ok = query.exec(cmd);

    if(!ok){
        qDebug() << "[error] fail to create User table " << query.lastError().text();
        return false;
    }

    return true;
}


QVector<QVariant> UserDao::QueryById(const int& id){
    QString cmd = "SELECT * from " + this->getTableName() + " WHERE ID="+QString::number(id);
    QSqlQuery query(this->db);
    query.prepare(cmd);
    
    QVector<QVariant> ret;
    if(!query.exec()){
        qDebug() << "[error] fail to query by id,  " << query.lastError().text();
        return ret;
    }
    
    while(query.next()){
        ret.append({query.value(0), query.value(1),query.value(2)});
    }

    return ret;
}

QVector<QVariant> UserDao::QueryByIdPassword(const int& id, const QString& password){
    QString cmd = "SELECT * from " + this->getTableName() + " WHERE ID="+QString::number(id) + " AND PASSWORD=\""+password+"\"";
    QSqlQuery query(this->db);
    query.prepare(cmd);
    
    QVector<QVariant> ret;
    if(!query.exec()){
        qDebug() << "[error] fail to query by id and password,  " << query.lastError().text();
        return ret;
    }
    
    while(query.next()){
        ret.append({query.value(0), query.value(1),query.value(2)});
    }

    return ret;
}

QVector<QVector<QVariant>> UserDao::QueryByName(const QString& name){
    QString cmd = "SELECT * from " + this->getTableName() + " WHERE NAME=\""+name+"\"";
    QSqlQuery query(this->db);
    query.prepare(cmd);

    QVector<QVector<QVariant>> ret;
    if(!query.exec()){
        qDebug() << "[error] fail to query by name,  " << query.lastError().text();
        return ret;
    }

    while(query.next()){
        QVector<QVariant> temp = {query.value(0), query.value(1),query.value(2)};
        ret.emplace_back(temp);
    }

    return ret;
}

bool UserDao::setName(const int& id, const QString& name){
//    QString cmd = "UPDATE " + this->table_name + "SET NAME =\"" + name + "\" WHERE ID"+QString::number(id);
    QString cmd = "UPDATE " + this->getTableName() + " SET NAME= \""+name+"\" WHERE ID= " + QString::number(id);

    QSqlQuery query(this->db);

    query.bindValue(":name", name);
    query.bindValue(":id", id);
    if(!query.prepare(cmd)){
        qDebug() << "[error] fail to prepare cmd in setname: " << query.lastError().text();
        return false;
    }


    if(!query.exec()){
        qDebug() << "[error] fail to exec cmd in setname: " << query.lastError().text();
        return false;
    }


    return true;
}

bool UserDao::setPassword(const int& id, const QString& password){
    QString cmd = "UPDATE " + this->getTableName() + " SET PASSWORD= \""+password+"\" WHERE ID= " + QString::number(id);
    QSqlQuery query(this->db);
    
    if(!query.prepare(cmd)){
        qDebug() << "[error] fail to prepare cmd in setpassword: " << query.lastError().text();
        return false;
    }


    if(!query.exec()){
        qDebug() << "[error] fail to exec cmd in setpassword: " << query.lastError().text();
        return false;
    }

    return true;
}


bool UserDao::insert(const QString& name, const QString& password){
    QString cmd = "INSERT INTO " + this->getTableName() + "( NAME, PASSWORD)"+" VALUES( :name, :password)";

    QSqlQuery query(this->db);
    query.prepare(cmd);
    // query.bindValue(":id", id);
    query.bindValue(":name", name);
    query.bindValue(":password", password);

    if(!query.exec()){
        qDebug() << "[error] fail to insert,  " << query.lastError().text();
        return false;
    }

    return true;
}

bool UserDao::remove(const int& id){
    QString cmd = "DELETE FROM " + this->table_name + " WHERE ID=:id";

    QSqlQuery query(this->db);
    query.prepare(cmd);
    query.bindValue(":id", id);

    if(!query.exec()){
        qDebug() << "[error] fail to delete,  " << query.lastError().text();
        return false;
    }

    return true;
}

QVector<QVariant> UserDao::getcolumns(){
    QString cmd = "PRAGMA  table_info("+this->table_name+")";
    QSqlQuery query(this->db);
    query.prepare(cmd);
    
    QVector<QVariant> ret;
    if(!query.exec()){
        qDebug() << "[error] fail to query all columns,  " << query.lastError().text();
        return ret;
    }
    
    while(query.next()){
        ret.append({query.value(0), query.value(1), query.value(2)});
    }

    return ret;
}
void UserDao::showAll (){
    QString cmd = "SELECT * FROM "+this->table_name;
    QSqlQuery query(this->db);
    query.prepare(cmd);

    if(!query.exec()){
        qDebug() << "[error] fail to query all  " << query.lastError().text();
    }

    while(query.next()){
        int id = query.value(0).toInt();
        QString name = query.value(1).toString();
        QString pwd = query.value(2).toString();
        qDebug()<<id<<name<<pwd;
    }

}

bool UserDao::deleteTable(){
    QString cmd = "DROP TABLE " + this->table_name;
    
    QSqlQuery query(this->db);
    query.prepare(cmd);

    if(!query.exec()){
        qDebug() << "[error] fail to delete table,  " << query.lastError().text();
        return false;
    }

    return true;
}



UserDao::~UserDao(){
}
