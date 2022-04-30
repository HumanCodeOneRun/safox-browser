

#include "historymodel.h"


void HistoryModel::init() {
    //use database to load the data structure
}


HistoryModel::HistoryModel(History *history) : QStandardItemModel(history),
m_rootItem(new HistoryItem(NULL)), m_history(history)
{
    m_todayItem = nullptr;
    init();
    connect(m_history, &History::historyEntryAdded, this, &HistoryModel::addHistoryEntry);
    connect(m_history, &History::historyEntryDeleted, this, &HistoryModel::deleteHistoryEntry);
    connect(m_history, &History::historyEntryCleared, this, &HistoryModel::clearHistoryEntry);
}

void HistoryModel::addHistoryEntry(HistoryEntry& historyEntry) {
    if(m_todayItem == nullptr) {
        m_todayItem = new HistoryItem(NULL);
        m_rootItem->prependChild(m_todayItem);
        m_todayItem->historyEntry.title = "todayItem";
        m_todayItem->m_endTimestamp = (QDateTime::currentDateTime()).toMSecsSinceEpoch();
    }
    deleteHistoryEntry(historyEntry);//for adding no repeated element

    HistoryItem* historyItem = new HistoryItem(NULL);
    historyItem->historyEntry = historyEntry;
    historyItem->m_endTimestamp = (QDateTime::currentDateTime()).toMSecsSinceEpoch();
    m_todayItem->prependChild(historyItem);
    //traverse();//test
}


HistoryItem* HistoryModel::findHistoryItem(const HistoryEntry& historyEntry) {
    HistoryItem* item;
    HistoryItem* dayItem;
    qint64 timestamp = historyEntry.date.toMSecsSinceEpoch();
    for(int i=0; i<m_rootItem->getChildrenCount(); i++) {
        dayItem = m_rootItem->getChild(i);
        
        if(dayItem->m_endTimestamp <= timestamp) {
            break;
        }    
    }
    
    if(dayItem == NULL) {
        return NULL;//the historyEntry is not found
    }
    for(int i=0; i<dayItem->getChildrenCount(); i++) {
        item = dayItem->getChild(i);
        if(historyEntry.id == item->historyEntry.id) {
            return item;
        }
    }
    return NULL;

}

void HistoryModel::deleteHistoryEntry(HistoryEntry& historyEntry) {
    //qDebug()<<"test1 delete in historymodel title "<<historyEntry.title;
    HistoryItem* item = findHistoryItem(historyEntry);
    //qDebug()<<"test2 delte in historymodel";
    //traverse();
    if(item == NULL)
        return;//the entry is not found
    //qDebug()<<"test3 delte in historymodel";
    HistoryItem* m_parent = item->m_parent;
    //qDebug()<<"test4 delte in historymodel";
    m_parent->removeChild(item);
    //qDebug()<<"test5 delte in historymodel";
    //qDebug()<<"delete traverse happens";
    traverse();
}

void HistoryModel::clearHistoryEntry() {
    //qDebug()<<"clear test1";
    for(int i=0; i<m_rootItem->getChildrenCount(); i++) {
        HistoryItem* dayItem = m_rootItem->getChild(i);
        dayItem->clearChildren();
        delete dayItem;
    }
    m_rootItem->clearChildren();
    m_todayItem = nullptr;
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
            std::cout<<"id: "<< item->historyEntry.id<<"  endTimestamp: "<<item->m_endTimestamp<<"title: "<<item->historyEntry.title.toStdString()<<std::endl;
        }
        std::cout<<"..........."<<std::endl;
    }
    std::cout<<"traverse() exit"<<std::endl;
}