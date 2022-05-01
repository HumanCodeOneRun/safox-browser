#ifndef WEBVIEW_H
#define WEBVIEW_H

#include <QObject>
#include <QWebEngineView>


class WebView: public QWebEngineView {
    Q_OBJECT
    public:
    explicit WebView(QWidget* parent = 0);
    
    QString getTitle();
    QUrl getUrl();
    QUrl getIconUrl();

    bool getConnectedToHistory();
    void setConnectedToHistory(bool _connectToHistory);



    public slots:
    void changeTitle(const QString& newTitle);
    void changeUrl(const QUrl& newUrl);
    void changeIconUrl(const QUrl& iconUrl);
    

    public://later should be changed to private
    QString title;
    QUrl url;
    bool connectedToHistory;
    QUrl iconUrl;


    Q_SIGNALS:
    void sendChangedWebView(WebView* webview);




};

#endif