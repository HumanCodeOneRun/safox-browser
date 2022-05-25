#include "browser.h"
#include "adblock_request_interceptor.h"
#include "bookmarkmodel.h"
#include "downloadmanager.h"
#include "history.h"
#include "service.h"
#include "Config.h"
#include "homepage.h"
#include "databasetaskscheduler.h"
#include "usermodel.h"
#include <QDebug>
Browser::Browser(int userid, const MyServiceLocator &serviceLocator) :
        userid(userid),
        m_serviceLocator(serviceLocator),
        m_config(serviceLocator.getServiceAs<Config>("Config")),
        m_databaseScheduler(serviceLocator.getServiceAs<DatabaseTaskScheduler>("DatabaseTaskScheduler")),
        m_user(serviceLocator.getServiceAs<UserModel>("UserModel")),
        m_bookmark(serviceLocator.getServiceAs<BookmarkModel>("BookmarkModel")),
        m_history(serviceLocator.getServiceAs<History>("History")),
        m_downloadMgr(serviceLocator.getServiceAs<DownloadManager>("DownloadManager")),
        m_adblock(serviceLocator.getServiceAs<AdblockRequestInterceptor>("AdblockRequestInterceptor")) {

////    query测试

    bool isExist1 = m_user->queryUserName("kunkun33333");
    qDebug()<<"3333测试："<<isExist1;
    
// add测试
    m_user->addRegisterUser("kunkuntest","kunkunpassword");

    bool isExist = m_user->queryUserName("kunkuntest");
    qDebug()<<"test测试："<<isExist;

    bool canLog = m_user->queryUserPassword("kunkuntest","kunkunpassword");
    if(!canLog){
        qDebug()<<"queryUserPassword测试："<<canLog;

    }
    int newid = m_user->getUserIdByName("kunkuntest");
    changeUser(newid);
    qDebug()<<"newid："<<this->userid;

    //测试添加历史用
    WebView *webview = new WebView();
    webview->load(QUrl("https://doc.qt.io/qt-5/qwebengineview.html"));
    m_history->addHistoryEntry(webview);

}

void Browser::changeUser(int newid){
    this->userid = newid;
    m_history->loginHistory(newid);
}
