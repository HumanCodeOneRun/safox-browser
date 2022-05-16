#include "browser.h"

Browser::Browser(int userid)
{
    m_taskScheduler = new DatabaseTaskScheduler();
    m_taskScheduler->run();
    this->userid = userid;
    this->baseHistory = new History(userid, m_taskScheduler);
}
