#include "usermodel.h"
#include <iostream>
#include "QDebug"
#include "databasetaskscheduler.h"
using namespace  std;


bool t_addUsr(UserModel& um) {
    
    // um.addRegisterUser("usr2", "123");
    return 1
    &&um.addRegisterUser("usr1", "1")
    &&um.addRegisterUser("usr2", "12")
    &&um.addRegisterUser("usr3", "123");
}
bool t_deleteUsr(UserModel& um) {
    
    return 1
           &&um.deleteRegisterUser("usr2")
           &&um.deleteRegisterUser("usr3")
           ;
}
bool t_queryUsr(UserModel& um) {
    
    return 1
    &&um.queryUserId(1)
    &&um.queryUserName("usr1")
    &&um.queryUserPassword("usr1","1")
    &&(um.getUserIdByName("usr1") == 1);

}

bool t_editUsr(int id, UserModel& um) {
    
    return 1 &&  um.editUser(id, "user100", "666");
}

int main() {
    auto scheduler = std::make_shared<DatabaseTaskScheduler>(2);
    scheduler->run();
    UserModel model(scheduler);

    int ret = 1
              && t_addUsr(model)
              && t_deleteUsr(model)
              && t_queryUsr(model)
              && t_editUsr(1, model)
            ;
    scheduler->stop();

    return !ret;
}