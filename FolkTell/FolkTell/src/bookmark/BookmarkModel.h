#ifndef BOOKMARKMODEL_H
#define BOOKMARKMODEL_H

#include <QtWebEngineCore>
#include "dao/BookmarkDao.h"
#include "dao/BookmarkGroupDao.h"
//#include "BookmarkModel.moc"
// TODO: 1. auto-increment for count in bookmark group
//       2. consider return BookmarkItem/BookmarkItem for convinience

class BookmarkModel {

public:
    BookmarkModel();
    ~BookmarkModel();
    class BookmarkItem{
    public:
        BookmarkItem();
        QVector<QVariant> getItemById(const int& id);
        QVector<QVector<QVariant>> getItemByGid(const int& gid);

        inline int getId() { return this->id; }
        inline QString getName() { return this->name; }
        inline int getGid() { return this->gid;}
        inline QString getIcon() { return this->icon; }
        inline QUrl getUrl() { return this->url; }

        bool setName(const int& id, const QString& name);
        bool setGid(const int& id, const int& gid); 
        bool setUrl(const int& id, const QUrl& url);
        bool setIcon(const int& id, const QString& icon);

        bool addBookmark(const QString& name, const QUrl& url, const QString& gname);
        bool deleteBookmark(const int& id);

        ~BookmarkItem();
    private:
        int id;
        int gid;
        QString name;
        QUrl url;
        QString icon;

        BookmarkDao dao;
    };

    class BookmarkGroupItem{
    public:
        BookmarkGroupItem();
        BookmarkGroupItem getGroupById(const int& gid);
        //QVector<QVariant> getGroupById(const int& gid);
        BookmarkGroupItem getGroupByName(const QString& name);
        //QVector<QVariant> getGroupByName(const QString& name);
        QVector<QVector<QVariant>> getAllGroup();
        bool addGroup(const QString& name, const int& count, const QString& icon);

        inline int getGid() { return this->gid; }
        inline QString getName() { return this->name; }
        inline int getCount() { return this->count;}
        inline QString getIcon() { return this->icon; } 

        bool setName(const int& gid, const QString& name);
        bool setIcon(const int& gid, const QString& icon);

        ~BookmarkGroupItem();

    private:
        int gid;
        QString name;
        int count; // number of bookmark in this group
        QString icon;

        BookmarkGroupDao dao;
    };

public:

    QVector<QVector<QVariant>> initGetGroups();
    QVector<QVector<QVariant>> getItemsByGid(const int& gid);

    bool addBookmarkGroup(const QString& name, const int& count, const QString& icon);
    bool addBookmark(const QString& name, const QUrl& url, const QString& gname);
    bool deleteBookmark(const int& id);
    bool editBookmark(const int& id, const QString& name="", const QUrl& url=QUrl(""), const QString& gname="");
    

private:


};

//#include "BookmarkModel.moc"

#endif