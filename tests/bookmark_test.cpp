#include "bookmarkmodel.h"
#include "databasetaskscheduler.h"
#include <ctime>


bool add_bookmark_test(BookmarkModel &model) {
    for(int i = 0; i < 10; i++){
        if(!model.addBookmark(i, "bookmarktest"+QString::number(i), QUrl("bookmarktest"+QString::number(i)), "bookmarktest"+QString::number(i), QUrl("bookmarktest"+QString::number(i))))
            return false;
    } 

    return true;
           
}

bool get_bookmark_bygid_test(BookmarkModel &model) {
    for(int i = 0; i < 10; i++){
        auto item_list = model.getItemsByGid(i, i);
        auto item = item_list.value(0);
        QString item_name = item.value(3).toString();

        if(item_name != "bookmarktest"+QString::number(i))
            return false;
    }

    return true;
}

bool edit_bokmark_test(BookmarkModel &model) {


    return true
           && model.editBookmark(0, 0, "BookmarkChanged1", QUrl("changedQurl1"), "bookmarktest3")
           && model.editBookmark(3, 3, "BookmarkChanged2", QUrl("changedQurl2"), "bookmarktest0");

}

bool delete_bookmark_test(BookmarkModel &model) {

    return true
           && model.deleteBookmark(4, 4)
           && model.deleteBookmark(8, 8);
}


int main(int argc, char **argv) {
    auto scheduler = std::make_shared<DatabaseTaskScheduler>(2);
    scheduler->run();
    static BookmarkModel model(scheduler);

    bool ok = add_bookmark_test(model)
            && get_bookmark_bygid_test(model)
            && edit_bokmark_test(model)
            && delete_bookmark_test(model);
    
    scheduler->stop();

    return !ok;
}