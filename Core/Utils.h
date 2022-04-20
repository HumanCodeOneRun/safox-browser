#ifndef UTILS_H
#define UTILS_H



#include <QtCore/QMetaEnum>
#include <QtCore/QMimeData>
#include <QtCore/QMimeType>
#include <QtCore/QUrl>
#include <QtGui/QIcon>

#define SECONDS_IN_DAY 86400


enum TrileanValue //三值
{
    UnknownValue = 0,
    FalseValue,
    TrueValue
};

struct ApplicationInformation final
{
    QString command;
    QString name;
    QIcon icon;
};

struct ErrorPageInformation final
{
    enum ActionType
    {
        OtherAction = 0,
        MainAction,
        AdvancedAction
    };

    enum ErrorType
    {
        OtherError = 0,
        BlockedContentError,
        ConnectionInsecureError,
        ConnectionRefusedError,
        FileNotFoundError,
        FraudAttemptError,
        RedirectionLoopError,
        ServerNotFoundError,
        UnsupportedAddressTypeError
    };

    struct PageAction final
    {
        QString name;
        QString title;
        ActionType type;
    };

    QString title;
    QUrl url;
    QStringList description;
    QVector<PageAction> actions;
    ErrorType type = OtherError;
};

struct SaveInformation final
{
    QString path;
    QString filter;
    bool canSave = false;
};

class EnumeratorMapper
{
public:
    explicit EnumeratorMapper(const QMetaEnum &enumeration, const QString &suffix = {});

    QString mapToName(int value, bool lowercaseFirst = true) const;
    int mapToValue(const QString &name, bool checkSuffix = false) const;

private:
    QMetaEnum m_enumerator;
    QString m_suffix;
};

namespace Utils
{

void runApplication(const QString &command, const QUrl &url = {});
void startLinkDrag(const QUrl &url, const QString &title, const QPixmap &pixmap, QObject *parent = nullptr);
QString matchUrl(const QUrl &url, const QString &prefix);
QString createIdentifier(const QString &source, const QStringList &exclude = {}, bool toLowerCase = true);
QString createErrorPage(const ErrorPageInformation &information);
QString appendShortcut(const QString &text, const QKeySequence &shortcut);
QString elideText(const QString &text, const QFontMetrics &fontMetrics, QWidget *widget = nullptr, int maximumWidth = -1, int minimumWidth = 100);
QString substitutePlaceholders(QString text, const QHash<QString, QString> &placeholders);
QString savePixmapAsDataUri(const QPixmap &pixmap);
QString extractHost(const QUrl &url);
QString formatElapsedTime(int value);
QString formatDateTime(const QDateTime &dateTime, QString format = {}, bool allowFancy = true);
QString formatUnit(qint64 value, bool isSpeed = false, int precision = 1, bool appendRaw = false);
QString formatFileTypes(const QStringList &filters = {});
QString normalizeObjectName(QString name, const QString &suffix = {});
QString normalizePath(const QString &path);
QUrl expandUrl(const QUrl &url);
QUrl normalizeUrl(QUrl url);
QLocale createLocale(const QString &name);
QPixmap loadPixmapFromDataUri(const QString &data);
SaveInformation getSavePath(const QString &fileName, const QString &directory = {}, QStringList filters = {}, bool forceAsk = false);
QStringList getOpenPaths(const QStringList &fileNames = {}, QStringList filters = {}, bool selectMultiple = false);
QVector<QUrl> extractUrls(const QMimeData *mimeData);
QVector<ApplicationInformation> getApplicationsForMimeType(const QMimeType &mimeType);
qreal calculatePercent(qint64 amount, qint64 total, int multiplier = 100);
int calculateCharacterWidth(QChar character, const QFontMetrics &fontMetrics);
int calculateTextWidth(const QString &text, const QFontMetrics &fontMetrics);
bool isUrl(const QString &text);
bool isUrlEmpty(const QUrl &url);

}



#endif // UTILS_H
