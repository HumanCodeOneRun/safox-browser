#include "BookmarkDao.h"

BookmarkDao::BookmarkDao(const QString& _db_path, const QString& _table_name )
: BaseDao(_db_path){
    
}

bool BookmarkDao::createTable(){
    QString cmd = "CREATE TABLE IF NOT EXISTS " + this->getTableName() +
                " (ID INTEGER PRIMARY KEY, GROUPID INTEGER, NAME TEXT, URL TEXT, ICON TEXT)";

    QSqlQuery query(cmd);

    if(!query.exec()){
        qDebug() << "[error] fail to create bookmark table " << query.lastError().text();
        return false;
    }

    return true;
}

BookmarkDao::~BookmarkDao(){
    
}