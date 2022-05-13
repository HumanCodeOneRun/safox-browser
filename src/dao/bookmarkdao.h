#ifndef BOOKMARKDAO_H
#define BOOKMARKDAO_H
#include "basedao.h"

#define BOOKMARKDAO_TABLE_NAME "Bookmark"

class BookmarkDao : public BaseDao{
public:
    BookmarkDao(const QString& _db_path=DEFAULT_DB_PATH, const QString& _table_name = BOOKMARKDAO_TABLE_NAME);
    
    static BookmarkDao& getDao();
    bool createTable() override;

    // query
    QVector<QVariant> QueryByUidAndId(const int& uid, const int& id);
    QVector<QVector<QVariant>> QueryByUidAndGroupId(const int& uid, const int& gid);
    QVector<QVector<QVariant>> QueryByUidAndName(const int& uid, const QString& name);

    // update
    bool setName(const int& uid,const int& id, const QString& name);
    bool setGid(const int& uid,const int& id, const int& gid);
    bool setIcon(const int& uid,const int& id, const QString& icon);
    bool setUrl(const int& uid,const int& id, const QUrl& url);

    // insert
    // TODO automatically get icon
    bool insert(const int& uid, const int& gid, const QString& name, const QUrl& url, const QUrl& icon);
    
    // delete
    bool remove(const int& uid, const int& id);
    // debug
    //QVector<QVariant> getcolumns();
    bool deleteTable();
    ~BookmarkDao();
};


#endif