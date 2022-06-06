/*
 * @Author: SC-WSKun 540610423@qq.com
 * @Date: 2022-05-23 13:23:38
 * @LastEditors: SC-WSKun 540610423@qq.com
 * @LastEditTime: 2022-05-26 00:37:35
 * @FilePath: \FolkTell\src\core\browser\browser.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include "browser.h"
#include "adblock_request_interceptor.h"
#include "default_request_interceptor.h"
#include "bookmarkmodel.h"
#include "downloadmanager.h"
#include "history.h"
#include "service.h"
#include "Config.h"
#include "homepage.h"
#include "databasetaskscheduler.h"
#include "usermodel.h"
#include "core/useragent/useragent.h"
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
        m_adblock(serviceLocator.getServiceAs<AdblockRequestInterceptor>("AdblockRequestInterceptor")),
        m_uaMgr(serviceLocator.getServiceAs<UserAgentManager>("UserAgentManager"))
        {

    //测试添加历史用
//    WebView *webview = new WebView();
//    webview->load(QUrl("https://doc.qt.io/qt-5/qwebengineview.html"));
//    m_history->addHistoryEntry(webview);

    this->Browser::m_bookmark->addBookmarkGroup(this->Browser::userid,"默认收藏夹",QUrl("www.testIcon.com"));

}

void Browser::changeUser(int newid){
    this->userid = newid;
    m_history->loginHistory(newid);
    this->Browser::m_bookmark->addBookmarkGroup(this->Browser::userid,"默认收藏夹",QUrl("www.testIcon.com"));
}

void Browser::setAdblockRequestInterceptor(AdblockRequestInterceptor* _m_adblockRequest) {
    m_adblockRequest = _m_adblockRequest;
}

void Browser::setDefaultRequestInterceptor(DefaultRequestInterceptor* _m_defaultRequest) {
    m_defaultRequest = _m_defaultRequest;
}