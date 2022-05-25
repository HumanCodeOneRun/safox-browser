#include "bookmarkmodel.h"
#include "databasetaskscheduler.h"

bool init_getgroup_test(BookmarkModel &model){

    auto groups = model.initGetGroups(1);
    groups = model.initGetGroups(2);

    return 0;
}

bool add_group_test(BookmarkModel &model){
    for(int i = 0; i < 10; i++){
        if(!model.addBookmarkGroup(i, "group_test_"+QString::number(i), QUrl("group_test_icon_"+QString::number(i))))
            return false;
    }

    return true;

}


bool delete_group_test(BookmarkModel &model){


    return true
            && model.deleteBookmarkGroup(0, 1)
            && model.deleteBookmarkGroup(2, 3);
        
}


int main(int argc, char** argv){
    auto scheduler = std::make_shared<DatabaseTaskScheduler>(2);
    scheduler->run();
    static BookmarkModel model(scheduler);
    return 0 
        || init_getgroup_test(model)
        || add_group_test(model);
}
