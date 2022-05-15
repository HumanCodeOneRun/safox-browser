#include "usermodel.h"
#include <iostream>
#include "QDebug"
#include "databasetaskscheduler.h"
using namespace  std;

bool t_getItemById(UserModel& um) {
    
    return 0;
}
bool t_addUsr(UserModel& um) {
    
    // um.addRegisterUser("usr2", "123");
    return 0
    || !um.addRegisterUser("usr1", "1")
    || !um.addRegisterUser("usr2", "12")
    || !um.addRegisterUser("usr3", "123");
}
bool t_deleteUsr(UserModel& um) {
    
    return 0
           || !um.deleteRegisterUser(2)
           || !um.deleteRegisterUser(3)
           ;
}
bool t_queryUsr(UserModel& um) {
    
    return 0
    || !um.queryUserId(1)
    || !um.queryUserName("usr1")
    || !um.queryUserPassword(1,"1");

}

bool t_editUsr(int id, UserModel& um) {
    
    return 0 || !um.editUser(id, "user100", "666");
}
int main() {
    auto scheduler = std::make_shared<DatabaseTaskScheduler>(2);
    scheduler->run();
    static UserModel model(scheduler);

    int ret = 0
            //|| !t_addUsr(model)
            || !t_deleteUsr(model)
            || !t_queryUsr(model)
            || !t_editUsr(1, model);
    
//    int ret = 0
//            || t_addUsr();
//    UserDao dao;
//    dao.showAll();
//    dao.deleteTable();
    return ret;
}