#ifndef BROWSER_H
#define BROWSER_H

#include <QObject>

class Browser : public QObject
{
    Q_OBJECT
public:
    explicit Browser(QObject *parent = nullptr);

signals:

};

#endif // BROWSER_H
