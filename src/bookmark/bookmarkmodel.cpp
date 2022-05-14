#include "bookmarkmodel.h"

// bookmark group item
BookmarkGroupDao BookmarkModel::BookmarkGroupItem::dao = BookmarkGroupDao::getDao();
BookmarkDao BookmarkModel::BookmarkItem::dao = BookmarkDao::getDao();
BookmarkModel::BookmarkGroupItem::BookmarkGroupItem()
:gid(-1), name("null"), uid(-1), icon("null")
{
    //this->dao = BookmarkGroupDao::getDao();
}

BookmarkModel::BookmarkGroupItem BookmarkModel::BookmarkGroupItem::getGroupByUidAndId(const int& uid, const int& gid){
    QVector<QVariant> ret = (this->dao).QueryByUidAndId(uid, gid);
    if(ret.empty()){
        qDebug() << "[error] fail to query group by uid and id";
        return *this;
    }
    this->uid = ret.value(0).toInt();
    this->gid = ret.value(1).toInt();
    this->name = ret.value(2).toString();
    this->icon = ret.value(3).toUrl();

    return *this;

}


/*
// TODO change return value to BookmarkGroupItem()
// TODO migarate the inner class function to return inner class 
QVector<QVariant> BookmarkModel::BookmarkGroupItem::getGroupById(const int& gid){
    // bookmark class infomation can be used to judge
    // whether the query succeeded

    QVector<QVariant> ret = (this->dao).QueryById(gid);
    if(ret.empty()){
        qDebug() << "[error] fail to query group by id";
        return ret;
    }
    this->gid = ret.value(0).toInt();
    this->name = ret.value(1).toString();
    this->count = ret.value(2).toInt();
    this->icon = ret.value(3).toString();

    return ret;

}
*/


BookmarkModel::BookmarkGroupItem BookmarkModel::BookmarkGroupItem::getGroupByUidAndName(const int& uid, const QString& name){
    QVector<QVariant> ret = (this->dao).QueryByUidAndName(uid, name);
    if(ret.empty()){
        qDebug() << "[warning] no group named " << name;
        return *this;
    }
    this->uid = ret.value(0).toInt();
    this->gid = ret.value(1).toInt();
    this->name = ret.value(2).toString();
    this->icon = ret.value(3).toUrl();

    return *this;

}

/*
QVector<QVariant> BookmarkModel::BookmarkGroupItem::getGroupByName(const QString& name){
    QVector<QVariant> ret = (this->dao).QueryByName(name);
    if(ret.empty()){
        qDebug() << "[error] fail to query group by id";
        return ret;
    }
    this->gid = ret.value(0).toInt();
    this->name = ret.value(1).toString();
    this->count = ret.value(2).toInt();
    this->icon = ret.value(3).toString();

    return ret;

}
*/

QVector<QVector<QVariant>> BookmarkModel::BookmarkGroupItem::getAllGroup(const int& uid){
    return (this->dao).QueryAll(uid);
}

bool BookmarkModel::BookmarkGroupItem::addGroup(const int& uid, const QString& name, const QUrl& icon){
    this->name = name;
    this->icon = icon;
    this->uid = uid;
    return (this->dao).insert(uid, name, icon.toString());
}


bool BookmarkModel::BookmarkGroupItem::setName(const int& uid, const int& gid, const QString& name){
    this->name = name;
    return (this->dao).setName(uid, gid, name);
}

bool BookmarkModel::BookmarkGroupItem::setIcon(const int& uid, const int& gid, const QUrl& icon){
    this->icon = icon;
    return (this->dao).setIcon(uid, gid, icon.toString());
}

bool BookmarkModel::BookmarkGroupItem::deleteBookmarkGroup(const int& uid, const int& gid){
    return (this->dao).remove(uid, gid);
}

QString BookmarkModel::BookmarkGroupItem::get_connection(){
    return (this->dao).get_connection();
}

BookmarkModel::BookmarkGroupItem::~BookmarkGroupItem(){
    (this->dao).close();
}


// bookmark item

