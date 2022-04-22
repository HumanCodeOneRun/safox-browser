#ifndef BOOKMARKMODEL_H
#define BOOKMARKMODEL_H
#include <QtGui/QStandardItemModel>
#include <QtWebEngineCore>
#include "dao/BookmarkDao.h"
#include "dao/BookmarkGroupDao.h"

class BookmarkModel{
    Q_OBJECT // for slots

public:
    BookmarkModel();

    class BookmarkItem{
    public:
        BookmarkItem();
        QVector<QVariant> getItemById(const int& id);
        
        inline int getId() { return this->id; }
        inline QString getName() { return this->name; }
        inline int getGid() { return this->gid;}
        inline QString getIcon() { return this->icon; }
        inline QUrl getUrl() { return this->url; }

        bool setName(const int& id, const QString& name);
        bool setGid(const int& id, const int& gid); 
        bool setUrl(const int& id, const QUrl& url);
        bool setIcon(const int& id, const QString& icon);

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
        QVector<QVariant> getGroupById(const int& gid);

        inline int getGid() { return this->gid; }
        inline QString getName() { return this->name; }
        inline int getCount() { return this->count;}
        inline QString getIcon() { return this->icon; } 

        bool setName(const int& gid, const QString& name);
        bool setIcon(const int& gid, const QString& icon);

    private:
        int gid;
        QString name;
        int count; // number of bookmark in this group
        QString icon;

        BookmarkGroupDao dao;
    };

public slots:
    
    QVector<QVector<QVariant>> getItemsByGid(const int& gid);
    QVector<QVector<QVariant>> getGroupsByGid(const QString& name);

    bool addBookmark();
    bool deleteBookmark();
    bool editBookmark();
    
private:


};



#endif