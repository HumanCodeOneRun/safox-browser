#include "bookmarkdao.h"

BookmarkDao::BookmarkDao(const QString& _db_path, const QString& _table_name )
: BaseDao(_db_path, _table_name){
    createTable();

}
BookmarkDao& BookmarkDao::getDao(){
    static BookmarkDao dao;
    return dao;
}
bool BookmarkDao::createTable(){
    QString cmd = "CREATE TABLE IF NOT EXISTS " + this->getTableName() +
                " (UID INTEGER NOT NULL, ID INTEGER NOT NULL, GID INTEGER, NAME TEXT UNIQUE, URL TEXT, ICON TEXT, PRIMARY KEY(UID, ID));";
    QSqlQuery query(this->db);
    bool ok = query.exec(cmd);

    if(!ok){
        qDebug() << "[error] fail to create bookmark table " << query.lastError().text();
        return false;
    }

    return true;
}


QVector<QVariant> BookmarkDao::QueryByUidAndId(const int& uid, const int& id){
    QString cmd = "SELECT * from " + this->getTableName() + " WHERE ID="+QString::number(id)+ " AND UID="+QString::number(uid);
    QSqlQuery query(this->db);
    query.prepare(cmd);
    
    QVector<QVariant> ret;
    if(!query.exec()){
        qDebug() << "[error] fail to query by id and uid,  " << query.lastError().text();
        return ret;
    }
    
    while(query.next()){
        ret.append({query.value(0), query.value(1),query.value(2),query.value(3),query.value(4), query.value(5)});
    }

    return ret;
}

QVector<QVector<QVariant>> BookmarkDao::QueryByUidAndGroupId(const int& uid, const int& gid){
    QString cmd = "SELECT * from " + this->getTableName() + " WHERE GID="+QString::number(gid) + " AND UID="+QString::number(uid);
    QSqlQuery query(this->db);
    query.prepare(cmd);

    QVector<QVector<QVariant>> ret;
    if(!query.exec()){
        qDebug() << "[error] fail to query by gid,  " << query.lastError().text();
        return ret;
    }

    while(query.next()){
        QVector<QVariant> temp = {query.value(0), query.value(1),query.value(2),query.value(3),query.value(4), query.value(5)};
        ret.emplace_back(temp);
    }

    return ret;
}

QVector<QVector<QVariant>> BookmarkDao::QueryByUidAndName(const int& uid, const QString& name){
    QString cmd = "SELECT * from " + this->getTableName() + " WHERE NAME="+name + " AND UID="+QString::number(uid);
    QSqlQuery query(this->db);
    query.prepare(cmd);
    qDebug() << this->getcolumns();
    QVector<QVector<QVariant>> ret;
    if(!query.exec()){
        qDebug() << "[error] fail to query by name,  " << query.lastError().text();
        return ret;
    }

    while(query.next()){
        QVector<QVariant> temp = {query.value(0), query.value(1),query.value(2),query.value(3),query.value(4), query.value(5)};
        ret.emplace_back(temp);
    }

    return ret;
}

bool BookmarkDao::setName(const int& uid, const int& id, const QString& name){
    QString cmd = "UPDATE " + this->table_name + " SET NAME =:name WHERE ID =:id AND UID =:uid";
    QSqlQuery query(this->db);
    
    if(!query.prepare(cmd)){
        qDebug() << "[error] fail to prepare cmd in setname: " << query.lastError().text();
        return false;
    }

    query.bindValue(":name", name);
    query.bindValue(":id", id);
    query.bindValue(":uid", uid);

    if(!query.exec()){
        qDebug() << "[error] fail to exec cmd in setname: " << query.lastError().text();
        return false;
    }

    return true;
}

bool BookmarkDao::setGid(const int& uid, const int& id, const int& gid){
    QString cmd = "UPDATE " + this->table_name + " SET GID=:gid WHERE ID=:id AND UID=:uid";
    QSqlQuery query(this->db);
    
    if(!query.prepare(cmd)){
        qDebug() << "[error] fail to prepare cmd in setgid: " << query.lastError().text();
        return false;
    }

    query.bindValue(":gid", gid);
    query.bindValue(":id", id);
    query.bindValue(":uid", uid);

    if(!query.exec()){
        qDebug() << "[error] fail to exec cmd in setgid: " << query.lastError().text();
        return false;
    }

    return true;
}

bool BookmarkDao::setIcon(const int& uid, const int& id, const QString& icon){
    QString cmd = "UPDATE " + this->table_name + " SET ICON=:icon WHERE ID=:id AND UID=:uid";
    QSqlQuery query(this->db);
    
    if(!query.prepare(cmd)){
        qDebug() << "[error] fail to prepare cmd in seticon: " << query.lastError().text();
        return false;
    }

    query.bindValue(":icon", icon);
    query.bindValue(":id", id);
    query.bindValue(":uid", uid);

    if(!query.exec()){
        qDebug() << "[error] fail to exec cmd in seticon: " << query.lastError().text();
        return false;
    }

    return true;
}

bool BookmarkDao::setUrl(const int& uid, const int& id, const QUrl& url){
    QString cmd = "UPDATE " + this->table_name + " SET URL=:url WHERE ID=:id AND UID=:uid";
    QSqlQuery query(this->db);
    
    if(!query.prepare(cmd)){
        qDebug() << "[error] fail to prepare cmd in seturl: " << query.lastError().text();
        return false;
    }

    query.bindValue(":url", url);
    query.bindValue(":id", id);
    query.bindValue(":uid", uid);

    if(!query.exec()){
        qDebug() << "[error] fail to exec cmd in seturl: " << query.lastError().text();
        return false;
    }

    return true;
}


bool BookmarkDao::insert(const int& uid, const int& gid, const QString& name, const QUrl& url, const QUrl& icon){
    QString cmd = "INSERT INTO " + this->getTableName() + "(UID, ID, GID, NAME, URL, ICON)"+" VALUES(:uid, :id, :gid, :name, :url, :icon)";

    QSqlQuery query(this->db);
    query.prepare(cmd);

    int id = qHash(url.toString());

    query.bindValue(":uid", uid);
    query.bindValue(":id", id);
    query.bindValue(":gid", gid);
    query.bindValue(":name", name);
    query.bindValue(":url", url.toString());
    query.bindValue(":icon",icon.toString());
    
    if(!query.exec()){
        qDebug() << "[error] fail to insert,  " << query.lastError().text();
        return false;
    }

    return true;
}

bool BookmarkDao::remove(const int& uid, const int& id){
    QString cmd = "DELETE FROM " + this->table_name + " WHERE ID=:id AND UID=:uid";

    QSqlQuery query(this->db);
    query.prepare(cmd);
    query.bindValue(":id", id);
    query.bindValue(":uid", uid);

    if(!query.exec()){
        qDebug() << "[error] fail to delete,  " << query.lastError().text();
        return false;
    }

    return true;
}

/*
QVector<QVariant> BookmarkDao::getcolumns(){
    QString cmd = "PRAGMA  table_info("+this->table_name+")";
    QSqlQuery query(this->db);
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
*/
bool BookmarkDao::deleteTable(){
    QString cmd = "DROP TABLE " + this->table_name;
    
    QSqlQuery query(this->db);
    query.prepare(cmd);

    if(!query.exec()){
        qDebug() << "[error] fail to delete table,  " << query.lastError().text();
        return false;
    }

    return true;
}



BookmarkDao::~BookmarkDao(){
}