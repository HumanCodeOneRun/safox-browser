
#ifndef HISTORYITEM_H
#define HISTORYITEM_H

#include <QtCore/QDateTime>
#include <QtCore/QUrl>
#include "history.h"





class HistoryItem
{
    public:
    HistoryItem(HistoryItem* _m_parent);
    //HistoryEntry historyEntry; //may be it should be changed to private
    void prependChild(HistoryItem* child);
    int getChildrenCount();
    HistoryItem* getChild(int index);
    void removeChild(HistoryItem* item);
    void clearChildren();
    QList<HistoryItem*> getChildren();

    //set and get private member
    qint64 getEndTimestamp();
    void setEndTimestamp(const qint64 _m_endTimestamp);
    HistoryItem* getParent();
    void setHistoryEntry(const HistoryEntry historyEntry);
    HistoryEntry getHistoryEntry();


    //private:
    private://should changed to private later
    HistoryItem* m_parent;
    QList<HistoryItem*> m_children;
    qint64 m_startTimestamp;
    qint64 m_endTimestamp;
    HistoryEntry historyEntry;

};

#endif