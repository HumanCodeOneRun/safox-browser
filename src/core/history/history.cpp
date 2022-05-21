#include "history.h"
#include "historymodel.h"



History::History(const int &_userid, std::shared_ptr<DatabaseTaskScheduler>_m_taskscheduler, QObject *parent) :
    QObject(parent), m_taskScheduler(_m_taskscheduler) {
    m_historyDao = std::make_shared<HistoryDao>(_userid, std::shared_ptr<DatabaseTaskScheduler>(m_taskScheduler));
    m_historyModel = std::make_shared<HistoryModel>(this);

    create_table();
}

void History::create_table(){
    m_taskScheduler->post([this](){
        this->m_historyDao->createTable();
    });
}

void History::addHistoryEntry(WebView *webview) {
    const QString title = webview->getTitle();
    const QUrl url = webview->getUrl();
    const QUrl iconUrl = webview->getUrl();
    if (webview->getConnectedToHistory() == 0) {
        webview->setConnectedToHistory(1);
        QObject::connect(webview, &WebView::sendChangedWebView, this, &History::addHistoryEntry);
    }
    if (url.toString() != "")
        addHistoryEntryHelp(title, url, iconUrl);
}

void History::addHistoryEntryHelp(const QString &title, const QUrl &url, const QUrl &iconUrl) {
    HistoryEntry historyEntry;
    historyEntry = makeHistoryEntry(title, url, iconUrl);
    std::shared_ptr<HistoryDao> pm_historyDao = m_historyDao;
    std::shared_ptr<HistoryModel> pm_historyModel = m_historyModel;
    m_taskScheduler->post([historyEntry, pm_historyDao, pm_historyModel] {
        qDebug() << "[test] addhisotry entry ";
        pm_historyDao->insertHistoryEntry(historyEntry.urlid, historyEntry.title, historyEntry.url,
                                          historyEntry.iconUrl, historyEntry.date.toMSecsSinceEpoch());
        pm_historyModel->addHistoryEntry(historyEntry);
    });
}


void
History::deleteHistoryEntryHelp(const QString &title, const QUrl &url, const QUrl &iconUrl, const QDateTime &date) {
    HistoryEntry historyEntry;
    historyEntry = makeHistoryEntry(title, url, iconUrl);
    historyEntry.date = date;
    std::shared_ptr<HistoryDao> pm_historyDao = m_historyDao;
    std::shared_ptr<HistoryModel> pm_historyModel = m_historyModel;
    m_taskScheduler->post([historyEntry, pm_historyDao, pm_historyModel] {
        pm_historyDao->deleteByPriKey(historyEntry.urlid, historyEntry.url);
        pm_historyModel->deleteHistoryEntry(historyEntry);
    });


}

HistoryEntry History::makeHistoryEntry(const QString &title, const QUrl &url, const QUrl &iconUrl) {
    HistoryEntry historyEntry;
    historyEntry.title = title;
    historyEntry.url = url;
    historyEntry.date = QDateTime::currentDateTime();
    historyEntry.iconUrl = iconUrl;
    historyEntry.urlid = qHash(url.toString(), HISTORY_ID_SEED);
    return historyEntry;
}

void History::clearHistoryEntryHelp() {
    std::shared_ptr<HistoryDao> pm_historyDao = m_historyDao;
    std::shared_ptr<HistoryModel> pm_historyModel = m_historyModel;
    m_taskScheduler->post([pm_historyDao, pm_historyModel] {
        pm_historyDao->clearTable();
        pm_historyModel->clearHistoryEntry();
    });
}


#if defined(__clang__) || defined(__GNUC__)
QList<qint64> History::queryDayTimestamp() {
    std::shared_ptr<HistoryModel> pm_historyModel = m_historyModel;
    auto future = m_taskScheduler->post([this, pm_historyModel] {
        return pm_historyModel->queryDayTimestamp();
    });
    return future.get();
}

QList<HistoryEntry> History::queryDayHistoryEntry(const int index) {
    std::shared_ptr<HistoryModel> pm_historyModel = m_historyModel;
    auto future = m_taskScheduler->post([this, pm_historyModel, index] {
        return pm_historyModel->queryDayHistoryEntry(index);
    });
    return future.get();
}
#endif

#if defined(_MSC_VER)
QList<qint64> History::queryDayTimestamp() {
    std::promise<QList<qint64>> pm;
    auto future = pm.get_future();

    std::shared_ptr<HistoryModel> pm_historyModel = m_historyModel;
    m_taskScheduler->post([this, &pm, pm_historyModel] {
        pm.set_value(pm_historyModel->queryDayTimestamp());
    });
    return future.get();
}

QList<HistoryEntry> History::queryDayHistoryEntry(const int index) {
    std::promise<QList<HistoryEntry>> pm;
    auto future = pm.get_future();

    std::shared_ptr<HistoryModel> pm_historyModel = m_historyModel;
    m_taskScheduler->post([this, &pm, pm_historyModel, index] {
        pm.set_value(pm_historyModel->queryDayHistoryEntry(index));
    });
    return future.get();
}
#endif
void History::deleteHistoryEntryHelp(const int dayIndex, const int entryIndex) {
    std::shared_ptr<HistoryModel> pm_historyModel = m_historyModel;
    m_taskScheduler->post([pm_historyModel, dayIndex, entryIndex] {
        pm_historyModel->deleteHistoryEntry(dayIndex, entryIndex);
    });
}

std::shared_ptr<HistoryDao> History::getHistoryDao() {
    return m_historyDao;
}

std::shared_ptr<HistoryModel> History::getHistoryModel() {
    return m_historyModel;
}