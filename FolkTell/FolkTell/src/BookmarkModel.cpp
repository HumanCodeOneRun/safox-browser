#include "BookmarkModel.h"

// bookmark group item
BookmarkModel::BookmarkGroupItem::BookmarkGroupItem()
:gid(-1), name("null"), count(-1), icon("null")
{
    this->dao = BookmarkGroupDao::getDao();
}

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

bool BookmarkModel::BookmarkGroupItem::setName(const int& gid, const QString& name){
    this->name = name;
    return (this->dao).setName(gid, name);
}

bool BookmarkModel::BookmarkGroupItem::setIcon(const int& gid, const QString& icon){
    this->icon = icon;
    return (this->dao).setIcon(gid, icon);
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

// bookmark model

