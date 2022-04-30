
#include "HistoryModel.h"
#include "Console.h"
#include "JsonSettings.h"
//#include "SessionsManager.h"
//#include "ThemesManager.h"
#include "Utils.h"

#include <QtCore/QFile>
#include <QtCore/QJsonArray>
#include <QtCore/QJsonObject>
#include <QApplication>

HistoryModel::Entry::Entry() = default;

void HistoryModel::Entry::setData(const QVariant &value, int role)
{
    if (model() && qobject_cast<HistoryModel*>(model()))
    {
        model()->setData(index(), value, role);
    }
    else
    {
        QStandardItem::setData(value, role);
    }
}

void HistoryModel::Entry::setItemData(const QVariant &value, int role)
{
    QStandardItem::setData(value, role);
}

QString HistoryModel::Entry::getTitle() const
{
    return (data(TitleRole).isNull() ? "untitled" : data(TitleRole).toString());
}

QUrl HistoryModel::Entry::getUrl() const
{
    return data(UrlRole).toUrl();
}

QDateTime HistoryModel::Entry::getTimeVisited() const
{
    return data(TimeVisitedRole).toDateTime();
}

QIcon HistoryModel::Entry::getIcon() const
{
    const QVariant iconData(data(Qt::DecorationRole));

    return (iconData.isNull() ? QIcon(): iconData.value<QIcon>());
}

quint64 HistoryModel::Entry::getIdentifier() const
{
    return data(IdentifierRole).toULongLong();
}

HistoryModel::HistoryModel(const QString &path, HistoryType type, QObject *parent) : QStandardItemModel(parent),
    m_type(type)
{
    QFile file(path);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        Console::addMessage(tr("Failed to open history file: %1").arg(file.errorString()), Console::OtherCategory, Console::ErrorLevel, path);//读本地历史记录

        return;
    }

    const QJsonArray historyArray(QJsonDocument::fromJson(file.readAll()).array());

    file.close();

    for (int i = 0; i < historyArray.count(); ++i)
    {
        const QJsonObject entryObject(historyArray.at(i).toObject());
        QDateTime dateTime(QDateTime::fromString(entryObject.value(QLatin1String("time")).toString(), Qt::ISODate));
        dateTime.setTimeSpec(Qt::UTC);

        addEntry(QUrl(entryObject.value(QLatin1String("url")).toString()), entryObject.value(QLatin1String("title")).toString(), {}, dateTime);
    }

    setSortRole(TimeVisitedRole);//按时间排序
    sort(0, Qt::DescendingOrder);
}

void HistoryModel::clearExcessEntries(int limit)
{
    if (limit > 0 && rowCount() > limit)
    {
        for (int i = (rowCount() - 1); i >= limit; --i)
        {
            removeEntry(index(i, 0).data(IdentifierRole).toULongLong());
        }
    }
}

void HistoryModel::clearRecentEntries(uint period)
{
    if (period == 0)
    {
        clear();

        m_urls.clear();
        m_identifiers.clear();

        emit cleared();

        return;
    }

    for (int i = (rowCount() - 1); i >= 0; --i)
    {
        if (index(i, 0).data(TimeVisitedRole).toDateTime().secsTo(QDateTime::currentDateTimeUtc()) < (period * 3600))
        {
            removeEntry(index(i, 0).data(IdentifierRole).toULongLong());
        }
    }
}

void HistoryModel::clearOldestEntries(int period)
{
    if (period < 0)
    {
        return;
    }

    const QDateTime currentDateTime(QDateTime::currentDateTimeUtc());

    for (int i = (rowCount() - 1); i >= 0; --i)
    {
        if (index(i, 0).data(TimeVisitedRole).toDateTime().daysTo(currentDateTime) > period)
        {
            removeEntry(index(i, 0).data(IdentifierRole).toULongLong());
        }
    }
}

void HistoryModel::removeEntry(quint64 identifier)
{
    Entry *entry(getEntry(identifier));

    if (!entry)
    {
        return;
    }

    const QUrl url(Utils::normalizeUrl(entry->getUrl()));

    if (m_urls.contains(url))
    {
        m_urls[url].removeAll(entry);

        if (m_urls[url].isEmpty())
        {
            m_urls.remove(url);
        }
    }

    if (identifier > 0 && m_identifiers.contains(identifier))
    {
        m_identifiers.remove(identifier);
    }

    emit entryRemoved(entry);

    removeRow(entry->row());

    emit modelModified();
}

HistoryModel::Entry* HistoryModel::addEntry(const QUrl &url, const QString &title, const QIcon &icon, const QDateTime &date, quint64 identifier)//给当前用户增加浏览记录
{
    blockSignals(true);

    if (m_type == TypedHistory)//如果已经访问过，更新，将其移除
    {
        if (hasEntry(url))
        {
            const QUrl normalizedUrl(Utils::normalizeUrl(url));

            for (int i = 0; i < m_urls[normalizedUrl].count(); ++i)
            {
                removeEntry(m_urls[normalizedUrl].at(i)->getIdentifier());
            }
        }
    }

    Entry *entry(new Entry());
    entry->setIcon(icon);

    insertRow(0, entry);
    setData(entry->index(), url, UrlRole);
    setData(entry->index(), title, TitleRole);
    setData(entry->index(), date, TimeVisitedRole);

    if (identifier == 0 || m_identifiers.contains(identifier))
    {
        identifier = (m_identifiers.isEmpty() ? 1 : (m_identifiers.lastKey() + 1));
    }

    setData(entry->index(), identifier, IdentifierRole);

    m_identifiers[identifier] = entry;

    blockSignals(false);

    emit entryAdded(entry);
    emit modelModified();

    return entry;
}

