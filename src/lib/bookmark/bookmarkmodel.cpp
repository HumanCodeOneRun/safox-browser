#include "bookmarkmodel.h"

// bookmark group item

BookmarkModel::BookmarkGroupItem::BookmarkGroupItem(std::shared_ptr<DatabaseTaskScheduler> scheduler)
:gid(-1), name("null"), uid(-1), icon("null")
{   
    this->dao = std::make_unique<BookmarkGroupDao>(scheduler);
}

QVector<QVariant> BookmarkModel::BookmarkGroupItem::getGroupByUidAndId(const int& uid, const int& gid){
    QVector<QVariant> ret = (this->dao)->QueryByUidAndId(uid, gid);
    if(ret.empty()){
        qDebug() << "[error] fail to query group by uid and id";
        return ret;
    }
    this->uid = ret.value(0).toInt();
    this->gid = ret.value(1).toInt();
    this->name = ret.value(2).toString();
    this->icon = ret.value(3).toUrl();

    return ret;

}



QVector<QVariant> BookmarkModel::BookmarkGroupItem::getGroupByUidAndName(const int& uid, const QString& name){
    QVector<QVariant> ret = (this->dao)->QueryByUidAndName(uid, name);
    if(ret.empty()){
        qDebug() << "[warning] no group named " << name;
        return ret;
    }
    this->uid = ret.value(0).toInt();
    this->gid = ret.value(1).toInt();
    this->name = ret.value(2).toString();
    this->icon = ret.value(3).toUrl();

    return ret;

}


QVector<QVector<QVariant>> BookmarkModel::BookmarkGroupItem::getAllGroup(const int& uid){
    return (this->dao)->QueryAll(uid);
}

bool BookmarkModel::BookmarkGroupItem::addGroup(const int& uid, const QString& name, const QUrl& icon){
    this->name = name;
    this->icon = icon;
    this->uid = uid;
    return (this->dao)->insert(uid, name, icon.toString());
}


bool BookmarkModel::BookmarkGroupItem::setName(const int& uid, const int& gid, const QString& name){
    this->name = name;
    return (this->dao)->setName(uid, gid, name);
}

bool BookmarkModel::BookmarkGroupItem::setIcon(const int& uid, const int& gid, const QUrl& icon){
    this->icon = icon;
    return (this->dao)->setIcon(uid, gid, icon.toString());
}

bool BookmarkModel::BookmarkGroupItem::deleteBookmarkGroup(const int& uid, const int& gid){
    return (this->dao)->remove(uid, gid);
}

QString BookmarkModel::BookmarkGroupItem::get_connection(){
    return (this->dao)->get_connection();
}

void BookmarkModel::BookmarkGroupItem::create_table(){
     (this->dao)->createTable();
}

BookmarkModel::BookmarkGroupItem::~BookmarkGroupItem(){
    
}


// bookmark item

BookmarkModel::BookmarkItem::BookmarkItem(std::shared_ptr<DatabaseTaskScheduler> scheduler)
:id(-1), gid(-1), name("null"), url("null"), icon("null")
{
    this->dao = std::make_unique<BookmarkDao>(scheduler);
}

QVector<QVariant> BookmarkModel::BookmarkItem::getItemByUidAndId(const int& uid, const int& id){
    QVector<QVariant> ret = (this->dao)->QueryByUidAndId(uid, id);
    if(ret.empty()){
        qDebug() << "[error] fail to query book mark item by id";
        return ret;
    }
    this->uid = ret.value(0).toInt();
    this->id = ret.value(1).toInt();
    this->gid = ret.value(2).toInt();
    this->name = ret.value(3).toString();
    this->url = ret.value(4).toUrl();
    this->icon = ret.value(5).toUrl();

    return ret;

}

QVector<QVector<QVariant>> BookmarkModel::BookmarkItem::getItemByUidAndGid(const int& uid, const int& gid){
    return (this->dao)->QueryByUidAndGroupId(uid, gid);
}

bool BookmarkModel::BookmarkItem::setName(const int& uid,const int& id, const QString& name){
    this->name = name;
    return (this->dao)->setName(uid, id, name);
}

bool BookmarkModel::BookmarkItem::setGid(const int& uid, const int& id, const int& gid){
    this->gid = gid;
    return (this->dao)->setGid(uid, id, gid);
}

bool BookmarkModel::BookmarkItem::setUrl(const int& uid,const int& id, const QUrl& url){
    this->url = url;
    return (this->dao)->setUrl(uid, id, url);
}

