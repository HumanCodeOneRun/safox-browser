#include "basedao.h"
#define USERDAO_TABLE_NAME "User"
#define USER_CONN "user_conn"
class UserDao : public BaseDao{
public:
    explicit UserDao(const QString&_conn_name=USER_CONN, const QString& _db_path=DEFAULT_DB_PATH, const QString& _table_name = USERDAO_TABLE_NAME);
    
    static UserDao& getDao();
    bool createTable() override;

    // query
    QVector<QVariant> QueryById(const int& id);
    QVector<QVector<QVariant>> QueryByName(const QString& name);
    QVector<QVariant> QueryByIdPassword(const int& id, const QString& password);
    // update
    bool setName(const int& id, const QString& name);
    bool setPassword(const int& id, const QString& password);
    // insert
    bool insert(const QString& name, const QString& password);

    // delete
    bool remove(const int& id);
    // debug
    QVector<QVariant> getcolumns();
    void showAll();
    bool deleteTable();
    ~UserDao();
};
