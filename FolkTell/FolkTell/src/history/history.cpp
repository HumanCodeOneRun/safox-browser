#include "history.h"
#include "historymodel.h"

History::History(QObject* parent):
QObject(parent)
{
    m_historyModel = new HistoryModel(this);   
}

void History::addHistoryEntry(WebView* webview) {
    const QString title = webview->getTitle();
    const QUrl url = webview->getUrl();
    if(webview->getConnectedToHistory() == 0) {
        webview->setConnectedToHistory(1);
        QObject::connect(webview, &WebView::sendChangedWebView, this, &History::addHistoryEntry);
    }
    
    if(url.toString() != "")
        addHistoryEntryHelp(title, url);
}

void History::addHistoryEntryHelp(const QString& title, const QUrl& url) {
    HistoryEntry historyEntry;
    historyEntry = makeHistoryEntry(title, url);
    /*
    code for database
    */
    emit(historyEntryAdded(historyEntry));
};

/*
void History::deleteHistoryEntry(WebView* webview) {
    const QString title = webview->getTitle();
    const QUrl url = webview->getUrl();
    if(url.toString() != "")
        deleteHistoryEntryHelp(title, url);
}
*/


void History::deleteHistoryEntryHelp(const QString& title, const QUrl& url, const QDateTime& date) {
    HistoryEntry historyEntry;
    historyEntry = makeHistoryEntry(title, url);
    historyEntry.date = date;
    /*
    code for database to delete
    */
   emit(historyEntryDeleted(historyEntry));
}




HistoryEntry History::makeHistoryEntry(const QString& title, const QUrl& url) {
    HistoryEntry historyEntry;
    historyEntry.title = title;
    historyEntry.url = url;
    historyEntry.date = QDateTime::currentDateTime();
    historyEntry.id = qHash( url.toString(), HISTORY_ID_SEED);
    return historyEntry;
}

void History::clearHistoryEntryHelp() {
    /*
    code for database
    */
    emit(historyEntryCleared());
}