#include "browser.h"

Browser::Browser(int userid)
{
    m_taskScheduler = new DatabaseTaskScheduler();
    m_taskScheduler->run();
    this->userid = userid;
    this->baseHistory = new History(userid, std::shared_ptr<DatabaseTaskScheduler>(m_taskScheduler));
    //测试添加历史用
    WebView* webview = new WebView();
    webview->load(QUrl("https://baidu.com"));
    this->baseHistory->addHistoryEntry(webview);
}
