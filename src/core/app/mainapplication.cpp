#include "src/core/app/mainapplication.h"
#include "adblock_request_interceptor.h"
#include "default_request_interceptor.h"
#include "bookmarkmodel.h"
#include "downloadmanager.h"
#include "core/useragent/useragent.h"
#include "history.h"
#include "../service/service.h"
#include "Config.h"
#include "homepage.h"
#include "databasetaskscheduler.h"
#include "usermodel.h"
#include "browserwindow.h"
#include <vector>
#include <string>
#include <QString>
#include <QWidget>
#define DEFAULT_USR_ID 1
#define DEFAULT_USR_NAME "default_usr"
#define DEFAULT_USR_PWD "123456"

MainApplication::MainApplication(int &argc, char **argv)
        : QApplication(argc, argv), defaultUsrId(DEFAULT_USR_ID) {
    m_config = std::make_shared<Config>();
    registerService("Config",m_config);

    m_databaseScheduler = std::make_shared<DatabaseTaskScheduler>();
    registerService("DatabaseTaskScheduler",m_databaseScheduler);
    m_databaseScheduler->run();

    m_user = std::make_shared<UserModel>(m_databaseScheduler);
    registerService("UserModel",m_user);
    initDefaultUser();

    m_bookmark = std::make_shared<BookmarkModel>(m_databaseScheduler);
    registerService("BookmarkModel",m_bookmark);

    //history store in memory, related to uid
    m_history = std::make_shared<History>(defaultUsrId, m_databaseScheduler);
    registerService("History",m_history);

    m_downloadMgr = std::make_shared<DownloadManager>();
    registerService("DownloadManager",m_downloadMgr);

    m_adblock = std::make_shared<AdblockRequestInterceptor>();
    registerService("AdblockRequestInterceptor", m_adblock);

    m_uaMgr = std::make_shared<UserAgentManager>();
    registerService("UserAgentManager", m_uaMgr);

    m_adblockRequest = new AdblockRequestInterceptor("../FolkTell/dependent_files/easylist.txt");
    m_defaultRequest = new DefaultRequestInterceptor();
}

void MainApplication::registerService(std::string keyType, std::shared_ptr<QObject> service) {
    if (!m_serviceLocator.addService(keyType, service))
        qWarning() << "Could not register " << QString::fromStdString(keyType) << " with service registry";
}

void MainApplication::initDefaultUser() {
    if (!(m_user->addRegisterUser(DEFAULT_USR_NAME, DEFAULT_USR_PWD))) {
        qDebug() << "init default user failed";
    }

}

std::shared_ptr<BrowserWindow> MainApplication::getNewWindow() {
    auto w = std::make_shared<BrowserWindow>(DEFAULT_USR_ID, m_serviceLocator, (QWidget * )nullptr);
    w->setAdblockRequestInterceptor(m_adblockRequest);
    w->setDefaultRequestInterceptor(m_defaultRequest);
    w->show();
    return w;
}

MainApplication::~MainApplication() {
    m_databaseScheduler->stop();
}
