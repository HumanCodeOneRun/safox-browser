#ifndef TABWIDGET_H
#define TABWIDGET_H

#include <QWidget>
#include <QTabWidget>
#include <QWebEnginePage>
#include <QLineEdit>
#include <QIcon>
#include <QMenu>
//#include <toolbar.h>
#include <bookmarkwidget.h>

class QUrl;
class BrowserWindow;


namespace Ui {
class tabwidget;
}

class WebView;


class tabwidget : public QTabWidget
{
    Q_OBJECT

public:
    explicit tabwidget(QWidget *parent = nullptr,QWebEngineProfile *Profile= nullptr);
    ~tabwidget();
    //Toolbar* toolbar;

    void setParentWindow(BrowserWindow *ParentWindow);
    WebView *currentWebView() const;

public slots:
    void closeTab(int index);
    void setUrl(const QUrl &url);
    void nextTab();
    void previousTab();
    WebView *createTab(bool makeCurrent = true);
    WebView *createView();
    void triggerWebPageAction(QWebEnginePage::WebAction action);


private slots:
    void handleCurrentChanged(int index);
    void handleContextMenuRequested(const QPoint &pos);
    void reloadTab(int index);
    void cloneTab(int index);
    void closeOtherTabs(int index);
    void reloadAllTabs();
    void addbookmark(int index);




signals:
    void linkHovered(const QString &link);
    void titleChanged(const QString &title);
    void urlChanged(const QUrl &url);
    void favIconChanged(const QIcon &icon);
    void webActionEnabledChanged(QWebEnginePage::WebAction action, bool enabled);

    void loadProgress(int progress);



private:
    BrowserWindow *BrowserPoint;
    WebView *webView(int index) const;
    void setupView(WebView *webView);
    Ui::tabwidget *ui;

    QWebEngineProfile *profile;
};

#endif // TABWIDGET_H
