#ifndef HISTORYMODEL_H
#define HISTORYMODEL_H
#include <QtCore/QDateTime>
#include <QtCore/QUrl>
#include <QtGui/QStandardItemModel>

//lib used for testing  
#include <iostream>
#include "historyitem.h"
#include <Qt>




class HistoryModel final : public QStandardItemModel
{
    Q_OBJECT
    public:
    enum Roles {
        IdRole = Qt::UserRole + 1,
        TitleRole = Qt::UserRole + 2,
        DateRole = Qt::UserRole + 3,
        UrlRole = Qt::UserRole + 4
    };


    public:
        explicit HistoryModel(History* history);
        void init();
        
    
    public slots:
        void addHistoryEntry(HistoryEntry& historyEntry);
        HistoryItem* findHistoryItem(const HistoryEntry& historyEntry);
        void deleteHistoryEntry(HistoryEntry& historyEntry);//just for adding no repeated element
        void deleteHistoryEntry(const int dayIndex, const int entryIndex);
        void clearHistoryEntry();
        QList<qint64> queryDayTimestamp();
        QList<HistoryEntry> queryDayHistoryEntry(const int index);

    private://later change to private
        HistoryItem* m_rootItem;
        HistoryItem* m_todayItem;
        History* m_history;
    
    //test code
    public:
        static void test();
        void traverse();
        void getRootChildrenNum();

    
        
};  

#endif 


/*
by cuddly

notice:
1, when comes to multiple users, we can store all user_id in a table such as users_id, 
and create history_user_id table to restore the data about the history for one spectific user
2, the id in historyEntry is a identifier of Entry and maybe we can hash url to generate it



*/