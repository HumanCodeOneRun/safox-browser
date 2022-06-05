#ifndef ADDBOOKMARKWIDGET_H
#define ADDBOOKMARKWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QComboBox>
#include <QLineEdit>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "bookmarkmodel.h"
#include "bookmarkitem.h"
#include "databasetaskscheduler.h"
#include <QSpacerItem>
#include <tabwidget.h>

namespace Ui {
class addbookmarkwidget;
}

class BrowserWindow;

class addbookmarkwidget : public QWidget
{
    Q_OBJECT

public:
    explicit addbookmarkwidget(QWidget *parent = nullptr,int x=0,int y=0,int width=0,int height=0,BrowserWindow* root=nullptr);
    BrowserWindow* root;
    int width,height;
    ~addbookmarkwidget();
    QVBoxLayout *Vlayout;
    QHBoxLayout* Hlayout;
    QLabel* title;
    QWidget* buttonwidget;
    QLineEdit *BM_name;
    QComboBox *BM_group;
    QPushButton *BM_save;
    QPushButton *BM_cancel;
    std::vector<int> gidArr;
    QVector<QVector<QVariant>> userBookmark;
    void on_clicked_addbookmark();
    void on_clicked_editbookmark();
    virtual void focusOutEvent(QFocusEvent *e);
    QString url,Booktitle,gname;
    int id;

private:
    void loadBookmarkGroup();
    void paintEvent(QPaintEvent *event);
    //void mouseMoveEvent(QMouseEvent* event);
    //void mouseReleaseEvent(QMouseEvent* event);
    int saveFlag;


    Ui::addbookmarkwidget *ui;

signals:
    void EditBookmark();
    void AddBookmark();
    void add();
    void edit();

private slots:
    //void on_clicked_bookmarkerGroup(int index);
    void on_clicked_add();
    void on_clicked_edit();
    void on_clicked_BM_cancel();

};

#endif // ADDBOOKMARKWIDGET_H
