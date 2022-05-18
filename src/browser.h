#ifndef BROWSER_H
#define BROWSER_H

#include "lib/service/service.h"

class QMenu;

class Config;

class DatabaseTaskScheduler;

class UserModel;

class BookmarkModel;

class History;

class DownloadManager;

class AdblockRequestInterceptor;

class Browser
{
public:

    explicit Browser(int userid, const MyServiceLocator &serviceLocator);
    virtual ~Browser() = default;
//    userid is default user id


public:
    int userid;
    const MyServiceLocator &m_serviceLocator;
    std::shared_ptr<Config> m_config;
    std::shared_ptr<DatabaseTaskScheduler> m_databaseScheduler;
    std::shared_ptr<UserModel> m_user;
    std::shared_ptr<BookmarkModel> m_bookmark;
    std::shared_ptr<History> m_history;
    std::shared_ptr<DownloadManager> m_downloadMgr;
    std::shared_ptr<AdblockRequestInterceptor> m_adblock;
};

#endif // BROWSER_H
