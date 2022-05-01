#include "history.h"
#include "historymodel.h"

History::History(const int& _userid, QObject* parent):
userid(_userid), QObject(parent)
{   
    m_historyDao = new HistoryDao(_userid);
    m_historyModel = new HistoryModel(this);
}

void History::addHistoryEntry(WebView* webview) {
    const QString title = webview->getTitle();
    const QUrl url = webview->getUrl();
    const QUrl iconUrl = webview->getUrl();
    if(webview->getConnectedToHistory() == 0) {
        webview->setConnectedToHistory(1);
        QObject::connect(webview, &WebView::sendChangedWebView, this, &History::addHistoryEntry);
    }
    
    if(url.toString() != "")
        addHistoryEntryHelp(title, url, iconUrl);
}

void History::addHistoryEntryHelp(const QString& title, const QUrl& url, const QUrl& iconUrl) {
    HistoryEntry historyEntry;
    historyEntry = makeHistoryEntry(title, url, iconUrl);
    //code for database
    m_historyDao->insertHistoryEntry(historyEntry.urlid, historyEntry.title, historyEntry.url, historyEntry.iconUrl, historyEntry.date.toMSecsSinceEpoch());
    
    emit(historyEntryAdded(historyEntry));
};




void History::deleteHistoryEntryHelp(const QString& title, const QUrl& url, const QUrl& iconUrl, const QDateTime& date) {
    HistoryEntry historyEntry;
    historyEntry = makeHistoryEntry(title, url, iconUrl);
    historyEntry.date = date;
    //code for database to delete
   m_historyDao->deleteByPriKey(historyEntry.urlid, historyEntry.url);
   emit(historyEntryDeleted(historyEntry));
}

HistoryEntry History::makeHistoryEntry(const QString& title, const QUrl& url, const QUrl& iconUrl) {
    HistoryEntry historyEntry;
    historyEntry.title = title;
    historyEntry.url = url;
    historyEntry.date = QDateTime::currentDateTime();
    historyEntry.iconUrl = iconUrl;
    historyEntry.urlid = qHash( url.toString(), HISTORY_ID_SEED);
    return historyEntry;
}

void History::clearHistoryEntryHelp() {
    //code for database
    m_historyDao->clearTable();
    emit(historyEntryCleared());
}

QList<qint64> History::queryDayTimestamp() {
    return m_historyModel->queryDayTimestamp();
}

QList<HistoryEntry> History::queryDayHistoryEntry(const int index) {
    return m_historyModel->queryDayHistoryEntry(index);
}

void History::deleteHistoryEntryHelp(const int dayIndex, const int entryIndex) {
    m_historyModel->deleteHistoryEntry(dayIndex, entryIndex);
}

HistoryDao* History::getHistoryDao() {
    return m_historyDao;
}

HistoryModel* History::getHistoryModel() {
    return m_historyModel;
}