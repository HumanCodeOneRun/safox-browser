/*
 * @Author: SC-WSKun 540610423@qq.com
 * @Date: 2022-05-14 22:01:55
 * @LastEditors: SC-WSKun 540610423@qq.com
 * @LastEditTime: 2022-05-26 16:46:51
 * @FilePath: \safox\src\core\bookmark\bookmarkwidget.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include "src/ui/bookmark/bookmarkwidget.h"
#include "ui_bookmarkwidget.h"
#include "src/ui/browserwindow/browserwindow.h"
BookmarkWidget::BookmarkWidget(QWidget *parent,int x,int y,int width,int height,BrowserWindow* root) :
    QWidget(parent),width(width),height(height),root(root),
    ui(new Ui::BookmarkWidget)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose,true);

    /* ui部分 */
    this->setGeometry(x,y,width,height);
    this->setStyleSheet("QWidget{background:rgba(46,50,53,70);}");

    /* 标题 */
    QLabel* title = new QLabel(this);
    title->setText("书签列表");
    title->setGeometry(20,15,56,20);
    title->setStyleSheet("QLabel{color:white;font-size:14px;}");


    QToolButton* refreshBtn = new QToolButton(this);
    refreshBtn->setGeometry(260,15,20,20);
    QIcon refresh = QIcon(":/icon/image/refresh.png");
    refreshBtn->setIcon(refresh);
    connect(refreshBtn,&QToolButton::clicked,this,[=](){
        on_clicked_bookmarkerGroup(index);
    });


    /* 搜索框 */
    searchKey = new QLineEdit(this);
    searchKey->setText("Type here to search");
    searchKey->setGeometry(20,50,260,35);
    searchKey->setStyleSheet("QLineEdit{background-color:rgba(51, 53, 54, 255);color:rgba(255, 255, 255, 128);font-size:15px;border:none;}");
    QAction * pActLeft = new QAction(this);
    pActLeft->setIcon(QIcon(":/icon/image/search.png"));
    searchKey->addAction(pActLeft,QLineEdit::LeadingPosition);

    loadBookmarkGroup();


    /*添加书签测试*/
//    for(int i=0;i<10;i++){
//            root->Browser::m_bookmark->addBookmark(root->Browser::userid,"testPage"+QString::number(i),QUrl("www.test.com"),"FirstGroup",QUrl("www.testIcon.com"));
//    }
//    root->Browser::m_bookmark->addBookmark(root->Browser::userid,"testPage2",QUrl("www.test.com"),"SecondGroup",QUrl("www.testIcon.com"));

    /* 书签显示 */
    this->scrollView = new QScrollArea(this);
    this->scrollView->setStyleSheet("QScrollArea{background-color:transparent;}");
    this->scrollView->horizontalScrollBar()->setStyleSheet("QScrollBar{height:0px;}");
    this->scrollView->setGeometry(0,150,width,height-200);
    scrollWidget = new QWidget();
    layout=new QVBoxLayout();
    scrollWidget->setLayout(layout);
    count=0;
    scrollWidget->setFixedSize(QSize(280,count*60));
    scrollView->setWidget(scrollWidget);

    /* 加载默认分组 */
    index = 0;
    qDebug("start init item");
    on_clicked_bookmarkerGroup(index);
}

BookmarkWidget::~BookmarkWidget()
{
    delete ui;
}

void BookmarkWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);

    /* 绘制historyWidget背景 */
    p.setPen(Qt::NoPen);
    p.setBrush(QColor(46,50,53,178));
    p.drawRect(0,0,this->width,this->height);
}

/* 加载分组 */
void BookmarkWidget::loadBookmarkGroup(){
    /* 书签分组下拉框 */
    QComboBox* markerGroup = new QComboBox(this);
    markerGroup->setGeometry(20,100,260,35);
    markerGroup->setStyleSheet("QComboBox{color:white;}");

    /* 添加分组测试 */
    qDebug()<<root->userid;
    root->Browser::m_bookmark->addBookmarkGroup(root->Browser::userid,"默认收藏夹",QUrl("www.testIcon.com"));
//    root->Browser::m_bookmark->addBookmarkGroup(root->Browser::userid,"FirstGroup",QUrl("www.testIcon.com"));
//    root->Browser::m_bookmark->addBookmarkGroup(root->Browser::userid,"SecondGroup",QUrl("www.testIcon.com"));

    /* 读取书签分组 */
    this->userBookmark = root->Browser::m_bookmark->initGetGroups(root->Browser::userid);
    QList<QList<QVariant>>::iterator i = this->userBookmark.begin();
    while(i!=this->userBookmark.end()){
        QList<QVariant>::iterator j = (*i).begin();
        j++;
        this->gidArr.push_back((*j).toInt());
        j++;
        QString GroupName = (*j).toString();
        markerGroup->addItem(GroupName);
        i++;
    }
    connect(markerGroup,&QComboBox::currentIndexChanged,this,&BookmarkWidget::on_clicked_bookmarkerGroup);
}

/* 加载书签 */
void BookmarkWidget::on_clicked_bookmarkerGroup(int newIndex){
    index = newIndex;
    this->scrollWidget->close();
    scrollWidget = new QWidget();
    layout=new QVBoxLayout();
    scrollWidget->setLayout(layout);
    qDebug()<<gidArr;
    int gid = this->gidArr[newIndex];
    count = 0;
    qDebug("start get item");
    QVector<QVector<QVariant>> bookmarkItems = root->Browser::m_bookmark->getItemsByGid(root->Browser::userid,gid);
    qDebug("get item end");
    for(int i=0;i<bookmarkItems.size();i++){
        BookmarkItem* temp=new BookmarkItem(scrollWidget,bookmarkItems[i][0].toInt(),bookmarkItems[i][4].toString(),bookmarkItems[i][3].toString(),"description",root);
        connect(temp,&BookmarkItem::on_deleteItem_passSignals,this,[=](){
            count--;
            scrollWidget->setFixedSize(QSize(280,50+count*135));
        });
        count++;
        layout->addWidget(temp);
    }
    qDebug("end");
    scrollWidget->setFixedSize(width,50+count*135);
    this->scrollView->setWidget(scrollWidget);
}

void BookmarkWidget::refresh(){

}

void BookmarkWidget::bookmarkerReload(){
    emit reloadbookmark();
}

//防止触发browserwindow的位移
void BookmarkWidget::mousePressEvent(QMouseEvent *event)
{
    event->accept();
}

void BookmarkWidget::mouseMoveEvent(QMouseEvent *event)
{
    event->accept();
}

void BookmarkWidget::mouseReleaseEvent(QMouseEvent *event)
{
    event->accept();
}
