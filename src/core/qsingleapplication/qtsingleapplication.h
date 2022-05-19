#ifndef QTSINGLEAPPLICATION_H
#define QTSINGLEAPPLICATION_H

#include <QApplication>

class QtSingleApplication:public QApplication
{
    Q_OBJECT

public:
    QtSingleApplication(int &argc, char **argv, bool GUIenabled = true);
};

#endif // QTSINGLEAPPLICATION_H