BookmarkModel::BookmarkItem::BookmarkItem()
:id(-1), gid(-1), name("null"), url("null"), icon("null")
{
    //this->dao = BookmarkDao::getDao();
}

QVector<QVariant> BookmarkModel::BookmarkItem::getItemByUidAndId(const int& uid, const int& id){
    QVector<QVariant> ret = (this->dao).QueryByUidAndId(uid, id);
    if(ret.empty()){
        qDebug() << "[error] fail to query book mark item by id";
        return ret;
    }
    this->id = ret.value(0).toInt();
    this->gid = ret.value(1).toInt();
    this->name = ret.value(2).toString();
    this->url = ret.value(3).toUrl();
    this->icon = ret.value(4).toUrl();

    return ret;

}

QVector<QVector<QVariant>> BookmarkModel::BookmarkItem::getItemByUidAndGid(const int& uid, const int& gid){
    return (this->dao).QueryByUidAndGroupId(uid, gid);
}

bool BookmarkModel::BookmarkItem::setName(const int& uid,const int& id, const QString& name){
    this->name = name;
    return (this->dao).setName(uid, id, name);
}

bool BookmarkModel::BookmarkItem::setGid(const int& uid, const int& id, const int& gid){
    this->gid = gid;
    return (this->dao).setGid(uid, id, gid);
}

bool BookmarkModel::BookmarkItem::setUrl(const int& uid,const int& id, const QUrl& url){
    this->url = url;
    return (this->dao).setUrl(uid, id, url);
}

bool BookmarkModel::BookmarkItem::setIcon(const int& uid,const int& id, const QUrl& icon){
    this->icon = icon;
    return (this->dao).setIcon(uid, id, icon.toString());
}

bool BookmarkModel::BookmarkItem::addBookmark(const int& uid, const QString& name, const QUrl& url, const int& gid,  const QUrl& icon){

    return (this->dao).insert(uid, gid, name, url, icon);
}

bool BookmarkModel::BookmarkItem::deleteBookmark(const int& uid, const int& id){
    return (this->dao).remove(uid, id);
}

QString BookmarkModel::BookmarkItem::get_connection(){
    return (this->dao).get_connection();
}

BookmarkModel::BookmarkItem::~BookmarkItem(){
    (this->dao).close();
}


// bookmark model
BookmarkModel::BookmarkModel(DatabaseTaskScheduler &taskScheduler):
m_taskScheduler(taskScheduler)
{
}

QVector<QVector<QVariant>> BookmarkModel::initGetGroups(const int& uid){
    BookmarkGroupItem item;
    std::promise<QVector<QVector<QVariant>>> pm;
    std::future<QVector<QVector<QVariant>>> future = pm.get_future();
    m_taskScheduler.post([&pm,&item, &uid](){
        auto ret =  item.getAllGroup(uid);
        pm.set_value(ret);
    });
    return future.get();
}

QVector<QVector<QVariant>> BookmarkModel::getItemsByGid(const int& uid, const int& gid){
    BookmarkItem item;
    std::promise<QVector<QVector<QVariant>>> pm;
    std::future<QVector<QVector<QVariant>>> future = pm.get_future();
    m_taskScheduler.post([&pm,&item, &uid, &gid](){
        auto ret =  item.getItemByUidAndGid(uid, gid);
        pm.set_value(ret);
    });
    return future.get();
}

bool BookmarkModel::addBookmarkGroup(const int& uid, const QString& name,  const QUrl& icon){
    BookmarkGroupItem item;
    std::promise<bool> pm;
    std::future<bool> future = pm.get_future();
    m_taskScheduler.post([&pm,&item, &uid, &name,&icon](){
        int ret =  item.addGroup(uid, name, icon);
        pm.set_value(ret);
    });
    return future.get();
}


