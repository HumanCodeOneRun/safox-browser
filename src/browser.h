#ifndef BROWSER_H
#define BROWSER_H

#include "lib/history/history.h"
#include "lib/taskscheduler/databasetaskscheduler.h"

class Browser
{
public:
    explicit Browser(int userid);
    int userid;
    DatabaseTaskScheduler dts;
    History* baseHistory;
signals:

};

#endif // BROWSER_H
