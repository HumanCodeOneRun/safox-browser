#ifndef USER_H_
#define USER_H_

#include <QtWebEngineCore>
#include "../dao/userdao.h"
#include "../taskscheduler/databasetaskscheduler.h"

class UserModel : public QObject {

public:
    explicit UserModel(std::shared_ptr<DatabaseTaskScheduler> scheduler);

    ~UserModel();

    class UserItem {
    public:
        UserItem(std::shared_ptr<DatabaseTaskScheduler> scheduler);

        QVector<QVariant> getItemById(const int &id);

        QVector<QVector<QVariant>> getItemByName(const QString &name);

        QVector<QVariant> getItemByIdPassword(const int &id, const QString &password);

        inline int getId() { return this->id; }

        inline QString getName() { return this->name; }

        inline QString getPassword() { return this->password; }

        bool setName(const int &id, const QString &name);

        bool setPassword(const int &id, const QString &password);

        bool addUser(const QString &name, const QString &password);

        bool deleteUser(const int &id);

        void create_table();

        ~UserItem();

    private:
        int id;
        QString name;
        QString password;
        QVector<QVector<QVariant>> samename;
        std::unique_ptr<UserDao> dao;
    };


public :

    bool addRegisterUser(const QString &name, const QString &password);

    bool deleteRegisterUser(const int &id);

    bool editUser(const int &id, const QString &name = "", const QString &password = "123456");

    bool queryUserName(const QString &name);

    bool queryUserId(const int &id);

    bool queryUserPassword(const int &id, const QString &password);

private:
    std::shared_ptr<DatabaseTaskScheduler> m_taskScheduler;

    std::unique_ptr<UserItem> item;

    void create_table();
};

#endif
