#include "src/BookmarkModel.h"


int main(int argc, char** argv){
    BookmarkModel* model = new BookmarkModel();
    auto groups = model->initGetGroups();

    for (auto & group : groups){
        qDebug() << group;
    }

    return 1;
}