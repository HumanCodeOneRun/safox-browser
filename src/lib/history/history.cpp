#include "history.h"
#include "historymodel.h"

History::History(const int& _userid, QObject* parent):
userid(_userid), QObject(parent)
{   
    m_historyDao = new HistoryDao(_userid, std::shared_ptr<DatabaseTaskScheduler>(m_taskScheduler));
    m_historyModel = new HistoryModel(this);
}

History::History(const int& _userid, DatabaseTaskScheduler* _m_taskscheduler, QObject* parent):
userid(_userid), QObject(parent), m_taskScheduler(_m_taskscheduler)
{   
    m_historyDao = new HistoryDao(_userid, std::shared_ptr<DatabaseTaskScheduler>(m_taskScheduler));
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
    HistoryDao* pm_historyDao = m_historyDao;
    HistoryModel* pm_historyModel = m_historyModel;
    m_taskScheduler->post([historyEntry, pm_historyDao, pm_historyModel] {
        qDebug()<<"[test] addhisotry entry ";
        pm_historyDao->insertHistoryEntry(historyEntry.urlid, historyEntry.title, historyEntry.url, historyEntry.iconUrl, historyEntry.date.toMSecsSinceEpoch());
        pm_historyModel->addHistoryEntry(historyEntry);
    });
};




void History::deleteHistoryEntryHelp(const QString& title, const QUrl& url, const QUrl& iconUrl, const QDateTime& date) {
    HistoryEntry historyEntry;
    historyEntry = makeHistoryEntry(title, url, iconUrl);
    historyEntry.date = date;
    HistoryDao* pm_historyDao = m_historyDao;
    HistoryModel* pm_historyModel = m_historyModel;
    m_taskScheduler->post([historyEntry, pm_historyDao, pm_historyModel] {
        pm_historyDao->deleteByPriKey(historyEntry.urlid, historyEntry.url);
        pm_historyModel->deleteHistoryEntry(historyEntry); 
    });


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
    HistoryDao* pm_historyDao = m_historyDao;
    HistoryModel* pm_historyModel = m_historyModel;
    m_taskScheduler->post([pm_historyDao, pm_historyModel] {
        pm_historyDao->clearTable();
        pm_historyModel->clearHistoryEntry();
    });
}

QList<qint64> History::queryDayTimestamp() {
    HistoryModel* pm_historyModel = m_historyModel;
    auto future = m_taskScheduler->post([this, pm_historyModel] {
        return pm_historyModel->queryDayTimestamp();
    });
    return future.get();
}

QList<HistoryEntry> History::queryDayHistoryEntry(const int index) {
    HistoryModel* pm_historyModel = m_historyModel;
    auto future = m_taskScheduler->post([this, pm_historyModel, index] {
        return pm_historyModel->queryDayHistoryEntry(index);
    });
    return future.get();
}

void History::deleteHistoryEntryHelp(const int dayIndex, const int entryIndex) {
    HistoryModel* pm_historyModel = m_historyModel;
    m_taskScheduler->post([pm_historyModel, dayIndex, entryIndex] {
        pm_historyModel->deleteHistoryEntry(dayIndex, entryIndex);
    });
}

HistoryDao* History::getHistoryDao() {
    return m_historyDao;
}

HistoryModel* History::getHistoryModel() {
    return m_historyModel;
}