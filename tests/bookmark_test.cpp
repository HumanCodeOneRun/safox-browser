#include "bookmark/bookmarkmodel.h"
#include "taskscheduler/databasetaskscheduler.h"

DatabaseTaskScheduler scheduler;

bool add_bookmark_test() {
    BookmarkModel model(scheduler);

    return 0
           || !model.addBookmark(1, "bookmarktest3", QUrl("test.com"), "test112313", QUrl("test.icon"))
           || !model.addBookmark(1, "bookmarktest4", QUrl("test2.com"), "test123123", QUrl("test3.icon"));
}

bool get_bookmark_bygid_test() {
    BookmarkModel model(scheduler);

    auto item1 = model.getItemsByGid(1, 802222310);
    auto item2 = model.getItemsByGid(1, 1104652184);


    return 0
           || item1.empty()
           || item2.empty();

}

bool edit_bokmark_test() {
    BookmarkModel model(scheduler);

    return 0
           || !model.editBookmark(1, 494249112, "BookmarkChanged", QUrl("changedQurl"), "bookmarktest3");

}

bool delete_bookmark_test() {
    BookmarkModel model(scheduler);

    return 0
           || model.deleteBookmark(1, 1428143438);
}

int main(int argc, char **argv) {
    scheduler.run();
//    return 0
//           || !add_bookmark_test()
//           || !get_bookmark_bygid_test()
//           || !edit_bokmark_test()
//           || !delete_bookmark_test();
    return 0;
}