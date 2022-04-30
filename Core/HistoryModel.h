#ifndef HISTORYMODEL_H
#define HISTORYMODEL_H
#include <QtCore/QDateTime>
#include <QtCore/QUrl>
#include <QtGui/QStandardItemModel>



class HistoryModel final : public QStandardItemModel
{
    Q_OBJECT

public:
    enum HistoryEntryRole
    {
        TitleRole = Qt::DisplayRole,
        UrlRole = Qt::StatusTipRole,
        IdentifierRole = Qt::UserRole,
        TimeVisitedRole
    };

    enum HistoryType
    {
        BrowsingHistory = 0,
        TypedHistory //已经访问过,需要更新
    };

    class Entry final : public QStandardItem
    {
    public:
        void setData(const QVariant &value, int role) override;
        void setItemData(const QVariant &value, int role);
        QString getTitle() const;
        QUrl getUrl() const;
        QDateTime getTimeVisited() const;
        QIcon getIcon() const;
        quint64 getIdentifier() const;

    protected:
        explicit Entry();

    friend class HistoryModel;
    };

    struct HistoryEntryMatch final
    {
        Entry *entry = nullptr;
        QString match;
        bool isTypedIn = false;
    };

    explicit HistoryModel(const QString &path, HistoryType type, QObject *parent = nullptr);

    void clearExcessEntries(int limit);
    void clearRecentEntries(uint period);
    void clearOldestEntries(int period);
    void removeEntry(quint64 identifier);
    Entry* addEntry(const QUrl &url, const QString &title, const QIcon &icon, const QDateTime &date = QDateTime::currentDateTimeUtc(), quint64 identifier = 0);
    Entry* getEntry(quint64 identifier) const;
    QDateTime getLastVisitTime(const QUrl &url) const;
    QVector<HistoryEntryMatch> findEntries(const QString &prefix, bool markAsTypedIn = false) const;
    HistoryType getType() const;
    bool hasEntry(const QUrl &url) const;
    bool save(const QString &path) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;

private:
    QHash<QUrl, QVector<Entry*> > m_urls;
    QMap<quint64, Entry*> m_identifiers;
    HistoryType m_type;

signals:
    void cleared();
    void entryAdded(Entry *entry);
    void entryModified(Entry *entry);
    void entryRemoved(Entry *entry);
    void modelModified();
};


#endif // HISTORYMODEL_H
