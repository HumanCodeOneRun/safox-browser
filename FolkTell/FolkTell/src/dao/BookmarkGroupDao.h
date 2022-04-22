#ifndef BOOKMARKGROUPDAO_H
#define BOOKMARKGROUPDAO_H
#include "BaseDao.h"

#define BOOKMARKGROUPDAO_TABLE_NAME "BookmarkGroup"

class BookmarkGroupDao : public BaseDao{
public:
    explicit BookmarkGroupDao(const QString& _db_path=DEFAULT_DB_PATH, const QString& _table_name = BOOKMARKGROUPDAO_TABLE_NAME);
    
    static BookmarkGroupDao& getDao();
    bool createTable() override;

    // query
    QVector<QVariant> QueryById(const int& gid);
    QVector<QVariant> QueryByName(const QString& name);

    // update
    bool setName(const int& id, const QString& name);
    bool setIcon(const int& id, const QString& icon);

    // insert
    bool insert(const int& gid, const QString& name, const QString& url, const QString& icon);
    
    // debug
    QVector<QVariant> getcolumns();
    bool deleteTable();
    ~BookmarkGroupDao();
};

#endif