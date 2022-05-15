#include "bookmarkmodel.h"
#include "databasetaskscheduler.h"

bool init_getgroup_test(BookmarkModel &model){

    auto groups = model.initGetGroups(1);
    groups = model.initGetGroups(2);

    return 0;
}

bool add_group_test(BookmarkModel &model){

    return 0
        ||  !model.addBookmarkGroup(1, "test112313", QUrl("test1.icon"))
        ||  !model.addBookmarkGroup(2, "test221313", QUrl("test2.icon"))
        ||  !model.addBookmarkGroup(1, "test123123", QUrl("test3.icon"));

}


bool delete_group_test(BookmarkModel &model){

    return 0
        ||  !model.deleteBookmarkGroup(1, 802222310);
        
}


int main(int argc, char** argv){
    auto scheduler = std::make_shared<DatabaseTaskScheduler>(2);
    scheduler->run();
    static BookmarkModel model(scheduler);
    return 0 
        || init_getgroup_test(model)
        || add_group_test(model);
}