bool BookmarkModel::BookmarkItem::setIcon(const int& uid,const int& id, const QUrl& icon){
    this->icon = icon;
    return (this->dao)->setIcon(uid, id, icon.toString());
}

bool BookmarkModel::BookmarkItem::addBookmark(const int& uid, const QString& name, const QUrl& url, const int& gid,  const QUrl& icon){

    return (this->dao)->insert(uid, gid, name, url, icon);
}

bool BookmarkModel::BookmarkItem::deleteBookmark(const int& uid, const int& id){
    return (this->dao)->remove(uid, id);
}

void BookmarkModel::BookmarkItem::create_table(){
     (this->dao)->createTable();
}

QString BookmarkModel::BookmarkItem::get_connection(){
    return (this->dao)->get_connection();
}

BookmarkModel::BookmarkItem::~BookmarkItem(){
    
}


// bookmark model
BookmarkModel::BookmarkModel(std::shared_ptr<DatabaseTaskScheduler> _scheduler):
m_taskScheduler(_scheduler)
{   
    this->gitem = std::make_unique<BookmarkGroupItem>(this->m_taskScheduler);
    this->item = std::make_unique<BookmarkItem>(this->m_taskScheduler);
}

QVector<QVector<QVariant>> BookmarkModel::initGetGroups(const int& uid){
    
    
    auto future = m_taskScheduler->post([this, &uid](){
        return this->gitem->getAllGroup(uid);
    });

    return future.get();
}

QVector<QVector<QVariant>> BookmarkModel::getItemsByGid(const int& uid, const int& gid){
    auto future = m_taskScheduler->post(std::move([this, &uid, &gid](){
        return this->item->getItemByUidAndGid(uid, gid);
    }));
    return future.get();
}

bool BookmarkModel::addBookmarkGroup(const int& uid, const QString& name,  const QUrl& icon){
    auto future = m_taskScheduler->post(std::move([this, &uid, &name,&icon](){
        return this->gitem->addGroup(uid, name, icon);
    }));
    return future.get();
}


bool BookmarkModel::addBookmark(const int& uid, const QString& name, const QUrl& url, const QString& gname, const QUrl& icon){

    auto future = m_taskScheduler->post(std::move([this, &uid,  &gname](){
        return this->gitem->getGroupByUidAndName(uid, gname);
    }));
    
    int gid;
    if(future.get().isEmpty()){
        
        auto future_gid = m_taskScheduler->post(std::move([this, &gname, &uid](){
            this->gitem->addGroup(uid, gname, QUrl("src/image/bookmaker.png"));
            return this->gitem->getGroupByUidAndName(uid, gname).value(1).toInt();
        }));
        gid = future_gid.get();
    }

    auto ret = m_taskScheduler->post(std::move([this, &gid, &uid, &name, &url, &gname, &icon](){
       return this->item->addBookmark(uid, name, url, gid, icon);
    }));
    
    return ret.get();
}


bool BookmarkModel::editBookmark(const int& uid, const int& id, const QString& name, const QUrl& url, const QString& gname){
    int name_valid=1, url_valid=1, gid_valid=1;
    if(!name.isEmpty()){
        auto future = m_taskScheduler->post(std::move([this, &uid, &id, &name](){
            return this->item->setName(uid, id, name);
        }));
        name_valid = future.get();
    }

    if(!url.isEmpty()){

        auto future = m_taskScheduler->post(std::move([this, &uid, &id, &url](){
            return this->item->setUrl(uid, id, url);
        }));
        url_valid = future.get();
    }

    if(!gname.isEmpty()){
        auto future = m_taskScheduler->post(std::move([this,&id, &uid, &gname](){
            auto gid = this->gitem->getGroupByUidAndName(uid, gname).value(1).toInt();
            return this->item->setGid(uid, id, gid);
        }));
        gid_valid =  future.get();
    }

    return name_valid && url_valid && gid_valid;
    
}

bool BookmarkModel::deleteBookmark(const int& uid, const int& id){
    auto future = m_taskScheduler->post(std::move([this, &uid, &id](){
        return this->item->deleteBookmark(uid, id);
    }));
    return future.get();
}


bool BookmarkModel::deleteBookmarkGroup(const int& uid, const int& gid){
    auto future = m_taskScheduler->post(std::move([this, &uid, &gid](){
        return this->gitem->deleteBookmarkGroup(uid, gid);
    }));
    return future.get();
}

/*
void BookmarkModel::resetDB(){
    
    BookmarkItem item;
    item.dropTable();

    BookmarkGroupItem gitem;
    gitem.dropTable();
    
}
*/
BookmarkModel::~BookmarkModel(){
    
}