bool BookmarkModel::addBookmark(const int& uid, const QString& name, const QUrl& url, const QString& gname, const QUrl& icon){
    BookmarkItem item;
    BookmarkGroupItem gitem;
    std::promise<bool> pm;
    std::future<bool> future = pm.get_future();

    std::promise<int> get_pm;
    std::future<int> get_future = get_pm.get_future();

    //gitem.print_db_state();
    m_taskScheduler.post([&uid, &get_pm, &gname, &gitem](){
        int ret = gitem.getGroupByUidAndName(uid, gname).getGid();
        get_pm.set_value(ret);
        
    });
    int gid = get_future.get();

    if(gid == -1){
        //gitem.print_db_state();
        m_taskScheduler.post([&gitem, &gid, &gname, &uid, &pm](){
            int ret = gitem.addGroup(uid, gname, QUrl("src/image/bookmaker.png"));
            pm.set_value(ret);
        });
        bool ok = future.get();
        
        //gitem.print_db_state();
        m_taskScheduler.post([&gitem, &gid, &gname, &uid, &get_pm](){
            int ret = gitem.getGroupByUidAndName(uid, gname).getGid();
            get_pm.set_value(ret);
        });
        gid = get_future.get();
    }

    
    m_taskScheduler.post([&gid, &pm,&item, &uid, &name, &url, &gname, &icon](){
       int ret = item.addBookmark(uid, name, url, gid, icon);
       pm.set_value(ret);
    });
    return future.get();
}

bool BookmarkModel::editBookmark(const int& uid, const int& id, const QString& name, const QUrl& url, const QString& gname){
    BookmarkItem item;
    int name_valid, url_valid, gid_valid;
    name_valid = url_valid = gid_valid = 1;
    if(!name.isEmpty()){
//        if(!item.setName(uid, id, name)){
//            qDebug() << "[error] fail to edit bookmark name ";
//            return false;
//        }

        std::promise<bool> pm;
        std::future<bool> future = pm.get_future();
        m_taskScheduler.post([&pm,&item, &uid, &id, &name](){
            int ret = item.setName(uid, id, name);
            pm.set_value(ret);
        });
        name_valid = future.get();
    }

    if(!url.isEmpty()){
//        if(!item.setUrl(uid, id, url)){
//            qDebug() << "[error] fail to edit bookmark url ";
//            return false;
//        }

        std::promise<bool> pm;
        std::future<bool> future = pm.get_future();
        m_taskScheduler.post([&pm,&item, &uid, &id, &url](){
            int ret = item.setUrl(uid, id, url);
            pm.set_value(ret);
        });
        url_valid = future.get();
    }

    if(!gname.isEmpty()){
        BookmarkGroupItem gitem;
        std::promise<BookmarkGroupItem> pm_target;
        std::future<BookmarkGroupItem> futureTarget = pm_target.get_future();
        m_taskScheduler.post([&pm_target,&gitem, &uid, &name](){
            BookmarkGroupItem target = gitem.getGroupByUidAndName(uid, name);
            pm_target.set_value(target);
        });
        BookmarkGroupItem target = futureTarget.get();

        std::promise<bool> pm;
        std::future<bool> future = pm.get_future();
        m_taskScheduler.post([&pm,&item, &uid, &id, &target](){
            int ret = item.setGid(uid, id, target.getGid());
            pm.set_value(ret);
        });
        gid_valid =  future.get();
//        if(!item.setGid(uid, id, target.getGid())){
//            qDebug() << "[error] fail to edit bookmark group ";
//            return false;
//        }
    }

    return name_valid && url_valid && gid_valid;
    
}


bool BookmarkModel::deleteBookmark(const int& uid, const int& id){
    BookmarkItem item;
    std::promise<bool> pm;
    std::future<bool> future = pm.get_future();
    m_taskScheduler.post([&pm,&item, &uid, &id](){
        int ret =  item.deleteBookmark(uid, id);
        pm.set_value(ret);
    });
    return future.get();
}


bool BookmarkModel::deleteBookmarkGroup(const int& uid, const int& gid){
    BookmarkGroupItem item;
    std::promise<bool> pm;
    std::future<bool> future = pm.get_future();
    m_taskScheduler.post([&pm,&item, &uid, &gid](){
        int ret =  item.deleteBookmarkGroup(uid, gid);
        pm.set_value(ret);
    });
    return future.get();
}

BookmarkModel::~BookmarkModel(){
    
}