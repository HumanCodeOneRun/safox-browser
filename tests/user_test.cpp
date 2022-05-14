#include "user/usermodel.h"
#include <iostream>
#include "QDebug"
#include "taskscheduler/databasetaskscheduler.h"
using namespace  std;
DatabaseTaskScheduler scheduler;
bool t_getItemById() {
    UserModel um(scheduler);
    return 0;
}
bool t_addUsr() {
    UserModel um(scheduler);
    // um.addRegisterUser("usr2", "123");
    return 0
    || !um.addRegisterUser("usr1", "1")
    || !um.addRegisterUser("usr2", "12")
    || !um.addRegisterUser("usr3", "123");
}
bool t_deleteUsr() {
    UserModel um(scheduler);
    // um.addRegisterUser("usr2", "123");
    return 0
           || !um.deleteRegisterUser(2)
           || !um.deleteRegisterUser(3)
           ;
}
bool t_queryUsr(int id) {
    UserModel um(scheduler);
    return 0
    || !um.queryUserId(1)
    || !um.queryUserName("usr1")
    || !um.queryUserPassword(1,"1");

}

bool t_editUsr(int id) {
    UserModel um(scheduler);
    return 0 || !um.editUser(id, "user100", "666");
}
int main() {
    scheduler.run();

    int ret = 0
            || !t_addUsr()
            || !t_deleteUsr()
            || !t_queryUsr(1)
            || !t_editUsr(1);
//    int ret = 0
//            || t_addUsr();
//    UserDao dao;
//    dao.showAll();
//    dao.deleteTable();
    return ret;
}