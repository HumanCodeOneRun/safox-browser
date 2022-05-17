#ifndef BOOKMARKMODEL_H
#define BOOKMARKMODEL_H

#include <QtWebEngineCore>
#include "bookmarkdao.h"
#include "bookmarkgroupdao.h"
#include "taskscheduler/databasetaskscheduler.h"


class BookmarkModel : public QObject {

public:
    explicit BookmarkModel(std::shared_ptr<DatabaseTaskScheduler> scheduler);

    ~BookmarkModel();

    class BookmarkItem {
    public:
        BookmarkItem(std::shared_ptr<DatabaseTaskScheduler> scheduler);

        QVector<QVariant> getItemByUidAndId(const int &uid, const int &id);

        QVector<QVector<QVariant> > getItemByUidAndGid(const int &uid, const int &gid);

        inline int getUid() { return this->uid; }

        inline int getId() { return this->id; }

        inline QString getName() { return this->name; }

        inline int getGid() { return this->gid; }

        inline QUrl getIcon() { return this->icon; }

        inline QUrl getUrl() { return this->url; }

        bool setName(const int &uid, const int &id, const QString &name);

        bool setGid(const int &uid, const int &id, const int &gid);

        bool setUrl(const int &uid, const int &id, const QUrl &url);

        bool setIcon(const int &uid, const int &id, const QUrl &icon);

        bool addBookmark(const int &uid, const QString &name, const QUrl &url, const int &gid, const QUrl &icon);

        bool deleteBookmark(const int &uid, const int &id);

        void create_table();

        QString get_connection();

        ~BookmarkItem();


    private:
        std::unique_ptr<BookmarkDao> dao;
        int uid;
        int id;
        int gid;
        QString name;
        QUrl url;
        QUrl icon;

    };

    class BookmarkGroupItem {
    public:
        BookmarkGroupItem(std::shared_ptr<DatabaseTaskScheduler> scheduler);

        QVector<QVariant> getGroupByUidAndId(const int &uid, const int &gid);

        //QVector<QVariant> getGroupById(const int& gid);
        QVector<QVariant> getGroupByUidAndName(const int &uid, const QString &name);

        //QVector<QVariant> getGroupByName(const QString& name);
        QVector<QVector<QVariant>> getAllGroup(const int &uid);

        bool addGroup(const int &uid, const QString &name, const QUrl &icon);

        inline int getGid() { return this->gid; }

        inline QString getName() { return this->name; }

        inline int getUid() { return this->uid; }

        inline QUrl getIcon() { return this->icon; }

        bool setName(const int &uid, const int &gid, const QString &name);

        bool setIcon(const int &uid, const int &gid, const QUrl &icon);

        bool deleteBookmarkGroup(const int &uid, const int &gid);

        void print_db_state() { this->dao->print_db_state(); }

        QString get_connection();

        void create_table();

        ~BookmarkGroupItem();

    private:
        std::unique_ptr<BookmarkGroupDao> dao;

        int uid;
        int gid;
        QString name;
        QUrl icon;

        //static BookmarkGroupDao dao;
    };

public:

    QVector<QVector<QVariant>> initGetGroups(const int &uid);

    QVector<QVector<QVariant>> getItemsByGid(const int &uid, const int &gid);

    bool addBookmarkGroup(const int &uid, const QString &name, const QUrl &icon);

    bool addBookmark(const int &uid, const QString &name, const QUrl &url, const QString &gname, const QUrl &icon);


    bool deleteBookmark(const int &uid, const int &id);

    bool editBookmark(const int &uid, const int &id, const QString &name = "", const QUrl &url = QUrl(""),
                      const QString &gname = "");

    bool deleteBookmarkGroup(const int &uid, const int &gid);

    // for debug
    void resetDB();

private:
    std::shared_ptr<DatabaseTaskScheduler> m_taskScheduler;

    std::unique_ptr<BookmarkGroupItem> gitem;
    std::unique_ptr<BookmarkItem> item;
};


#endif