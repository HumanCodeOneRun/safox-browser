#ifndef BOOKMARKGROUPDAO_H
#define BOOKMARKGROUPDAO_H
#include "basedao.h"
#include <QDateTime>
#define BOOKMARKGROUPDAO_TABLE_NAME "BookmarkGroup"

class BookmarkGroupDao : public BaseDao{
public:
    BookmarkGroupDao(const QString& _db_path=DEFAULT_DB_PATH, const QString& _table_name = BOOKMARKGROUPDAO_TABLE_NAME);
    
    static BookmarkGroupDao& getDao();
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

    bool deleteTable();
    ~BookmarkGroupDao();
};

#endif