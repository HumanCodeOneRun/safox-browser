//
// Created by Howell Young on 2022/5/18.
//

#include "service.h"
#include "usermodel.h"
#include <iostream>
#include "QDebug"
#include "databasetaskscheduler.h"
#include "bookmarkmodel.h"
#include "history.h"

class app{
public:
    MyServiceLocator m_serviceLocator;
    std::shared_ptr<DatabaseTaskScheduler> m_databaseScheduler;
    std::shared_ptr<UserModel> m_user;
    app()
    {
        m_databaseScheduler = std::make_shared<DatabaseTaskScheduler>();
        registerService("DatabaseTaskScheduler",m_databaseScheduler);
        m_databaseScheduler->run();
        m_user = std::make_shared<UserModel>(m_databaseScheduler);
        registerService("UserModel",m_user);
        m_user->addRegisterUser("aaa","aaa");
    }
    void registerService(std::string keyType, std::shared_ptr<QObject> service) {
        if (!m_serviceLocator.addService(keyType, service))
            qWarning() << "Could not register " << QString::fromStdString(keyType) << " with service registry";
    }

};

class browser{
public:
    explicit browser(const MyServiceLocator &serviceLocator):
    m_serviceLocator(serviceLocator),
    m_databaseScheduler(serviceLocator.getServiceAs<DatabaseTaskScheduler>("DatabaseTaskScheduler")),
    m_user(serviceLocator.getServiceAs<UserModel>("UserModel"))
    {
    }
    const MyServiceLocator &m_serviceLocator;
    std::shared_ptr<UserModel> m_user;
    std::shared_ptr<DatabaseTaskScheduler> m_databaseScheduler;

};
bool isvalid(){
    app a;
    browser(a.m_serviceLocator);
    UserModel um(a.m_databaseScheduler);
    int ret = um.queryUserPassword(1,"aaa");
    UserDao dao(a.m_databaseScheduler);
    dao.showAll();
    dao.deleteTable();
    return ret;
}
int main() {
    return 0 || !isvalid();

}