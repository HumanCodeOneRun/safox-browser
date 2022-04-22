#include "BookmarkGroupDao.h"

BookmarkGroupDao::BookmarkGroupDao(const QString& _db_path, const QString& _table_name )
: BaseDao(_db_path, _table_name){
    createTable();

}
BookmarkGroupDao& BookmarkGroupDao::getDao(){
    static BookmarkGroupDao dao;
    return dao;
}
bool BookmarkGroupDao::createTable(){
    QString cmd = "CREATE TABLE IF NOT EXISTS " + this->getTableName() +
                " (GID INTEGER PRIMARY KEY AUTOINCREMENT, NAME TEXT UNIQUE, COUNT INT, ICON TEXT);";
    QSqlQuery query(this->db);
    bool ok = query.exec(cmd);

    if(!ok){
        qDebug() << "[error] fail to create bookmarkgroup table " << query.lastError().text();
        return false;
    }

    return true;
}

QVector<QVariant> BookmarkGroupDao::QueryById(const int& id){
    QString cmd = "SELECT * from " + this->getTableName() + " WHERE GID="+QString::number(id);
    QSqlQuery query(this->db);
    query.prepare(cmd);
    
    QVector<QVariant> ret;
    if(!query.exec()){
        qDebug() << "[error] fail to query by gid,  " << query.lastError().text();
        return ret;
    }
    
    while(query.next()){
        ret.append({query.value(0), query.value(1),query.value(2),query.value(3)});
    }

    return ret;
}

QVector<QVariant> BookmarkGroupDao::QueryByName(const QString& name){
    QString cmd = "SELECT * from " + this->getTableName() + " WHERE NAME="+name;
    QSqlQuery query(this->db);
    query.prepare(cmd);

    QVector<QVariant> ret;
    if(!query.exec()){
        qDebug() << "[error] fail to query by name,  " << query.lastError().text();
        return ret;
    }

    while(query.next()){
        ret.append({query.value(0), query.value(1),query.value(2),query.value(3)});
    }

    return ret;
}

bool BookmarkGroupDao::setName(const int& id, const QString& name){
    QString cmd = "UPDATE " + this->getTableName() + " SET NAME=:name WHERE GID=:id";
    QSqlQuery query;
    if(!query.prepare(cmd)){
        qDebug() << "[error] fail to prepare cmd : " << query.lastError().text();
        return false; 
    }
    query.bindValue(":name", name);
    query.bindValue(":id", id);

    if(!query.exec()){
        qDebug() << "[error] fail to exec cmd : " << query.lastError().text();
        return false; 
    }

    return true;
}

bool BookmarkGroupDao::setIcon(const int& id, const QString& icon){
    QString cmd = "UPDATE " + this->getTableName() + " SET ICON=:icon WHERE GID=:id";
    QSqlQuery query;
    if(!query.prepare(cmd)){
        qDebug() << "[error] fail to prepare cmd : " << query.lastError().text();
        return false; 
    }
    query.bindValue(":icon", icon);
    query.bindValue(":id", id);

    if(!query.exec()){
        qDebug() << "[error] fail to exec cmd : " << query.lastError().text();
        return false; 
    }

    return true;
}
