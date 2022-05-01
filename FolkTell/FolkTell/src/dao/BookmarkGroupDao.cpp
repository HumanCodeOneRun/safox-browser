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
                " (UID INTEGER NOT NULL, GID INTEGER NOT NULL, NAME TEXT UNIQUE, ICON TEXT, PRIMARY KEY(UID, GID));";
    QSqlQuery query(this->db);
    bool ok = query.exec(cmd);

    if(!ok){
        qDebug() << "[error] fail to create bookmarkgroup table " << query.lastError().text();
        return false;
    }

    return true;
}

QVector<QVariant> BookmarkGroupDao::QueryByUidAndId(const int& uid, const int& id){
    QString cmd = "SELECT * from " + this->getTableName() + " WHERE GID="+QString::number(id)+" AND UID="+QString::number(uid);
    QSqlQuery query(this->db);
    query.prepare(cmd);
    
    QVector<QVariant> ret;
    if(!query.exec()){
        qDebug() << "[error] fail to query by uid and gid,  " << query.lastError().text();
        return ret;
    }
    
    while(query.next()){
        ret.append({query.value(0), query.value(1),query.value(2),query.value(3)});
    }

    return ret;
}

QVector<QVariant> BookmarkGroupDao::QueryByUidAndName(const int& uid, const QString& name){
    QString cmd = "SELECT * from " + this->getTableName() + " WHERE NAME= '"+name+"'" + " AND UID="+QString::number(uid);
    QSqlQuery query(this->db);
    QVector<QVariant> ret;

    if(!query.prepare(cmd)){
        qDebug() << "[error] fail to query by name,  table:" << this->getTableName() << query.lastError().text();
        return ret;
    }
    
    if(!query.exec()){
        qDebug() << "[error] fail to exec query by name,  " << query.lastError().text();
        return ret;
    }

    QSqlRecord rec = query.record();
    
    if(!rec.isEmpty()){
        ret.append({rec.value("UID"), rec.value("GID"),rec.value("NAME"),rec.value("ICON")});
    }

    return ret;
}

QVector<QVector<QVariant>> BookmarkGroupDao::QueryAll(const int& uid){
    QString cmd = "SELECT * FROM " + this->getTableName() + " WHERE UID="+QString::number(uid);
    QSqlQuery query(this->db);
    qDebug() << cmd;
    qDebug() << this->getDbPath();
    QVector<QVector<QVariant>> ret;
    if(!query.prepare(cmd)){
        qDebug() << "[error] fail to prepare cmd : " << query.lastError().text();
        return ret; 
    }

    if(!query.exec()){
        qDebug() << "[error] fail to exec cmd : " << query.lastError().text();
        return ret; 
    }

    while(query.next()){
        QVector<QVariant> temp = {query.value(0), query.value(1),query.value(2),query.value(3)};
        ret.emplace_back(temp);
    }

    return ret;
}

bool BookmarkGroupDao::insert(const int& uid, const QString& name, const QString& icon){
    QString cmd = "INSERT INTO " + this->getTableName() + "(UID, GID, NAME, ICON) VALUES(:uid,:gid,:name,:icon)";
    QSqlQuery query(this->db);
    if(!query.prepare(cmd)){
        qDebug() << "[error] fail to prepare cmd : " << query.lastError().text();
        return false; 
    }
    int id = qHash(name);
    query.bindValue(":uid", uid);
    query.bindValue(":gid", id);
    query.bindValue(":name", name);
    query.bindValue(":icon", icon);

    if(!query.exec()){
        qDebug() << "[error] fail to exec cmd : " << query.lastError().text();
        return false; 
    }

    return true;
}

bool BookmarkGroupDao::setName(const int&uid, const int& id, const QString& name){
    QString cmd = "UPDATE " + this->getTableName() + " SET NAME=:name AND GID=:changed WHERE GID=:id AND UID=:uid";
    QSqlQuery query(this->db);
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

bool BookmarkGroupDao::setIcon(const int& uid, const int& id, const QString& icon){
    QString cmd = "UPDATE " + this->getTableName() + " SET ICON=:icon WHERE GID=:id AND UID=:uid";
    QSqlQuery query(this->db);
    if(!query.prepare(cmd)){
        qDebug() << "[error] fail to prepare cmd : " << query.lastError().text();
        return false; 
    }
    query.bindValue(":uid", uid);
    query.bindValue(":icon", icon);
    query.bindValue(":id", id);

    if(!query.exec()){
        qDebug() << "[error] fail to exec cmd : " << query.lastError().text();
        return false; 
    }

    return true;
}

BookmarkGroupDao::~BookmarkGroupDao(){
    (this->db).close();
}