#include "src/ui/bookmark/bookmarkitem.h"
#include "ui_bookmarkitem.h"
#include "browserwindow.h"
#include "addbookmarkwidget.h"

BookmarkItem::BookmarkItem(QWidget *parent,int id,QString url,QString title,QString description,QString gname,BrowserWindow* root) :
    QWidget(parent),root(root),id(id),url(url),title(title),gname(gname),
    ui(new Ui::BookmarkItem)
{
    ui->setupUi(this);
    this->setGeometry(0,0,260,130);
    this->setContextMenuPolicy(Qt::DefaultContextMenu);

    /* icon */
    QLabel* iconLabel = new QLabel(this);
    iconLabel->setGeometry(16,25,80,80);
    QString localUrl = IconManager::get_local_cache(url);
//    QString localUrl = ":/icon/image/clock.png";
    iconLabel->setPixmap(QPixmap(localUrl).scaled(iconLabel->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation));
    iconLabel->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    iconLabel->show();
    iconLabel->setStyleSheet("QLabel{background-color:grey;}");

    /* 标题 */
    QLabel* titleLabel = new QLabel(this);
    titleLabel->setStyleSheet("QLabel{background-color:transparent;color:white;font-size:14px;}");
    titleLabel->setText(title);
    titleLabel->setGeometry(106,25,126,20);

    /* 描述 */
    QLabel* descriptionLabel = new QLabel(this);
    descriptionLabel->setStyleSheet("QLabel{background-color:transparent;color:white;font-size:14px;}");
    descriptionLabel->setText(description);
    descriptionLabel->setAlignment(Qt::AlignLeft|Qt::AlignTop);
    descriptionLabel->setGeometry(106,55,126,50);


}

BookmarkItem::~BookmarkItem()
{
    delete ui;
}

//void BookmarkItem::paintEvent(QPaintEvent *event)
//{
//    Q_UNUSED(event);
//    QStyleOption opt;
//    opt.initFrom(this);
//    QPainter p(this);
//    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);

//    /* 绘制BookmarkItem背景 */
//    p.setPen(Qt::NoPen);
//    p.setBrush(QColor(0,0,0,178));
//    p.drawRect(0,0,260,130);
//}

void BookmarkItem::contextMenuEvent(QContextMenuEvent *event){
        cmenu = new QMenu(this);//新建Menu
        QAction *action1 = cmenu->addAction("编辑");
        QAction *action2 = cmenu->addAction("删除");
        connect(action1, &QAction::triggered, this, &BookmarkItem::editItem);
        connect(action2, &QAction::triggered, this, &BookmarkItem::deleteItem);
        cmenu->exec(QCursor::pos());
}

/* 删除书签 */
void BookmarkItem::deleteItem(){
    root->Browser::m_bookmark->deleteBookmark(root->Browser::userid,id);
    emit on_deleteItem_passSignals();
    this->close();
}

/* 编辑书签 */
void BookmarkItem::editItem(){
    root->addbookmarkTest = new addbookmarkwidget(root,0,100,300,230,root);
    root->addbookmarkTest->id=id;
    root->addbookmarkTest->Booktitle=title;
    root->addbookmarkTest->url=url;
    root->addbookmarkTest->gname=gname;
    root->addbookmarkTest->show();
    root->addbookmarkTest->on_clicked_editbookmark();
    root->addbookmarkTest->setFocus();
    root->my_tab->stackUnder(root->addbookmarkTest);
    root->my_tab->currentWebView()->stackUnder(root->addbookmarkTest);
}

void BookmarkItem::mouseReleaseEvent(QMouseEvent* event){
    if(event->button()==Qt::LeftButton){
        root->my_tab->createTab();
        root->my_tab->setUrl(QUrl(url));
    }
}
