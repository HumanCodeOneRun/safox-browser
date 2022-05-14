#include "historydao.h"

HistoryDao::HistoryDao(const int& _userid, const QString& _db_path, const QString& _table_name):
userid(_userid), BaseDao(_db_path, _table_name) {
    createTable();
}


bool HistoryDao::createTable() {
    QString cmd = "CREATE TABLE IF NOT EXISTS " + this->getTableName() + 
    " (userid integer unsigned, urlid integer unsigned, title text, url text, iconUrl text, timestamp bigint unsigned, primary key(userid, urlid, url) )";
    QSqlQuery query(this->db);

    if(!query.exec(cmd)){
        qDebug() << "[error] fail to create history table " << query.lastError().text();
        return false;
    }

    return true;
}

bool HistoryDao::insertHistoryEntry(const uint& urlid, const QString &title, const QUrl& url, const QUrl& iconUrl, const qint64& timestamp) {
    QString cmd = "insert or replace into " + this->getTableName() + " (userid, urlid, title, url, iconUrl, timestamp) values (:userid, :urlid, :title, :url, :iconUrl, :timestamp)";
    QSqlQuery query(this->db);
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
    return true;
}

bool HistoryDao::queryByUserid() {
    QString cmd = "select * from " + this->getTableName() + " where userid = " + QString::number(this->userid) ;
    QSqlQuery query(this->db);
    if(!query.exec(cmd)) {
        qDebug() << "[error] fail to select,  " << query.lastError().text();
        return false;
    }
    else {
        while(query.next()) {
            qDebug()<<query.value(0)<<" "<<query.value(1)<<" "<<query.value(2)<<" "<<query.value(3)<<" "<<query.value(4)<<" "<<query.value(5); 
        }
    }
    return true;
}

QList<qint64> HistoryDao::queryDayTimestamp() {
    QString cmd = "select timestamp from " + this->getTableName() + " where userid = " + QString::number(this->userid) + " and url = \"todayItem\" order by timestamp asc";
    QSqlQuery query(this->db);
    QList<qint64> ret;
    if(!query.exec(cmd)) {
        qDebug() << "[error] fail to select,  " << query.lastError().text();
        return ret;
    }
    else {
        while(query.next()) { 
            ret.append(query.value(0).toLongLong());
        }
    }
    return ret;
}

QList<HistoryEntry> HistoryDao::queryHistoryEntry() {
    QString cmd = "select urlid, title, url, iconUrl, timestamp  from " + this->getTableName() + " where userid = " + QString::number(this->userid) + " and url != \"todayItem\" order by timestamp asc" ;
    QSqlQuery query(this->db);
    QList<HistoryEntry> ret;
    if(!query.exec(cmd)) {
        qDebug() << "[error] fail to select,  " << query.lastError().text();
        return ret;
    }
    else {
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
    return ret;
}

bool HistoryDao::deleteByPriKey(const unsigned int& urlid, const QUrl& url) {
    QString cmd = "delete from " + this->getTableName() + " where userid = :userid and urlid = :urlid and url = :url";
    QSqlQuery query(this->db);
    query.prepare(cmd);
    query.bindValue(":userid", this->userid);
    query.bindValue(":urlid", urlid);
    query.bindValue(":url", url);
    if(!query.exec()) {
        qDebug() << "[error] fail to delete by prikey, " << query.lastError().text();
        return false;
    }
    return true;
}

bool HistoryDao::clearTable() {
    QString cmd = "delete from " + this->getTableName();
    QSqlQuery query(this->db);
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

