#include "usermodel.h"
#include <future>

// User item

UserModel::UserItem::UserItem()
        : id(-1), name("null"), password("123456"), samename({}) {
    this->dao = UserDao::getDao();
}

QVector<QVariant> UserModel::UserItem::getItemById(const int &id) {
    QVector<QVariant> ret = (this->dao).QueryById(id);
    if (ret.empty()) {
        qDebug() << "[error] fail to query user item by id";
        return ret;
    }
    this->id = ret.value(0).toInt();
    this->name = ret.value(1).toString();
    this->password = ret.value(2).toString();
    return ret;

}

QVector<QVector<QVariant>> UserModel::UserItem::getItemByName(const QString &name) {
    QVector<QVector<QVariant>> ret = (this->dao).QueryByName(name);
    if (ret.empty()) {
        qDebug() << "[error] fail to query user item by name";
        return ret;
    }
    this->samename = ret;
    return ret;
}

QVector<QVariant> UserModel::UserItem::getItemByIdPassword(const int &id, const QString &password) {
    QVector<QVariant> ret = (this->dao).QueryByIdPassword(id, password);
    if (ret.empty()) {
        qDebug() << "[error] fail to query user item by id";
        return ret;
    }
    this->id = ret.value(0).toInt();
    this->name = ret.value(1).toString();
    this->password = ret.value(2).toString();
    return ret;

}

bool UserModel::UserItem::setName(const int &id, const QString &name) {
    this->name = name;
    return (this->dao).setName(id, name);
}

bool UserModel::UserItem::setPassword(const int &id, const QString &password) {
    this->password = password;
    return (this->dao).setPassword(id, password);
}

bool UserModel::UserItem::addUser(const QString &name, const QString &password) {
    return (this->dao).insert(name, password);
}

bool UserModel::UserItem::deleteUser(const int &id) {
    return (this->dao).remove(id);
}

UserModel::UserItem::~UserItem() {
    (this->dao).close();
}


// User model
UserModel::UserModel(DatabaseTaskScheduler &taskScheduler) :
        m_taskScheduler(taskScheduler) {
}


bool UserModel::editUser(const int &id, const QString &name, const QString &password) {
    UserItem item;
    if (!name.isEmpty() && !password.isEmpty()) {
//        if (!item.setName(id, name)) {
//            qDebug() << "[error] fail to edit User name ";
//            return false;
//        } else {
//            if (!item.setPassword(id, password)) {
//                qDebug() << "[error] fail to edit User password ";
//                return false;
//            }
//            return true;
//        }

        std::promise<bool> pmName;
        std::future<bool> futureName = pmName.get_future();
        m_taskScheduler.post([&pmName,&item, &id, &name](){
            int ret = item.setName(id, name);
            pmName.set_value(ret);
        });
        int name_flag = futureName.get();

        std::promise<bool> pmPwd;
        std::future<bool> futurePwd = pmPwd.get_future();
        m_taskScheduler.post([&pmPwd,&item, &id, &password](){
            int ret = item.setPassword(id, password);
            pmPwd.set_value(ret);
        });
        int pwd_flag = futurePwd.get();

        if (pwd_flag && name_flag) {
            return true;
        }else {
            return false;
        }
    }
    qDebug() << "[error] fail to edit User name， name or password illegal ";
    return false;
}


UserModel::~UserModel() {

}

bool UserModel::queryUserName(const QString &name) {
    if (!name.isEmpty()) {
        UserItem item;
        std::promise<bool> pm;
        std::future<bool> future = pm.get_future();
        m_taskScheduler.post([&pm, &item, &name]() {
            int has = !item.getItemByName(name).isEmpty();
            int ret = has ? 1 : 0;
            pm.set_value(ret);
        });
        return future.get();
    }
    return false;
}

bool UserModel::queryUserId(const int &id) {

    UserItem item;
    std::promise<bool> pm;
    std::future<bool> future = pm.get_future();
    m_taskScheduler.post([&pm, &item, &id]() {
        int has = !item.getItemById(id).isEmpty();
        int ret = has ? 1 : 0;
        pm.set_value(ret);
    });
    return future.get();
}

bool UserModel::queryUserPassword(const int &id, const QString &password) {
    UserItem item;
    std::promise<bool> pm;
    std::future<bool> future = pm.get_future();
    m_taskScheduler.post([&pm, &item, &id, &password]() {
        int has = !item.getItemByIdPassword(id, password).isEmpty();
        int ret = has ? 1 : 0;
        pm.set_value(ret);
    });
    return future.get();

}

bool UserModel::addRegisterUser(const QString &name, const QString &password) {
    UserItem item;
    std::promise<bool> pm;
    std::future<bool> future = pm.get_future();
    m_taskScheduler.post([&pm, &name, &password, &item]() {
        int ret = item.addUser(name, password);
        pm.set_value(ret);
    });
    return future.get();
}

bool UserModel::deleteRegisterUser(const int &id) {
    UserItem item;
    return item.deleteUser(id);
}


