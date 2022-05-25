#ifndef BOOKMARKBOXGROUP_H
#define BOOKMARKBOXGROUP_H
#include <QWidget>
#include <QVBoxLayout>
#include <QToolButton>

class BookmarkBoxGroup : public QWidget
{
    Q_OBJECT
public:
    explicit BookmarkBoxGroup(QWidget *parent = nullptr);
//    bool addItem(QWidget* item);
//    void setName(QString name);
//    QString getName();
private:
    QVBoxLayout layout;
    QToolButton btn;
private slots:
    void onClicked(bool);

signals:

};

#endif // BOOKMARKBOXGROUP_H
