#ifndef MAINAPPLICATION_H
#define MAINAPPLICATION_H
#include <QList>
#include <QPointer>
#include <QApplication>

class QMenu;

class MainApplication:QApplication
{
public:
    explicit MainApplication(int &argc, char** argv);

};

#endif // MAINAPPLICATION_H
