#include "bookmarkgroupdao.h"

BookmarkGroupDao::BookmarkGroupDao(std::shared_ptr<DatabaseTaskScheduler> _scheduler, const QString& _table_name )
: BaseDao(_scheduler, _table_name){
    //createTable();
}

bool BookmarkGroupDao::createTable(){
    check_thread_connection();
    QString cmd = "CREATE TABLE IF NOT EXISTS " + this->getTableName() +
                " (UID INTEGER NOT NULL, GID INTEGER PRIMARY KEY AUTOINCREMENT, NAME TEXT, ICON TEXT);";
    QSqlQuery query(BaseDao::db_connection.localData()->get_db_connection());
    bool ok = query.exec(cmd);

    if(!ok){
        qDebug() << "[error] fail to create bookmarkgroup table " << query.lastError().text();
        return false;
    }

    return true;
}

QVector<QVariant> BookmarkGroupDao::QueryByUidAndId(const int& uid, const int& id){
    check_thread_connection();
    QString cmd = "SELECT * from " + this->getTableName() + " WHERE GID="+QString::number(id)+" AND UID="+QString::number(uid);
    QSqlQuery query(BaseDao::db_connection.localData()->get_db_connection());
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
    check_thread_connection();
    QString cmd = "SELECT * from " + this->getTableName() + " WHERE NAME= '"+name+"'" + " AND UID="+QString::number(uid);
    QSqlQuery query(BaseDao::db_connection.localData()->get_db_connection());
    QVector<QVariant> ret;
    
    qDebug() << "[info] query group: current thread is " << QThread::currentThreadId();
    if(!query.prepare(cmd)){
        qDebug() << "[error] fail to query by name,  table:" << this->getTableName() << query.lastError().text();
        return ret;
    }
    
    if(!query.exec()){
        qDebug() << "[error] fail to exec query by name,  " << query.lastError().text();
        return ret;
    }

    while(query.next()){
        ret.append({query.value(0), query.value(1),query.value(2),query.value(3)});
    }

    return ret;
}

QVector<QVector<QVariant>> BookmarkGroupDao::QueryAll(const int& uid){
    check_thread_connection();
    QString cmd = "SELECT * FROM " + this->getTableName() + " WHERE UID="+QString::number(uid);
    QSqlQuery query(BaseDao::db_connection.localData()->get_db_connection());
    
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
    check_thread_connection();
    QString cmd = "INSERT INTO " + this->getTableName() + "(UID, NAME, ICON) VALUES(:uid, :name,:icon)";
    QSqlQuery query(BaseDao::db_connection.localData()->get_db_connection());
    if(!query.prepare(cmd)){
        qDebug() << "[error] fail to prepare cmd : " << query.lastError().text();
        return false; 
    }
    //int id = qHash(name);
    query.bindValue(":uid", uid);
    //query.bindValue(":gid", id);
    query.bindValue(":name", name);
    query.bindValue(":icon", icon);

    if(!query.exec()){
        qDebug() << "[error] fail to exec cmd : " << query.lastError().text();
        return false; 
    }

    return true;
}

bool BookmarkGroupDao::setName(const int&uid, const int& id, const QString& name){
    check_thread_connection();
    QString cmd = "UPDATE " + this->getTableName() + " SET NAME=:name AND GID=:changed WHERE GID=:id AND UID=:uid";
    QSqlQuery query(BaseDao::db_connection.localData()->get_db_connection());
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
    check_thread_connection();
    QString cmd = "UPDATE " + this->getTableName() + " SET ICON=:icon WHERE GID=:id AND UID=:uid";
    QSqlQuery query(BaseDao::db_connection.localData()->get_db_connection());
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

 bool BookmarkGroupDao::remove(const int& uid, const int& gid){
    check_thread_connection();
    QString cmd = "DELETE FROM " + this->getTableName() + " WHERE UID=:uid AND GID=:gid";
    QSqlQuery query(BaseDao::db_connection.localData()->get_db_connection());
     if(!query.prepare(cmd)){
        qDebug() << "[error] fail to prepare cmd : " << query.lastError().text();
        return false; 
    }
    query.bindValue(":uid", uid);
    query.bindValue(":gid", gid);

    if(!query.exec()){
        qDebug() << "[error] fail to exec cmd : " << query.lastError().text();
        return false; 
    }

    return true;
 }

QString BookmarkGroupDao::get_connection(){
    return (BaseDao::db_connection.localData()->get_db_connection()).connectionName();
}

BookmarkGroupDao::~BookmarkGroupDao(){
}