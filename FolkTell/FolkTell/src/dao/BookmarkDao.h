#ifndef BOOKMARKDAO_H
#define BOOKMARKDAO_H
#include "BaseDao.h"

#define BOOKMARKDAO_TABLE_NAME "Bookmark"

class BookmarkDao : public BaseDao{
public:
    explicit BookmarkDao(const QString& _db_path=DEFAULT_DB_PATH, const QString& _table_name = BOOKMARKDAO_TABLE_NAME);
    
    bool createTable() override;

    ~BookmarkDao();
};


#endif