#include "mainapplication.h"
#include "adblock_request_interceptor.h"
#include "bookmarkmodel.h"
#include "downloadmanager.h"
#include "history.h"
#include "service.h"
#include "Config.h"
#include "homepage.h"
#include "databasetaskscheduler.h"
#include "usermodel.h"
#include <cmath>
#include <vector>
#define DEFAULT_USR_ID 1
#define DEFAULT_USR_NAME "default_usr"
#define DEFAULT_USR_PWD "123456"

MainApplication::MainApplication(int &argc, char** argv)
    : QApplication(argc, argv), defaultUsrId(DEFAULT_USR_ID)
{
    m_config = std::make_shared<Config>();
    registerService(m_config);

    m_databaseScheduler = std::make_shared<DatabaseTaskScheduler>();
    registerService(m_databaseScheduler);

    m_user = std::make_shared<UserModel>(m_databaseScheduler);
    registerService(m_user);
    initDefaultUser();

    m_bookmark = std::make_shared<BookmarkModel>(m_databaseScheduler);
    registerService(m_bookmark);


    //history store in memory, related to uid
    m_history = std::make_shared<History>(defaultUsrId, m_databaseScheduler);
    registerService(m_history);

    m_downloadMgr = std::make_shared<DownloadManager>();
    registerService(m_downloadMgr);

    m_adblock = std::make_shared<AdblockRequestInterceptor>();
    registerService(m_adblock);

    m_databaseScheduler->run();





}
void MainApplication::registerService(std::shared_ptr<QObject>service){
    if (!m_serviceLocator.addService(service->objectName().toStdString(), service))
        qWarning() << "Could not register " << service->objectName() << " with service registry";
}

void MainApplication::initDefaultUser() {
    if(!(m_user->addRegisterUser(DEFAULT_USR_NAME, DEFAULT_USR_PWD))) {
        qDebug()<<"init default user failed";
    }

}