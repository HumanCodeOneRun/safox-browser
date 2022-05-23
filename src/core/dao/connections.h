#ifndef CONNECTIONS_H
#define CONNECTIONS_H
#include <QSqlDatabase>
#include <QString>
#include <fstream>
#include <mutex>

#define DEFAULT_DB_PATH "./.safox.db"
class DbConnection{

public:
    static int conn_count;
    QSqlDatabase get_db_connection();
    DbConnection(const QString& _db_path = DEFAULT_DB_PATH);
    ~DbConnection();

private:
    QString conn_name;
    QString db_path;
    
    bool checkdbpath(const QString& _db_path);

    mutable std::mutex m_mutex{};
};

#endif