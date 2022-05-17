//
// Created by Howell Young on 2022/5/13.
//
#include "Config.h"

using namespace std;

#include <QtCore/QtCore>
#include <QDebug>

Config::Config(QString filename)
{
    if (m_filename.isEmpty())
    {
        m_filename = "Config.ini";
    }
    else
    {
        m_filename = filename;
    }

    m_psetting = new QSettings(m_filename, QSettings::IniFormat);
    qDebug() << "pppp" << m_filename << Qt::endl;
}

Config::~Config()
{
    delete m_psetting;
    m_psetting = NULL;
}

void Config::Set(QString qstrkeyname,QVariant qvarvalue)
{
    m_psetting->setValue(QString("/%1").arg(qstrkeyname), qvarvalue);
}

QVariant Config::Get(QString qstrkeyname) {
    QVariant qvar = m_psetting->value(QString("/%1").arg(qstrkeyname));
    return qvar;

}