#include "historydao.h"

HistoryDao::HistoryDao(const int& _userid,std::shared_ptr<DatabaseTaskScheduler> _scheduler, const QString& _table_name):
userid(_userid), BaseDao(_scheduler, _table_name) {
    createTable();
}


bool HistoryDao::createTable() {
    check_thread_connection();
    QString cmd = "CREATE TABLE IF NOT EXISTS " + this->getTableName() + 
    " (userid integer unsigned, urlid integer unsigned, title text, url text, iconUrl text, timestamp bigint unsigned, primary key(userid, urlid, url) )";
    QSqlQuery query(this->db_connection.localData()->get_db_connection());

    if(!query.exec(cmd)){
        qDebug() << "[error] fail to create history table " << query.lastError().text();
        return false;
    }

    return true;
}

bool HistoryDao::insertHistoryEntry(const uint& urlid, const QString &title, const QUrl& url, const QUrl& iconUrl, const qint64& timestamp) {
    check_thread_connection();
    auto db = BaseDao::db_connection.localData()->get_db_connection();
    QString cmd = "insert or replace into " + this->getTableName() + " (userid, urlid, title, url, iconUrl, timestamp) values (:userid, :urlid, :title, :url, :iconUrl, :timestamp)";
    
    if(db.transaction()){
        QSqlQuery query(db);
        query.prepare(cmd);
        query.bindValue(":userid", this->userid);
        query.bindValue(":urlid", urlid);
        query.bindValue(":title", title);
        query.bindValue(":url", url);
        query.bindValue(":iconUrl", iconUrl);
        query.bindValue(":timestamp", timestamp);
        if(!query.exec()){
            qDebug() << "[error] fail to insert,  " << query.lastError().text();
            return false;
        }

        if(!db.commit()){
            qDebug() << "[error] fail to commit " << db.lastError().text();
            return false;
        }
    }

    else{
        qDebug() << "[error] fail to strt transaction " << db.lastError().text();
        return false;
    }
    return true;
}

bool HistoryDao::queryByUserid() {
    check_thread_connection();
    auto db = BaseDao::db_connection.localData()->get_db_connection();
    QString cmd = "select * from " + this->getTableName() + " where userid = " + QString::number(this->userid) ;

    if(db.transaction()){
        QSqlQuery query(db);
        if(!query.exec(cmd)) {
            qDebug() << "[error] fail to select,  " << query.lastError().text();
            return false;
        }

        if(!db.commit()){
            qDebug() << "[error] fail to commit " << db.lastError().text();
            return false;
        }
        
        while(query.next()) {
            qDebug()<<query.value(0)<<" "<<query.value(1)<<" "<<query.value(2)<<" "<<query.value(3)<<" "<<query.value(4)<<" "<<query.value(5); 
        }
    }
    return true;
}

QList<qint64> HistoryDao::queryDayTimestamp() {
    check_thread_connection();
    auto db = BaseDao::db_connection.localData()->get_db_connection();
    QString cmd = "select timestamp from " + this->getTableName() + " where userid = " + QString::number(this->userid) + " and url = \"todayItem\" order by timestamp asc";
    QList<qint64> ret;

    if(db.transaction()){
        QSqlQuery query(db);
        if(!query.exec(cmd)) {
            qDebug() << "[error] fail to select,  " << query.lastError().text();
            return ret;
        }

        if(!db.commit()){
            qDebug() << "[error] fail to commit " << db.lastError().text();
            return ret;
        }
        while(query.next()) { 
            ret.append(query.value(0).toLongLong());
        }
    }

    else{
        qDebug() << "[error] fail to strt transaction " << db.lastError().text();
        return ret;
    }
    return ret;
}

QList<HistoryEntry> HistoryDao::queryHistoryEntry() {
    check_thread_connection();
    auto db = BaseDao::db_connection.localData()->get_db_connection();
    QString cmd = "select urlid, title, url, iconUrl, timestamp  from " + this->getTableName() + " where userid = " + QString::number(this->userid) + " and url != \"todayItem\" order by timestamp asc" ;
    QList<HistoryEntry> ret;

    if(db.transaction()){
        QSqlQuery query(db);
        if(!query.exec(cmd)) {
            qDebug() << "[error] fail to select,  " << query.lastError().text();
            return ret;
        }

        if(!db.commit()){
            qDebug() << "[error] fail to commit " << db.lastError().text();
            return ret;
        }

        while(query.next()) {
            HistoryEntry historyEntry;
            historyEntry.urlid = query.value(0).toLongLong();
            historyEntry.title = query.value(1).toString();
            historyEntry.url = query.value(2).toUrl();
            historyEntry.iconUrl = query.value(3).toUrl();
            historyEntry.date = QDateTime::fromMSecsSinceEpoch(query.value(4).toLongLong()); 
            ret.append(historyEntry);
        }

    }

    else{
        qDebug() << "[error] fail to strt transaction " << db.lastError().text();
        return ret;
    }
    return ret;
}

bool HistoryDao::deleteByPriKey(const unsigned int& urlid, const QUrl& url) {
    check_thread_connection();
    auto db = BaseDao::db_connection.localData()->get_db_connection();
    QString cmd = "delete from " + this->getTableName() + " where userid = :userid and urlid = :urlid and url = :url";

    if(db.transaction()){
        QSqlQuery query(db);
        query.prepare(cmd);
        query.bindValue(":userid", this->userid);
        query.bindValue(":urlid", urlid);
        query.bindValue(":url", url);
        if(!query.exec()) {
            qDebug() << "[error] fail to delete by prikey, " << query.lastError().text();
            return false;
        }
        if(!db.commit()){
            qDebug() << "[error] fail to commit " << db.lastError().text();
            return false;
        } 
    }

    else{
        qDebug() << "[error] fail to strt transaction " << db.lastError().text();
        return false;
    }
    return true;
}

bool HistoryDao::clearTable() {
    check_thread_connection();
    QString cmd = "delete from " + this->getTableName();
    QSqlQuery query(this->db_connection.localData()->get_db_connection());
    if(!query.exec(cmd)) {
        qDebug() << "[error] fail to clear table, " << query.lastError().text();
        return false;
    }
    cmd = "vacuum";
    if(!query.exec(cmd)) {
        qDebug() << "[error] fail to clear table, " << query.lastError().text();
        return false;
    }
    return true;
}


void HistoryDao::setUserid(const int& _userid) {
    userid = _userid;
}

HistoryDao::~HistoryDao() {
    this->scheduler.~shared_ptr();
}