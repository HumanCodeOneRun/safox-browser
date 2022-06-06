#ifndef WEBVIEW_H
#define WEBVIEW_H

#include <QObject>
#include <QWebEngineView>

class AdblockRequestInterceptor;
class DefaultRequestInterceptor;


class WebView: public QWebEngineView {
    Q_OBJECT
    public:
    explicit WebView(QWidget* parent = 0);
    QString getTitle();
    QUrl getUrl();
    QUrl getIconUrl();
    bool getConnectedToHistory();
    void setConnectedToHistory(bool _connectToHistory);

    QIcon favIcon()const;
    bool isWebActionEnabled(QWebEnginePage::WebAction webAction) const;
    QWebEngineView *createWindow(QWebEnginePage::WebWindowType type) override;

    public slots:
    void changeTitle(const QString& newTitle);
    void changeUrl(const QUrl& newUrl);
    void changeIconUrl(const QUrl& iconUrl);
    void setAdblockRequestInterceptor(const QString _easylist_path = "../dependent_files/easylist.txt");
    void setDefaultRequestInterceptor();

    void setAdblockRequestInterceptor(AdblockRequestInterceptor* _m_adblockRequestInterceptor);
    void setDefaultRequestInterceptor(DefaultRequestInterceptor* _m_defaultRequestInterceptor);
    

    private:
    QString title;
    QUrl url;
    bool connectedToHistory;
    QUrl iconUrl;
    //adblock member may be should belong to browserwindow
    AdblockRequestInterceptor* m_adblockRequestInterceptor;
    DefaultRequestInterceptor* m_defaultRequestInterceptor;


    Q_SIGNALS:
    void sendChangedWebView(WebView* webview);




};

#endif
