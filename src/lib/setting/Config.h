//
// Created by Howell Young on 2022/5/13.
//

#ifndef FOLKTELL_CONFIG_H
#define FOLKTELL_CONFIG_H

#include<QString>
#include<QSettings>
#include<QVariant>

class Config
{
public:
    Config(QString filename = "");
    virtual ~Config();
    void Set(QString, QVariant);
    QVariant Get(QString);

private:
    QString m_filename;
    QSettings *m_psetting;
};


#endif //FOLKTELL_CONFIG_H