HistoryModel::Entry* HistoryModel::getEntry(quint64 identifier) const //用用户编号获取对应entry
{
    if (m_identifiers.contains(identifier))
    {
        return m_identifiers[identifier];
    }

    return nullptr;
}

QDateTime HistoryModel::getLastVisitTime(const QUrl &url) const //entries里最新的time
{
    const QUrl normalizedUrl(Utils::normalizeUrl(url));

    if (!m_urls.contains(normalizedUrl))
    {
        return {};
    }

    const QVector<Entry*> entries(m_urls.value(normalizedUrl));
    QDateTime lastVisitTime;

    for (int i = 0; i < entries.count(); ++i)
    {
        const QDateTime entryLastVisitTime(entries.at(i)->getTimeVisited());

        if (!lastVisitTime.isValid() || entryLastVisitTime > lastVisitTime)
        {
            lastVisitTime = entryLastVisitTime;
        }
    }

    return lastVisitTime;
}

QVector<HistoryModel::HistoryEntryMatch> HistoryModel::findEntries(const QString &prefix, bool markAsTypedIn) const
{
    QVector<Entry*> matchedEntries;
    QVector<HistoryEntryMatch> allMatches;
    QVector<HistoryEntryMatch> currentMatches;
    QMultiMap<QDateTime, HistoryEntryMatch> matchesMap;
    QHash<QUrl, QVector<Entry*> >::const_iterator urlsIterator;

    for (urlsIterator = m_urls.constBegin(); urlsIterator != m_urls.constEnd(); ++urlsIterator)
    {
        if (urlsIterator.value().isEmpty() || matchedEntries.contains(urlsIterator.value().value(0)))
        {
            continue;
        }

        const QString result(Utils::matchUrl(urlsIterator.key(), prefix));

        if (!result.isEmpty())
        {
            HistoryEntryMatch match;
            match.entry = urlsIterator.value().value(0);
            match.match = result;

            if (markAsTypedIn)
            {
                match.isTypedIn = true;
            }

            matchesMap.insert(match.entry->data(TimeVisitedRole).toDateTime(), match);

            matchedEntries.append(match.entry);
        }
    }

    currentMatches = matchesMap.values().toVector();

    matchesMap.clear();

    allMatches.reserve(currentMatches.count());

    for (int i = (currentMatches.count() - 1); i >= 0; --i)
    {
        allMatches.append(currentMatches.at(i));
    }

    return allMatches;
}

HistoryModel::HistoryType HistoryModel::getType() const
{
    return m_type;
}

bool HistoryModel::save(const QString &path) const
{
//    if (SessionsManager::isReadOnly())
//    {
//        return false;
//    }

    QJsonArray historyArray;

    for (int i = 0; i < rowCount(); ++i)
    {
        const QModelIndex index(this->index(i, 0));

        if (index.isValid())
        {
            QJsonObject cur();

            cur().insert(QLatin1String("url"),QString(index.data(UrlRole).toUrl().toString()));
            cur().insert(QLatin1String("title"),QString(index.data(TitleRole).toString()));
            cur().insert(QLatin1String("time"),QString(index.data(TimeVisitedRole).toDateTime().toString(Qt::ISODate)));

            historyArray.prepend(cur);

        };
    }

    JsonSettings settings;
    settings.setArray(historyArray);

    return settings.save(path);
}

bool HistoryModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    Entry *entry(static_cast<Entry*>(itemFromIndex(index)));

    if (!entry)
    {
        return QStandardItemModel::setData(index, value, role);
    }

    if (role == UrlRole && value.toUrl() != index.data(UrlRole).toUrl())
    {
        const QUrl oldUrl(Utils::normalizeUrl(index.data(UrlRole).toUrl()));
        const QUrl newUrl(Utils::normalizeUrl(value.toUrl()));

        if (!oldUrl.isEmpty() && m_urls.contains(oldUrl))
        {
            m_urls[oldUrl].removeAll(entry);

            if (m_urls[oldUrl].isEmpty())
            {
                m_urls.remove(oldUrl);
            }
        }

        if (!newUrl.isEmpty())
        {
            if (!m_urls.contains(newUrl))
            {
                m_urls[newUrl] = QVector<Entry*>();
            }

            m_urls[newUrl].append(entry);
        }
    }

    entry->setItemData(value, role);

    switch (role)
    {
        case TitleRole:
        case UrlRole:
        case IdentifierRole:
        case TimeVisitedRole:
            emit entryModified(entry);
            emit modelModified();

            break;
        default:
            break;
    }

    return true;
}

bool HistoryModel::hasEntry(const QUrl &url) const
{
    return m_urls.contains(Utils::normalizeUrl(url));
}


