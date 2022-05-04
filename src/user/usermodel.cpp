#include "usermodel.h"


// User item

UserModel::UserItem::UserItem()
:id(-1), name("null"), password("123456"), samename({})
{
    this->dao = UserDao::getDao();
}

QVector<QVariant> UserModel::UserItem::getItemById(const int& id){
    QVector<QVariant> ret = (this->dao).QueryById(id);
    if(ret.empty()){
        qDebug() << "[error] fail to query user item by id";
        return ret;
    }
    this->id = ret.value(0).toInt();
    this->name = ret.value(1).toString();
    this->password = ret.value(2).toString();
    return ret;

}

QVector<QVector<QVariant>> UserModel::UserItem::getItemByName(const QString& name){
    QVector<QVector<QVariant>> ret = (this->dao).QueryByName(name);
    if(ret.empty()){
        qDebug() << "[error] fail to query user item by name";
        return ret;
    }
    this->samename = ret;
    return ret;
}

QVector<QVariant> UserModel::UserItem::getItemByIdPassword(const int& id, const QString& password){
    QVector<QVariant> ret = (this->dao).QueryByIdPassword(id, password);
    if(ret.empty()){
        qDebug() << "[error] fail to query user item by id";
        return ret;
    }
    this->id = ret.value(0).toInt();
    this->name = ret.value(1).toString();
    this->password = ret.value(2).toString();
    return ret;

}

bool UserModel::UserItem::setName(const int& id, const QString& name){
    this->name = name;
    return (this->dao).setName(id, name);
}

bool UserModel::UserItem::setPassword(const int& id, const QString& password){
    this->password = password;
    return (this->dao).setPassword(id, password);
}

bool UserModel::UserItem::addUser(const QString& name, const QString& password){
    return (this->dao).insert(name, password);
}

bool UserModel::UserItem::deleteUser(const int& id){
    return (this->dao).remove(id);
}

UserModel::UserItem::~UserItem(){
    (this->dao).close();
}


// User model
UserModel::UserModel(){

}


bool UserModel::editUser(const int& id, const QString& name, const QString& password){
    UserItem item;
    if(!name.isEmpty()&& !password.isEmpty()){
        if(!item.setName(id, name)){
            qDebug() << "[error] fail to edit User name ";
            return false;
        }else {
            if(!item.setPassword(id, password)) {
                qDebug() << "[error] fail to edit User password ";
                return false;
            }
            return true;
        }
    }
    qDebug() << "[error] fail to edit User name， name or password illegal ";
    return false;
}



UserModel::~UserModel(){
    
}

bool UserModel::queryUserName(const QString& name){
    UserItem item;
    if(!name.isEmpty()){
        if(item.getItemByName(name).isEmpty()){
            qDebug() << "[error] fail to query User name ";
            return false;
        }else {
            return true;
        }
    }
    return false;
}

bool UserModel::queryUserId(const int& id){
    UserItem item;
    if (!item.getItemById(id).isEmpty()){
        return true;
    }else {
        qDebug() << "[error] fail to query User id";
        return false;
    }
   
}

bool UserModel::queryUserPassword(const int& id, const QString& password){
    UserItem item;
    if(!item.getItemByIdPassword(id, password).isEmpty()) {
        return true;
    }else {
        qDebug() << "[error] fail to query User id and password";
        return false;
    }

}

bool UserModel::addRegisterUser(const QString& name, const QString& password){
    UserItem item;
    return item.addUser(name, password);
}

bool UserModel::deleteRegisterUser(const int& id){
    UserItem item;
    return item.deleteUser(id);
}