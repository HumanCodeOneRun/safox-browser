#include "BookmarkModel.h"

// bookmark group item
BookmarkModel::BookmarkGroupItem::BookmarkGroupItem()
:gid(-1), name("null"), count(-1), icon("null")
{
    this->dao = BookmarkGroupDao::getDao();
}

BookmarkModel::BookmarkGroupItem BookmarkModel::BookmarkGroupItem::getGroupById(const int& gid){
    QVector<QVariant> ret = (this->dao).QueryById(gid);
    if(ret.empty()){
        qDebug() << "[error] fail to query group by id";
        return *this;
    }
    this->gid = ret.value(0).toInt();
    this->name = ret.value(1).toString();
    this->count = ret.value(2).toInt();
    this->icon = ret.value(3).toString();

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


BookmarkModel::BookmarkGroupItem BookmarkModel::BookmarkGroupItem::getGroupByName(const QString& name){
    QVector<QVariant> ret = (this->dao).QueryByName(name);
    if(ret.empty()){
        qDebug() << "[error] fail to query group by id";
        return *this;
    }
    this->gid = ret.value(0).toInt();
    this->name = ret.value(1).toString();
    this->count = ret.value(2).toInt();
    this->icon = ret.value(3).toString();

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

QVector<QVector<QVariant>> BookmarkModel::BookmarkGroupItem::getAllGroup(){
    return (this->dao).QueryAll();
}

bool BookmarkModel::BookmarkGroupItem::setName(const int& gid, const QString& name){
    this->name = name;
    return (this->dao).setName(gid, name);
}

bool BookmarkModel::BookmarkGroupItem::setIcon(const int& gid, const QString& icon){
    this->icon = icon;
    return (this->dao).setIcon(gid, icon);
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

QVector<QVariant> BookmarkModel::BookmarkItem::getItemById(const int& id){
    QVector<QVariant> ret = (this->dao).QueryById(gid);
    if(ret.empty()){
        qDebug() << "[error] fail to query book mark item by id";
        return ret;
    }
    this->id = ret.value(0).toInt();
    this->gid = ret.value(1).toInt();
    this->name = ret.value(2).toString();
    this->url = ret.value(3).toUrl();
    this->icon = ret.value(4).toString();

    return ret;

}

QVector<QVector<QVariant>> BookmarkModel::BookmarkItem::getItemByGid(const int& gid){
    return (this->dao).QueryByGroupId(gid);
}

bool BookmarkModel::BookmarkItem::setName(const int& id, const QString& name){
    this->name = name;
    return (this->dao).setName(id, name);
}

bool BookmarkModel::BookmarkItem::setGid(const int& id, const int& gid){
    this->gid = gid;
    return (this->dao).setGid(id, gid);
}

bool BookmarkModel::BookmarkItem::setUrl(const int& id, const QUrl& url){
    this->url = url;
    return (this->dao).setUrl(id, url);
}

bool BookmarkModel::BookmarkItem::setIcon(const int& id, const QString& icon){
    this->icon = icon;
    return (this->dao).setIcon(id, icon);
}

bool BookmarkModel::BookmarkItem::addBookmark(const QString& name, const QUrl& url, const QString& gname){
    BookmarkGroupItem gitem;
    BookmarkGroupItem target = gitem.getGroupByName(gname);

    return (this->dao).insert(target.getGid(), name, url);
}

bool BookmarkModel::BookmarkItem::deleteBookmark(const int& id){
    return (this->dao).remove(id);
}

BookmarkModel::BookmarkItem::~BookmarkItem(){
    (this->dao).close();
}


// bookmark model
BookmarkModel::BookmarkModel(){

}

QVector<QVector<QVariant>> BookmarkModel::initGetGroups(){
    BookmarkGroupItem item;
    return item.getAllGroup();
}

QVector<QVector<QVariant>> BookmarkModel::getItemsByGid(const int& gid){
    BookmarkItem item;
    return item.getItemByGid(gid);
}

bool BookmarkModel::addBookmark(const QString& name, const QUrl& url, const QString& gname){
    BookmarkItem item;
    return item.addBookmark(name, url, gname);
}

bool BookmarkModel::editBookmark(const int& id, const QString& name, const QUrl& url, const QString& gname){
    BookmarkItem item;
    if(!name.isEmpty()){
        if(!item.setName(id, name)){
            qDebug() << "[error] fail to edit bookmark name ";
            return false;
        }
    }

    if(!url.isEmpty()){
        if(!item.setUrl(id, url)){
            qDebug() << "[error] fail to edit bookmark url ";
            return false;
        }
    }

    if(!gname.isEmpty()){
        BookmarkGroupItem gitem;
        BookmarkGroupItem target = gitem.getGroupByName(name);

        if(!item.setGid(id, target.getGid())){
            qDebug() << "[error] fail to edit bookmark group ";
            return false;
        }
    }

    return true;
    
}


bool BookmarkModel::deleteBookmark(const int& id){
    BookmarkItem item;
    return item.deleteBookmark(id);
}

BookmarkModel::~BookmarkModel(){
    
}
