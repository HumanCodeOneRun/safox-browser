#include <QtWebEngineCore>
#include <QObject>
#include "dao/UserDao.h"

// TODO: 1. auto-increment for count in User group
//       2. consider return UserItem/UserItem for convinience

class UserModel : QObject{
    Q_OBJECT // for slots

public:
    UserModel();
    ~UserModel();
    class UserItem{
    public:
        UserItem();
        QVector<QVariant> getItemById(const int& id);
        QVector<QVector<QVariant>> getItemByName(const QString& name);
        QVector<QVariant> getItemByIdPassword(const int& id, const QString& password);
        inline int getId() { return this->id; }
        inline QString getName() { return this->name; }
        inline QString getPassword() { return this->password; }
        bool setName(const int& id, const QString& name);
        bool setPassword(const int& id, const QString& password);
        bool addUser(const QString& name, const QString& password);
        bool deleteUser(const int& id);

        ~UserItem();
    private:
        int id;
        QString name;
        QString password;
        QVector<QVector<QVariant>> samename;
        UserDao dao;
    };

   
public slots:

    bool addRegisterUser(const QString& name, const QString& password);
    bool deleteRegisterUser(const int& id);
    bool editUser(const int& id, const QString& name="",const QString& password="123456");
    bool queryUserName(const QString& name);
    bool queryUserId(const int& id);
    bool queryUserPassword(const int& id, const QString& password);
private:


};