#ifndef BOOKMARKMODEL_H
#define BOOKMARKMODEL_H

#include <QtWebEngineCore>
#include "bookmarkdao.h"
#include "bookmarkgroupdao.h"
#include "taskscheduler/databasetaskscheduler.h"

//#include "BookmarkModel.moc"
// TODO: 1. auto-increment for count in bookmark group
//       2. consider return BookmarkItem/BookmarkItem for convinience

class BookmarkModel {

public:
    explicit BookmarkModel(DatabaseTaskScheduler &taskScheduler);
    ~BookmarkModel();
    class BookmarkItem{
    public:
        BookmarkItem();
        QVector<QVariant> getItemByUidAndId(const int& uid, const int& id);
        QVector<QVector<QVariant>> getItemByUidAndGid(const int& uid, const int& gid);
        
        inline int getUid() { return this->uid; }
        inline int getId() { return this->id; }
        inline QString getName() { return this->name; }
        inline int getGid() { return this->gid;}
        inline QUrl getIcon() { return this->icon; }
        inline QUrl getUrl() { return this->url; }

        bool setName(const int& uid, const int& id, const QString& name);
        bool setGid(const int& uid, const int& id, const int& gid); 
        bool setUrl(const int& uid, const int& id, const QUrl& url);
        bool setIcon(const int& uid, const int& id, const QUrl& icon);

        bool addBookmark(const int& uid, const QString& name, const QUrl& url, const QString& gname, const QUrl& icon);
        bool deleteBookmark(const int& uid, const int& id);
        

        ~BookmarkItem();
    private:
        int uid;
        int id;
        int gid;
        QString name;
        QUrl url;
        QUrl icon;

        BookmarkDao dao;
    };

    class BookmarkGroupItem{
    public:
        BookmarkGroupItem();
        BookmarkGroupItem getGroupByUidAndId(const int& uid, const int& gid);
        //QVector<QVariant> getGroupById(const int& gid);
        BookmarkGroupItem getGroupByUidAndName(const int& uid, const QString& name);
        //QVector<QVariant> getGroupByName(const QString& name);
        QVector<QVector<QVariant>> getAllGroup(const int& uid);
        bool addGroup(const int&uid, const QString& name, const QUrl& icon);

        inline int getGid() { return this->gid; }
        inline QString getName() { return this->name; }
        inline int getUid() { return this->uid;}
        inline QUrl getIcon() { return this->icon; } 

        bool setName(const int& uid, const int& gid, const QString& name);
        bool setIcon(const int& uid, const int& gid, const QUrl& icon);

        bool deleteBookmarkGroup(const int& uid, const int& gid);
        ~BookmarkGroupItem();

    private:
        int uid;
        int gid;
        QString name;
        int count; // number of bookmark in this group
        QUrl icon;

        BookmarkGroupDao dao;
    };

public:

    QVector<QVector<QVariant>> initGetGroups(const int& uid);
    QVector<QVector<QVariant>> getItemsByGid(const int& uid, const int& gid);

    bool addBookmarkGroup(const int& uid, const QString& name,  const QUrl& icon);
    bool addBookmark(const int& uid, const QString& name, const QUrl& url, const QString& gname, const QUrl& icon);
    bool deleteBookmark(const int& uid, const int& id);
    bool editBookmark(const int& uid, const int& id, const QString& name="", const QUrl& url=QUrl(""), const QString& gname="");
    bool deleteBookmarkGroup(const int& uid, const int& gid);

private:
    DatabaseTaskScheduler &m_taskScheduler;


};

//#include "BookmarkModel.moc"

#endif