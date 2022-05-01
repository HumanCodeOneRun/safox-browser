
#include <time.h>
#include <stdlib.h>
#include "historymodel.h"
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>

void HistoryModel::init() {
    //use database to load the data structure
    QDateTime today = QDateTime::currentDateTime();
    QList<qint64> dayTimestamp = m_history->m_historyDao->queryDayTimestamp();
    for(int i=0; i<dayTimestamp.count(); i++) {
        HistoryItem* dayItem = new HistoryItem(NULL);
        dayItem->m_endTimestamp = dayTimestamp[i];
        m_rootItem->prependChild(dayItem);
        if(i == dayTimestamp.count() - 1) {
            QDateTime day = QDateTime::fromMSecsSinceEpoch(dayTimestamp[i]);
            if(day.daysTo(today) == 0) {
                m_todayItem = dayItem;
            }
        }
    }

    QList<HistoryEntry> historyEntrys = m_history->m_historyDao->queryHistoryEntry();
    for(int i=0; i<historyEntrys.count(); i++) {
        HistoryItem* historyItem = new HistoryItem(NULL);
        historyItem->historyEntry = historyEntrys[i];
        qint64 timestamp = historyEntrys[i].date.toMSecsSinceEpoch();
        historyItem->m_endTimestamp = timestamp;

        QList<HistoryItem*> dayItems = m_rootItem->getChildren();
        for(int i=0; i<dayItems.count(); i++) {
            HistoryItem* dayItem = dayItems[i];
            if(dayItem->m_endTimestamp <= timestamp) {
                dayItem->prependChild(historyItem);
                break;
            }
        }
    }

}


HistoryModel::HistoryModel(History *history) : QStandardItemModel(history),
m_rootItem(new HistoryItem(NULL)), m_history(history)
{
    srand(time(0));//for generate the todayItem id
    m_todayItem = nullptr;
    init();
    connect(m_history, &History::historyEntryAdded, this, &HistoryModel::addHistoryEntry);
    //connect(m_history, &History::historyEntryDeleted, this, &HistoryModel::deleteHistoryEntry); //if use deleteHistoryEntry(HistoryEntry&) please open connect
    connect(m_history, &History::historyEntryCleared, this, &HistoryModel::clearHistoryEntry);
}

void HistoryModel::addHistoryEntry(HistoryEntry& historyEntry) {
    if(m_todayItem == nullptr) {
        m_todayItem = new HistoryItem(NULL);
        m_rootItem->prependChild(m_todayItem);
        HistoryEntry& historyEntry = m_todayItem->historyEntry;
        historyEntry.url = QUrl("todayItem");
        historyEntry.urlid = rand(); 
        historyEntry.title = "todayItem";
        historyEntry.iconUrl = QUrl("todayItem");
        historyEntry.date = (QDateTime::currentDateTime());
        m_todayItem->m_endTimestamp = historyEntry.date.toMSecsSinceEpoch();
        m_history->m_historyDao->insertHistoryEntry(historyEntry.urlid, historyEntry.title, historyEntry.url, historyEntry.iconUrl, m_todayItem->m_endTimestamp);

    }
    deleteHistoryEntry(historyEntry);//for adding no repeated element

    HistoryItem* historyItem = new HistoryItem(NULL);
    historyItem->historyEntry = historyEntry;
    historyItem->m_endTimestamp = (QDateTime::currentDateTime()).toMSecsSinceEpoch();
    m_todayItem->prependChild(historyItem);
}


HistoryItem* HistoryModel::findHistoryItem(const HistoryEntry& historyEntry) {
    HistoryItem* item;
    HistoryItem* dayItem;
    qint64 timestamp = historyEntry.date.toMSecsSinceEpoch();
    for(int i=0; i<m_rootItem->getChildrenCount(); i++) {
        dayItem = m_rootItem->getChild(i);
        /*
        if(dayItem->m_endTimestamp <= timestamp) {
            break;
        }
        */
        for(int j=0; j<dayItem->getChildrenCount(); j++) {
            item = dayItem->getChild(j);
            if(historyEntry.urlid == item->historyEntry.urlid) {
                return item;
            }
        } 
    }
    /*
    if(dayItem == NULL) {
        return NULL;//the historyEntry is not found
    }
    for(int i=0; i<dayItem->getChildrenCount(); i++) {
        item = dayItem->getChild(i);
        if(historyEntry.urlid == item->historyEntry.urlid) {
            return item;
        }
    }
    */
    
    return NULL;

}

void HistoryModel::deleteHistoryEntry(HistoryEntry& historyEntry) {
    HistoryItem* item = findHistoryItem(historyEntry);
    if(item == NULL)
        return;//the entry is not found
    HistoryItem* m_parent = item->m_parent;
    m_parent->removeChild(item);
}

void HistoryModel::deleteHistoryEntry(const int dayIndex, const int entryIndex) {
    HistoryItem* dayItem = m_rootItem->getChild(dayIndex);
    if(entryIndex >= dayItem->getChildrenCount()) {
        qDebug()<<"[error] entryIndex out of range when deleteHistoryEntry";
        return;
    }
    HistoryItem* historyItem = dayItem->getChild(entryIndex);
    HistoryEntry historyEntry = historyItem->historyEntry;
    m_history->m_historyDao->deleteByPriKey(historyEntry.urlid, historyEntry.url);
    dayItem->removeChild(historyItem);
}

void HistoryModel::clearHistoryEntry() {
    for(int i=0; i<m_rootItem->getChildrenCount(); i++) {
        HistoryItem* dayItem = m_rootItem->getChild(i);
        dayItem->clearChildren();
        delete dayItem;
    }
    m_rootItem->clearChildren();
    m_todayItem = nullptr;
}

QList<qint64> HistoryModel::queryDayTimestamp() {
    QList<qint64> ret;
    QList<HistoryItem*> dayItems = m_rootItem->getChildren();
    for(int i=0; i<dayItems.count(); i++) {
        ret.append(dayItems[i]->m_endTimestamp);
    }
    return ret;
}

QList<HistoryEntry> HistoryModel::queryDayHistoryEntry(const int index) {
    QList<HistoryEntry> ret;
    HistoryItem* dayItem = m_rootItem->getChild(index);
    QList<HistoryItem*> children = dayItem->getChildren();
    for(int i=0; i<children.count(); i++) {
        ret.append(children[i]->historyEntry);
    }
    return ret;
}

//for test code
void HistoryModel::test() {
    std::cout<<"hello test in HistoryModel"<<std::endl;
}

void HistoryModel::getRootChildrenNum() {
    std::cout<<"test in rootChildrenNum(): "<<m_rootItem->getChildrenCount()<<std::endl;

}

void HistoryModel::traverse() {
    std::cout<<"traverse() begin"<<std::endl;
    for(int i=0; i<m_rootItem->getChildrenCount(); i++) {
        HistoryItem* historyItem = m_rootItem->m_children.at(i);
        std::cout<<"list: "<<i<<std::endl;
        std::cout<<"list endTimestamp: "<<historyItem->m_endTimestamp<<std::endl;
        for(int j=0; j<historyItem->getChildrenCount(); j++) {
            HistoryItem* item = historyItem->m_children.at(j);
            std::cout<<"id: "<< item->historyEntry.urlid<<"  endTimestamp: "<<item->m_endTimestamp<<" title: "<<item->historyEntry.title.toStdString()<<std::endl;
        }
        std::cout<<"..........."<<std::endl;
    }
    std::cout<<"traverse() exit"<<std::endl;
}

