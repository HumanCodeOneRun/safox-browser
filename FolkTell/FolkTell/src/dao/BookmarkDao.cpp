#include "BookmarkDao.h"

BookmarkDao::BookmarkDao(const QString& _db_path, const QString& _table_name )
: BaseDao(_db_path, _table_name){
    createTable();

    qDebug() << this->db.tables() << this->getTableName();
}
BookmarkDao& BookmarkDao::getDao(){
    static BookmarkDao dao;
    return dao;
}
bool BookmarkDao::createTable(){
    QString cmd = "CREATE TABLE IF NOT EXISTS " + this->getTableName() +
                " (ID INTEGER PRIMARY KEY AUTOINCREMENT, GID INTEGER, NAME TEXT, URL TEXT, ICON TEXT);";
    QSqlQuery query(this->db);
    bool ok = query.exec(cmd);

    if(!ok){
        qDebug() << "[error] fail to create bookmark table " << query.lastError().text();
        return false;
    }

    return true;
}


QVector<QVariant> BookmarkDao::QueryById(const int& id){
    QString cmd = "SELECT * from " + this->getTableName() + " WHERE ID="+QString::number(id);
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

QVector<QVector<QVariant>> BookmarkDao::QueryByGroupId(const int& gid){
    QString cmd = "SELECT * from " + this->getTableName() + " WHERE GID="+QString::number(gid);
    QSqlQuery query(this->db);
    query.prepare(cmd);

    QVector<QVector<QVariant>> ret;
    if(!query.exec()){
        qDebug() << "[error] fail to query by gid,  " << query.lastError().text();
        return ret;
    }

    while(query.next()){
        QVector<QVariant> temp = {query.value(0), query.value(1),query.value(2),query.value(3),query.value(4)};
        ret.emplace_back(temp);
    }

    return ret;
}

QVector<QVector<QVariant>> BookmarkDao::QueryByName(const QString& name){
    QString cmd = "SELECT * from " + this->getTableName() + " WHERE NAME="+name;
    QSqlQuery query(this->db);
    query.prepare(cmd);

    QVector<QVector<QVariant>> ret;
    if(!query.exec()){
        qDebug() << "[error] fail to query by name,  " << query.lastError().text();
        return ret;
    }

    while(query.next()){
        QVector<QVariant> temp = {query.value(0), query.value(1),query.value(2),query.value(3),query.value(4)};
        ret.emplace_back(temp);
    }

    return ret;
}

bool BookmarkDao::insert(const int& gid, const QString& name, const QString& url, const QString& icon){
    QString cmd = "INSERT INTO " + this->getTableName() + "(GID, NAME, URL, ICON)"+" VALUES(:gid, :name, :url, :icon)";

    QSqlQuery query(this->db);
    query.prepare(cmd);
    query.bindValue(":gid", gid);
    query.bindValue(":name", name);
    query.bindValue(":url", url);
    query.bindValue(":icon", icon);
    
    if(!query.exec()){
        qDebug() << "[error] fail to insert,  " << query.lastError().text();
        return false;
    }

    return true;
}

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