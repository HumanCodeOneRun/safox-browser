#ifndef BOOKMARKDAO_H
#define BOOKMARKDAO_H
#include "BaseDao.h"

#define BOOKMARKDAO_TABLE_NAME "Bookmark"

class BookmarkDao : public BaseDao{
public:
    explicit BookmarkDao(const QString& _db_path=DEFAULT_DB_PATH, const QString& _table_name = BOOKMARKDAO_TABLE_NAME);
    
    static BookmarkDao& getDao();
    bool createTable() override;

    // query
    QVector<QVariant> QueryById(const int& id);
    QVector<QVector<QVariant>> QueryByGroupId(const int& gid);
    QVector<QVector<QVariant>> QueryByName(const QString& name);


    // insert
    bool insert(const int& gid, const QString& name, const QString& url, const QString& icon);
    
    // debug
    QVector<QVariant> getcolumns();
    bool deleteTable();
    ~BookmarkDao();
};


#endif