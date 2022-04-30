#ifndef JSONSETTING_H
#define JSONSETTING_H


#include <QtCore/QJsonDocument>
#include <QtCore/QRect>


class JsonSettings final : public QJsonDocument
{
public:
    explicit JsonSettings();
    explicit JsonSettings(const QString &path);

    void setComment(const QString &comment);
    static QRect readRectangle(const QVariant &value);
    static QPoint readPoint(const QVariant &value);
    static QSize readSize(const QVariant &value);
    QString getComment() const;
    bool save(const QString &path = {}, bool isAtomic = true);
    bool hasError() const;

private:
    QString m_path;
    QString m_comment;
    bool m_hasError;
};



#endif // JSONSETTING_H
