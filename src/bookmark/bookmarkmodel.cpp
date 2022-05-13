#include "bookmarkmodel.h"

// bookmark group item
BookmarkModel::BookmarkGroupItem::BookmarkGroupItem()
:gid(-1), name("null"), uid(-1), icon("null")
{
    this->dao = BookmarkGroupDao::getDao();
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
        qDebug() << "[warning] no such group named " << name;
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

void BookmarkModel::BookmarkGroupItem::dropTable(){
    (this->dao).deleteTable();
}

BookmarkModel::BookmarkGroupItem::~BookmarkGroupItem(){
    (this->dao).close();
}


// bookmark item

BookmarkModel::BookmarkItem::BookmarkItem()
:id(-1), gid(-1), name("null"), url("null"), icon("null")
{
    this->dao = BookmarkDao::getDao();
}

QVector<QVariant> BookmarkModel::BookmarkItem::getItemByUidAndId(const int& uid, const int& id){
    QVector<QVariant> ret = (this->dao).QueryByUidAndId(uid, id);
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

void BookmarkModel::BookmarkItem::dropTable(){
    (this->dao).deleteTable();
}

BookmarkModel::BookmarkItem::~BookmarkItem(){
    (this->dao).close();
}


// bookmark model
BookmarkModel::BookmarkModel(){
    
}

QVector<QVector<QVariant>> BookmarkModel::initGetGroups(const int& uid){
    BookmarkGroupItem item;
    // create a default bookmark group
    auto group_list = item.getAllGroup(uid);
    if(group_list.empty()){
        item.addGroup(uid, "default", QUrl("src/image/bookmaker.png"));
        group_list = item.getAllGroup(uid);
    }

    return group_list;
}

QVector<QVector<QVariant>> BookmarkModel::getItemsByGid(const int& uid, const int& gid){
    BookmarkItem item;
   
    return item.getItemByUidAndGid(uid, gid);
}

bool BookmarkModel::addBookmarkGroup(const int& uid, const QString& name,  const QUrl& icon){
    BookmarkGroupItem item;
    return item.addGroup(uid, name, icon);
}


bool BookmarkModel::addBookmark(const int& uid, const QString& name, const QUrl& url, const QString& gname, const QUrl& icon){
    BookmarkItem item;
    // create directory if not exists
    BookmarkGroupItem gitem;
    if(gitem.getGroupByUidAndName(uid, gname).getGid() == -1){
        bool ok = gitem.addGroup(uid, gname, QUrl("src/image/bookmaker.png"));
        if(!ok){
            qDebug() << "[error] fail to create non-exist group.";
            return false;
        }
    }
    int gid = gitem.getGroupByUidAndName(uid, gname).getGid();

    return item.addBookmark(uid, name, url, gid, icon);
}

bool BookmarkModel::editBookmark(const int& uid, const int& id, const QString& name, const QUrl& url, const QString& gname){
    BookmarkItem item;
    if(!name.isEmpty()){
        if(!item.setName(uid, id, name)){
            qDebug() << "[error] fail to edit bookmark name ";
            return false;
        }
    }

    if(!url.isEmpty()){
        if(!item.setUrl(uid, id, url)){
            qDebug() << "[error] fail to edit bookmark url ";
            return false;
        }
    }

    if(!gname.isEmpty()){
        BookmarkGroupItem gitem;
        BookmarkGroupItem target = gitem.getGroupByUidAndName(uid, name);

        if(!item.setGid(uid, id, target.getGid())){
            qDebug() << "[error] fail to edit bookmark group ";
            return false;
        }
    }

    return true;
    
}


bool BookmarkModel::deleteBookmark(const int& uid, const int& id){
    BookmarkItem item;
    return item.deleteBookmark(uid, id);
}


bool BookmarkModel::deleteBookmarkGroup(const int& uid, const int& gid){
    BookmarkGroupItem item;

    // TODO: delete the bookmark with gid=gid
    return item.deleteBookmarkGroup(uid, gid);
}

void BookmarkModel::resetDB(){
    BookmarkItem item;
    item.dropTable();

    BookmarkGroupItem gitem;
    gitem.dropTable();
}

BookmarkModel::~BookmarkModel(){
    
}