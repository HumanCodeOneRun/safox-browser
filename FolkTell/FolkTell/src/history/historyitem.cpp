#include "historyitem.h"

HistoryItem::HistoryItem(HistoryItem* _m_parent): m_parent(_m_parent)
{

}

void HistoryItem::prependChild(HistoryItem* child) {
    if(m_children.contains(child)) {
        m_children.removeAll(child);
    }
    child->m_parent = this;
    m_children.prepend(child);
}

int HistoryItem::getChildrenCount() {
    return m_children.count();
}

HistoryItem* HistoryItem::getChild(int index) {
    return m_children.at(index);
}

void HistoryItem::removeChild(HistoryItem* item) {
    m_children.removeAll(item);
}

void HistoryItem::clearChildren() {
    m_children.clear();
}

QList<HistoryItem*> HistoryItem::getChildren() {
    return m_children;
}