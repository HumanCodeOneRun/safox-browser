#include "basedao.h"
#define USERDAO_TABLE_NAME "User"

class UserDao : public BaseDao{
public:
    explicit UserDao(std::shared_ptr<DatabaseTaskScheduler> _scheduler,const QString& _table_name = USERDAO_TABLE_NAME);
    
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
