#ifndef MAINAPPLICATION_H
#define MAINAPPLICATION_H

#include <QList>
#include <QPointer>
#include <QApplication>
#include "service.h"

class QMenu;

class Config;

class DatabaseTaskScheduler;

class UserModel;

class BookmarkModel;

class History;

class DownloadManager;

class AdblockRequestInterceptor;

class BrowserWindow;

class MainApplication : public QApplication {
public:
    explicit MainApplication(int &argc, char **argv);

    ~MainApplication();

    /// Registers a service with the MyServiceLocator
    void registerService(std::string keyType, std::shared_ptr<QObject> service);

    void initDefaultUser();

    /// Spawns and returns the pointer to a new browser window
    std::shared_ptr<BrowserWindow> getNewWindow();


private:
    MyServiceLocator m_serviceLocator;
    std::shared_ptr<Config> m_config;
    std::shared_ptr<DatabaseTaskScheduler> m_databaseScheduler;
    std::shared_ptr<UserModel> m_user;
    std::shared_ptr<BookmarkModel> m_bookmark;
    std::shared_ptr<History> m_history;
    std::shared_ptr<DownloadManager> m_downloadMgr;
    std::shared_ptr<AdblockRequestInterceptor> m_adblock;
    int defaultUsrId;

};

#endif // MAINAPPLICATION_H
