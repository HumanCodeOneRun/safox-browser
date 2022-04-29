#ifndef WEBVIEW_H
#define WEBVIEW_H

#include <QObject>
#include <QWebEngineView>


class WebView: public QWebEngineView {
    Q_OBJECT
    public:
    explicit WebView(QWidget* parent = 0);
    void changeTitle(const QString& newTitle);
    void changeUrl(const QUrl& newUrl);
    QString getTitle();
    QUrl getUrl();

    bool getConnectedToHistory();
    void setConnectedToHistory(bool _connectToHistory);



    public:
    

    public://later should be changed to private
    QString title;
    QUrl url;
    bool connectedToHistory;


    Q_SIGNALS:
    void sendChangedWebView(WebView* webview);




};

#endif