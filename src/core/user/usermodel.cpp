#include "usermodel.h"
#include <future>

// User item

UserModel::UserItem::UserItem(std::shared_ptr<DatabaseTaskScheduler> scheduler)
        : id(-1), name("null"), password("123456"), samename({}) {
    this->dao = std::make_unique<UserDao>(scheduler);
}

void UserModel::UserItem::create_table(){
    this->dao->createTable();
}

QVector<QVariant> UserModel::UserItem::getItemById(const int &id) {
    QVector<QVariant> ret = (this->dao)->QueryById(id);
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
    QVector<QVector<QVariant>> ret = (this->dao)->QueryByName(name);
    if (ret.empty()) {
        qDebug() << "[error] fail to query user item by name";
        return ret;
    }
    this->samename = ret;
    return ret;
}

QVector<QVariant> UserModel::UserItem::getItemByIdPassword(const int &id, const QString &password) {
    QVector<QVariant> ret = (this->dao)->QueryByIdPassword(id, password);
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
    return (this->dao)->setName(id, name);
}

bool UserModel::UserItem::setPassword(const int &id, const QString &password) {
    this->password = password;
    return (this->dao)->setPassword(id, password);
}

bool UserModel::UserItem::addUser(const QString &name, const QString &password) {
    return (this->dao)->insert(name, password);
}

bool UserModel::UserItem::deleteUser(const int &id) {
    return (this->dao)->remove(id);
}

UserModel::UserItem::~UserItem() {
    (this->dao)->close();
}


// User model
UserModel::UserModel(std::shared_ptr<DatabaseTaskScheduler> scheduler) :
        m_taskScheduler(scheduler) {
        this->item = std::make_unique<UserItem>(scheduler);

        //create_table();
}

void UserModel::create_table(){
    m_taskScheduler->post([this](){
        this->item->create_table();
    });
}

#if defined(__clang__) || defined(__GNUC__)
bool UserModel::editUser(const int &id, const QString &name, const QString &password) {
    if (!name.isEmpty() && !password.isEmpty()) {

        auto futureName = m_taskScheduler->post([this, &id, &name](){
            return this->item->setName(id, name);
        });
        int name_flag = futureName.get();

        auto futurePwd = m_taskScheduler->post([this,&id, &password](){
            return this->item->setPassword(id, password);
        });
        int pwd_flag = futurePwd.get();

        if (pwd_flag && name_flag) {
            return true;
        } else {
            return false;
        }
    }
    qDebug() << "[error] fail to edit User name， name or password illegal ";
    return false;
}


bool UserModel::queryUserName(const QString &name) {
    if (!name.isEmpty()) {

        auto future = m_taskScheduler->post([this, &name]() {
            int has = this->item->getItemByName(name).isEmpty();
            int ret = has ? 1 : 0;
            return ret;
        });
        return future.get();
    }
    return false;
}

bool UserModel::queryUserId(const int &id) {

    auto future = m_taskScheduler->post([this, &id]() {
        int has = !this->item->getItemById(id).isEmpty();
        int ret = has ? 1 : 0;
        return ret;
    });
    return future.get();
}

bool UserModel::queryUserPassword(const int &id, const QString &password) {

    auto future = m_taskScheduler->post([this, &id, &password]() {
        int has = !this->item->getItemByIdPassword(id, password).isEmpty();
        int ret = has ? 1 : 0;
        return ret;
    });
    return future.get();

}

bool UserModel::addRegisterUser(const QString &name, const QString &password) {

    auto future = m_taskScheduler->post([this, &name, &password]() {
        return  this->item->addUser(name, password);
    });
    return future.get();
}

bool UserModel::deleteRegisterUser(const int &id) {
    return m_taskScheduler->post([this, &id](){
        return this->item->deleteUser(id);
    }).get();
}

#endif

#if defined(_MSC_VER)
bool UserModel::editUser(const int &id, const QString &name, const QString &password) {
    if (!name.isEmpty() && !password.isEmpty()) {
        std::promise<bool> pm1;
        auto future1 = pm1.get_future();
        m_taskScheduler->post([this, &pm1, &id, &name](){
            pm1.set_value(this->item->setName(id, name));
        });
        int name_flag = future1.get();

        std::promise<bool> pm2;
        auto future2 = pm1.get_future();
        m_taskScheduler->post([this, &pm2, &id, &password](){
            pm2.set_value(this->item->setPassword(id, password));
        });
        int pwd_flag = future2.get();

        if (pwd_flag && name_flag) {
            return true;
        } else {
            return false;
        }
    }
    qDebug() << "[error] fail to edit User name， name or password illegal ";
    return false;
}


bool UserModel::queryUserName(const QString &name) {
    if (!name.isEmpty()) {
        std::promise<bool> pm;
        auto future = pm.get_future();
       m_taskScheduler->post([this, &pm, &name]() {
            int has = this->item->getItemByName(name).isEmpty();
            int ret = has ? 1 : 0;
            pm.set_value(ret);
        });
        return future.get();
    }
    return false;
}

bool UserModel::queryUserId(const int &id) {
    std::promise<bool> pm;
    auto future = pm.get_future();
    m_taskScheduler->post([this, &pm, &id]() {
        int has = !this->item->getItemById(id).isEmpty();
        int temp = has ? 1 : 0;
        pm.set_value(temp);
        //return ret;
    });
    return future.get();
}

bool UserModel::queryUserPassword(const int &id, const QString &password) {
    std::promise<bool> pm;
    auto future = pm.get_future();
    m_taskScheduler->post([this,&pm, &id, &password]() {
        int has = !this->item->getItemByIdPassword(id, password).isEmpty();
        int ret = has ? 1 : 0;
        pm.set_value(ret);
    });
    return future.get();

}

bool UserModel::addRegisterUser(const QString &name, const QString &password) {
    std::promise<bool> pm;
    auto future = pm.get_future();
    m_taskScheduler->post([this,&pm, &name, &password]() {
        pm.set_value(this->item->addUser(name, password));
    });
    return future.get();
}

bool UserModel::deleteRegisterUser(const int &id) {
    std::promise<bool> pm;
    auto future = pm.get_future();
    m_taskScheduler->post([this,&pm, &id]() {
        pm.set_value(this->item->deleteUser(id));
    });
    return future.get();

}


#endif

UserModel::~UserModel() {

}