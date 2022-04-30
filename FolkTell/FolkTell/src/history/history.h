//#pragma once

#ifndef HISTORY_H
#define HISTORY_H


#include <QObject>

#include <QString>
#include <QString>
#include <QUrl>
#include <QDateTime>
#include <QHash>
#include "../webengine/webview.h"
//#include "historymodel.h"


/*
struct HistoryEntry{
    int id;
    QString title;
    QDateTime date;
    QUrl url;
    //for test
    
    int count;
    QDateTime date;
    QString urlString;
    QString title;
    
};
*/

#define HISTORY_ID_SEED 999


class HistoryModel;

struct HistoryEntry{
    uint id;
    QString title;
    QDateTime date;
    QUrl url;
    //for test
    /*
    int count;
    QDateTime date;
    QString urlString;
    QString title;
    */
};

class History:public QObject {
    Q_OBJECT
    public:
    explicit History(QObject* parent=nullptr);

    
    Q_SIGNALS:
    void historyEntryAdded(HistoryEntry& historyEntry);
    void historyEntryDeleted(HistoryEntry& historyEntry);
    //void historyEntryDeleted(HistoryEntry& historyEntry);
    void historyEntryCleared();

    public: //later it be changed to private
    HistoryModel* m_historyModel;

    



    public slots:
    void addHistoryEntry(WebView* webview);
    HistoryEntry makeHistoryEntry(const QString& title, const QUrl& url);
    void addHistoryEntryHelp(const QString& title,const QUrl& url);
    void deleteHistoryEntryHelp(const QString& title,const QUrl& url, const QDateTime& date);
    void clearHistoryEntryHelp();

};
#endif



/*
questions:
1, contains for reference type, do we need to override operator =
it has been solved 
2, contains for pointer child? and will it compare to the object ?
it has been solved
3, in findHistoryEntry how to check if equal for reference type
it has been solved
4, can't get the title of url
it has been solved
5, hard bug: how to guarantee the consistence for history title when titleChange emitted?
assigning title after loading finished or using signals and slot?
it has been solved

something to optimize:
1, when addHistoryEntry, it will execute findHistoryEntry which is linear time.
Maybe we can speed up.(This can be done after all functions have been finished).
2, for every user create a table

*/