#include "bookmarkmodel.h"
#include "databasetaskscheduler.h"
#include <ctime>


bool add_bookmark_test(BookmarkModel &model) {
    clock_t start = clock();
    for(int i = 0; i < 10; i++){
        model.addBookmark(i, "bookmarktest"+QString::number(i), QUrl("bookmarktest"+QString::number(i)), "bookmarktest"+QString::number(i), QUrl("bookmarktest"+QString::number(i)));
    }
    clock_t end = clock();
    qDebug()<<"time = "<<double(end-start)/CLOCKS_PER_SEC<<"s";

    return 0;
           
}

bool get_bookmark_bygid_test(BookmarkModel &model) {

    auto item1 = model.getItemsByGid(1, 802222310);
    auto item2 = model.getItemsByGid(1, 1104652184);


    return 0
           || item1.empty()
           || item2.empty();

}

bool edit_bokmark_test(BookmarkModel &model) {

    return 0
           || !model.editBookmark(1, 494249112, "BookmarkChanged", QUrl("changedQurl"), "bookmarktest3");

}

bool delete_bookmark_test(BookmarkModel &model) {

    return 0
           || model.deleteBookmark(1, 1428143438);
}


int main(int argc, char **argv) {
    auto scheduler = std::make_shared<DatabaseTaskScheduler>(2);
    scheduler->run();
    static BookmarkModel model(scheduler);
    return 0
           || !add_bookmark_test(model);
//           || !get_bookmark_bygid_test(model);
//           || !edit_bokmark_test()
//           || !delete_bookmark_test();
}