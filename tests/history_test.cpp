#include <ctime>
#include "historymodel.h"
#include <QApplication>
#include <QWebEngineView>

void addHistoryEntryTest(int user_id = 15) {
    qDebug()<<"addHistoryEntry Test";
    //int user_id = 15;
    auto scheduler = std::make_shared<DatabaseTaskScheduler>(2);
    scheduler->run();
    History* history = new History(user_id, scheduler);
    WebView* webview1 = new WebView();
    webview1->load(QUrl("https://www.scut.edu.cn/new/"));
    history->addHistoryEntry(webview1);
    WebView* webview2 = new WebView();
    webview2->load(QUrl("https://www.bilibili.com"));
    history->addHistoryEntry(webview2);
    WebView* webview3 = new WebView();
    webview3->load(QUrl("https://qzone.qq.com"));
    history->addHistoryEntry(webview3);
}


void queryDayTimestampTest(int user_id = 15) {
    qDebug()<<"queryDayTimestamp Test";
    //int user_id = 15;
    auto scheduler = std::make_shared<DatabaseTaskScheduler>(2);
    scheduler->run();
    History* history = new History(user_id, scheduler);
    qDebug()<<"dayTimestamp list: ";
    QList<qint64> dayTimestamp = history->queryDayTimestamp();
    for(int i=0; i<dayTimestamp.count(); i++) {
        qDebug()<<dayTimestamp[i];
    }
}

void deleteHistoryEntryHelpTest(int user_id = 15, const int dayIndex = 0, const int entryIndex = 0) {
    qDebug()<<"deleteHistoryEntryHelp Test";
    //int user_id = 15;
    auto scheduler = std::make_shared<DatabaseTaskScheduler>(2);
    scheduler->run();
    History* history = new History(user_id, scheduler);
    history->deleteHistoryEntryHelp(dayIndex, entryIndex);
    history->getHistoryModel()->traverse();
}

void clearHistoryEntryHelpTest(int user_id = 15) {
    qDebug()<<"clearHistoryEntryHelp Test";
    //int user_id = 15;
    auto scheduler = std::make_shared<DatabaseTaskScheduler>(2);
    scheduler->run();
    History* history = new History(user_id, scheduler);
    history->clearHistoryEntryHelp();
    history->getHistoryModel()->traverse();
}

void queryDayHistoryEntryHelpTest(int user_id = 15, const int dayIndex = 0) {
    qDebug()<<"queryDayHistoryEntryHelp Test";
    //int user_id = 15;
    auto scheduler = std::make_shared<DatabaseTaskScheduler>(2);
    scheduler->run();
    History* history = new History(user_id, scheduler);
    QList<HistoryEntry> dayHistoryEntry = history->queryDayHistoryEntry(dayIndex);
    for(int i=0; i<dayHistoryEntry.count(); i++) {
        qDebug()<<dayHistoryEntry[i].title;
    }
}

void loginHistoryTest(int user_id1 = 15, int user_id2 = 16) {
    qDebug()<<"loginHistory Test";
    //int user_id1 = 16;
    auto scheduler = std::make_shared<DatabaseTaskScheduler>(2);
    scheduler->run();
    History* history = new History(user_id1, scheduler);
    history->getHistoryModel()->traverse();

    //int user_id2 = 15;
    history->loginHistory(user_id2);
    history->getHistoryModel()->traverse();

    history->loginHistory(user_id1);
    history->getHistoryModel()->traverse();
}

int main(int argc, char** argv){
    QApplication app(argc, argv);
    loginHistoryTest();
    return app.exec();
}