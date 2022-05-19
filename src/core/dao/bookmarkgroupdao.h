#ifndef BOOKMARKGROUPDAO_H
#define BOOKMARKGROUPDAO_H
#include "basedao.h"
#include <QDateTime>
#define BOOKMARKGROUPDAO_TABLE_NAME "BookmarkGroup"

class BookmarkGroupDao : public BaseDao{
public:
    explicit BookmarkGroupDao(std::shared_ptr<DatabaseTaskScheduler> _scheduler, const QString& _table_name = BOOKMARKGROUPDAO_TABLE_NAME);

    bool createTable() override;

    // query
    QVector<QVariant> QueryByUidAndId(const int& uid, const int& gid);
    QVector<QVariant> QueryByUidAndName(const int &uid, const QString& name);
    QVector<QVector<QVariant>> QueryAll(const int& uid);

    // update
    bool setName(const int& uid, const int& id, const QString& name);
    bool setIcon(const int& uid, const int& id, const QString& icon);

    // insert
    bool insert(const int& uid, const QString& name, const QString& icon);
    
    // delete
    bool remove(const int& uid, const int& gid);

    // debug
    void print_db_state(){ if(this->db_connection.localData()->get_db_connection().isOpen())  qDebug()<< "db is open"; else qDebug() << "db is closed";}
    bool deleteTable();

    QString get_connection();
    ~BookmarkGroupDao();
};

#endif