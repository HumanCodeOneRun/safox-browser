#include "bookmarkdao.h"

BookmarkDao::BookmarkDao(std::shared_ptr<DatabaseTaskScheduler> _scheduler,const QString& _table_name )
: BaseDao(_scheduler, _table_name){
   createTable();
}

bool BookmarkDao::createTable(){
    check_thread_connection();
    auto db = BaseDao::db_connection.localData()->get_db_connection();
    QString cmd = "CREATE TABLE IF NOT EXISTS " + this->getTableName() +
                " (UID INTEGER NOT NULL, ID INTEGER PRIMARY KEY AUTOINCREMENT, GID INTEGER, NAME TEXT, URL TEXT, ICON TEXT);";
    
    if(db.transaction()){
        QSqlQuery query(db);
        bool ok = query.exec(cmd);

        if(!db.commit()){
            qDebug() << "[error] fail to commit " << db.lastError().text();
            db.rollback();
            return false;
        }

        if(!ok){
            qDebug() << "[error] fail to create bookmark table " << query.lastError().text();
            return false;
        }
    }

    else{
        qDebug() <<"[error] fail to strt transaction " << db.lastError().text();
        return false;
    }
    return true;
}


QVector<QVariant> BookmarkDao::QueryByUidAndId(const int& uid, const int& id){
    check_thread_connection();
    auto db = BaseDao::db_connection.localData()->get_db_connection();
    QString cmd = "SELECT * from " + this->getTableName() + " WHERE ID="+QString::number(id)+ " AND UID="+QString::number(uid);
    
    QVector<QVariant> ret;

    if(db.transaction()){
        QSqlQuery query(db);
        query.prepare(cmd);
        if(!query.exec()){
            qDebug() << "[error] fail to query by id and uid,  " << query.lastError().text();
            return ret;
        }
        
        if(!db.commit()){
            qDebug() << "[error] fail to commit" << db.lastError().text();;
            db.rollback();
        }

        while(query.next()){
            ret.append({query.value(0), query.value(1),query.value(2),query.value(3),query.value(4), query.value(5)});
        }
    }
    else{
        qDebug() << "[error] fail to strt transaction " << db.lastError().text();;
    }

    return ret;
}

QVector<QVector<QVariant>> BookmarkDao::QueryByUidAndGroupId(const int& uid, const int& gid){
    check_thread_connection();
    auto db = BaseDao::db_connection.localData()->get_db_connection();
    QString cmd = "SELECT * from " + this->getTableName() + " WHERE GID="+QString::number(gid) + " AND UID="+QString::number(uid);
    QVector<QVector<QVariant>> ret;
    if(db.transaction()){
        QSqlQuery query(db);
        query.prepare(cmd);

        if(!query.exec()){
            qDebug() << "[error] fail to query by gid,  " << query.lastError().text();
            return ret;
        }
        
        if(!db.commit()){
            qDebug() << "[error] fail to commit" << db.lastError().text();;
            db.rollback();
        }

        while(query.next()){
            QVector<QVariant> temp = {query.value(0), query.value(1),query.value(2),query.value(3),query.value(4), query.value(5)};
            ret.emplace_back(temp);
        }
    }
    else{
        qDebug() << "[error] fail to strt transaction " << db.lastError().text();;
    }

    return ret;
}

QVector<QVector<QVariant>> BookmarkDao::QueryByUidAndName(const int& uid, const QString& name){
    check_thread_connection();
    auto db = BaseDao::db_connection.localData()->get_db_connection();
    QString cmd = "SELECT * from " + this->getTableName() + " WHERE NAME="+name + " AND UID="+QString::number(uid);
    QVector<QVector<QVariant>> ret;
    if(db.transaction()){
        QSqlQuery query(db);
        query.prepare(cmd);
        
        if(!query.exec()){
            qDebug() << "[error] fail to query by name,  " << query.lastError().text();
            return ret;
        }

        if(!db.commit()){
            qDebug() << "[error] fail to commit. " << db.lastError().text();;
            db.rollback();
        }
        while(query.next()){
            QVector<QVariant> temp = {query.value(0), query.value(1),query.value(2),query.value(3),query.value(4), query.value(5)};
            ret.emplace_back(temp);
        }
    }
    else{
        qDebug() << "[error] fail to strt transaction. " << db.lastError().text();;
    }

    return ret;
}

bool BookmarkDao::setName(const int& uid, const int& id, const QString& name){
    check_thread_connection();
    auto db = BaseDao::db_connection.localData()->get_db_connection();
    QString cmd = "UPDATE " + this->table_name + " SET NAME =:name WHERE ID =:id AND UID =:uid";

    if(db.transaction()){
        QSqlQuery query(db);
        
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

        if(!db.commit()){
            qDebug() << "[error] fail to commit" << db.lastError().text();;
            db.rollback();
            return false;
        }
    }
    else{
        qDebug() << "[error] fail to strt transaction. " << db.lastError().text();;
        return false;
    }

    return true;
}

