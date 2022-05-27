
//
// Created by Howell Young on 2022/5/13.
//

#ifndef safox_CONFIG_H
#define safox_CONFIG_H

#include<QString>
#include<QSettings>
#include<QVariant>

class Config : public QObject {
public:
    Config(QString filename = "");

    virtual ~Config();

    void Set(QString, QVariant);

    QVariant Get(QString);

    void Delete(QString);

private:
    QString m_filename;
    QSettings *m_psetting;
};


#endif //safox_CONFIG_H

