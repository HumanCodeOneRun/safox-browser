#ifndef MAINAPPLICATION_H
#define MAINAPPLICATION_H
#include <QList>
#include <QPointer>
#include "qtsingleapplication.h"

class QMenu;

class MainApplication:public QtSingleApplication
{
public:
    explicit MainApplication(int &argc, char** argv);

};

#endif // MAINAPPLICATION_H