bool BookmarkDao::setGid(const int& uid, const int& id, const int& gid){
    check_thread_connection();
    auto db = BaseDao::db_connection.localData()->get_db_connection();
    QString cmd = "UPDATE " + this->table_name + " SET GID=:gid WHERE ID=:id AND UID=:uid";
    if(db.transaction()){
        QSqlQuery query(db);
        
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

        if(!db.commit()){
            qDebug() << "[error] fail to commit " << db.lastError().text();;
            db.rollback();
            return false;
        }
    }

    else{
        qDebug() << "[error] fail to strt transaction " << db.lastError().text();;
        return false;
    }

    return true;
}

bool BookmarkDao::setIcon(const int& uid, const int& id, const QString& icon){
     check_thread_connection();
    auto db = BaseDao::db_connection.localData()->get_db_connection();
    QString cmd = "UPDATE " + this->table_name + " SET ICON=:icon WHERE ID=:id AND UID=:uid";
    if(db.transaction()){
        QSqlQuery query(db);
        
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

        if(!db.commit()){
            qDebug() << "[error] fail to commit " << db.lastError().text();;
            return false;
        }
    }

    else{
        qDebug() << "[error] fail to strt transaction " << db.lastError().text();;
        return false;
    }

    return true;
}

bool BookmarkDao::setUrl(const int& uid, const int& id, const QUrl& url){
    check_thread_connection();
    auto db = BaseDao::db_connection.localData()->get_db_connection();
    QString cmd = "UPDATE " + this->table_name + " SET URL=:url WHERE ID=:id AND UID=:uid";

    if(db.transaction()){
        QSqlQuery query(db);
        
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

        if(!db.commit()){
            qDebug() << "[error] fail to commit " << db.lastError().text();;
            return false;
        }
    }

    else{
        qDebug() << "[error] fail to strt transaction "<< db.lastError().text();;
        return false;
    }

    return true;
}


bool BookmarkDao::insert(const int& uid, const int& gid, const QString& name, const QUrl& url, const QUrl& icon){
    check_thread_connection();
    auto db = BaseDao::db_connection.localData()->get_db_connection();
    QString cmd = "INSERT INTO " + this->getTableName() + "(UID, GID, NAME, URL, ICON)"+" VALUES(:uid, :gid, :name, :url, :icon)";

    if(db.transaction()){
        QSqlQuery query(db);
        if(!query.prepare(cmd)){
            qDebug() << "[error] fail to prepare, " << query.lastError().text();
            return false;
        }

        //int id = qHash(url.toString());

        query.bindValue(":uid", uid);
        //query.bindValue(":id", id);
        query.bindValue(":gid", gid);
        query.bindValue(":name", name);
        query.bindValue(":url", url.toString());
        query.bindValue(":icon",icon.toString());
        
        if(!query.exec()){
            qDebug() << "[error] fail to insert,  " << query.lastError().text();
            return false;
        }

        if(!db.commit()){
            qDebug() << "[error] fail to commit " << db.lastError().text();;
            return false;
        }
    }

    else{
        qDebug() << "[error] fail to strt transaction "<< db.lastError().text();;
        return false;
    }
    return true;
}

bool BookmarkDao::remove(const int& uid, const int& id){
    check_thread_connection();
    auto db = BaseDao::db_connection.localData()->get_db_connection();
    QString cmd = "DELETE FROM " + this->table_name + " WHERE ID=:id AND UID=:uid";

    if(db.transaction()){
        QSqlQuery query(db);
        query.prepare(cmd);
        query.bindValue(":id", id);
        query.bindValue(":uid", uid);

        if(!query.exec()){
            qDebug() << "[error] fail to delete,  " << query.lastError().text();
            return false;
        }

        if(!db.commit()){
            qDebug() << "[error] fail to commit " << db.lastError().text();;
            return false;
        }
    }
    else{
        qDebug() << "[error] fail to strt transaction " << db.lastError().text();;
        return false;
    }

    return true;
}

/*
QVector<QVariant> BookmarkDao::getcolumns(){
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
*/
bool BookmarkDao::deleteTable(){
    check_thread_connection();
    QString cmd = "DROP TABLE " + this->table_name;
    
    QSqlQuery query(BaseDao::db_connection.localData()->get_db_connection());
    query.prepare(cmd);

    if(!query.exec()){
        qDebug() << "[error] fail to delete table,  " << query.lastError().text();
        return false;
    }

    return true;
}

QString BookmarkDao::get_connection(){
    return (BaseDao::db_connection.localData()->get_db_connection()).connectionName();
}

BookmarkDao::~BookmarkDao(){
}