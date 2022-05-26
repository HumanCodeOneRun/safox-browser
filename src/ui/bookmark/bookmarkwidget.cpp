/*
 * @Author: SC-WSKun 540610423@qq.com
 * @Date: 2022-05-14 22:01:55
 * @LastEditors: SC-WSKun 540610423@qq.com
 * @LastEditTime: 2022-05-17 16:24:30
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

    /* ui部分 */
    this->setGeometry(x,y,width,height);
    this->setStyleSheet("QWidget{background:rgba(46,50,53,70);}");
    QLabel* title = new QLabel(this);
    title->setText("书签列表");
    title->setGeometry(20,15,56,20);
    title->setStyleSheet("QLabel{color:rgba(225,225,225,100);font-size:14px;}");

    /* 搜索框 */
    searchKey = new QLineEdit(this);
    searchKey->setText("Type here to search");
    searchKey->setGeometry(20,50,260,35);
    searchKey->setStyleSheet("QLineEdit{background-color:rgba(51, 53, 54, 100);color:rgba(255, 255, 255, 50);font-size:15px;border:none;}");
    QAction * pActLeft = new QAction(this);
    pActLeft->setIcon(QIcon(":/icon/image/search.png"));
    searchKey->addAction(pActLeft,QLineEdit::LeadingPosition);

    /* 书签分组下拉框 */
    QComboBox* markerGroup = new QComboBox(this);
    markerGroup->setGeometry(20,100,260,35);
    markerGroup->setStyleSheet("QComboBox{color:white;}");

    /* 添加分组测试 */
//    this->root->Browser::m_bookmark->addBookmarkGroup(root->Browser::userid,"FirstGroup",QUrl("www.testIcon.com"));

    /* 读取书签分组 */
    this->userBookmark = root->Browser::m_bookmark->initGetGroups(root->Browser::userid);
    QList<QList<QVariant>>::iterator i = this->userBookmark.begin();
    while(i!=this->userBookmark.end()){
        QList<QVariant>::iterator j = (*i).begin();
        this->gidArr.push_back((*j).toInt());
        j++;
        j++;
        QString GroupName = (*j).toString();
        markerGroup->addItem(GroupName);
        i++;
    }
    connect(markerGroup,&QComboBox::currentIndexChanged,this,&BookmarkWidget::on_clicked_bookmarkerGroup);



//    root->Browser::m_bookmark->addBookmark(root->Browser::userid,"testPage1",QUrl("www.test.com"),"SecondGroup",QUrl("www.testIcon.com"));
//    this->bookmark->addBookmark(root->Browser::userid,"testPage2",QUrl("www.test.com"),"secondGroup",QUrl("www.testIcon.com"));

    /* 书签显示 */
    this->scrollView = new QScrollArea(this);
    this->scrollView->setStyleSheet("QScrollArea{background-color:transparent;}");
    this->scrollView->horizontalScrollBar()->setStyleSheet("QScrollBar{height:0px;}");
    this->scrollView->setGeometry(0,150,width,height-200);
    QVBoxLayout *layout=new QVBoxLayout();
    scrollWidget = new QWidget();
    scrollWidget->setStyleSheet("QWidget{background-color:transparent;}");

    this->scrollView->setWidget(scrollWidget);



    layout->addWidget(scrollWidget);

    this->scrollView->setLayout(layout);

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
    p.setBrush(QColor(46,50,53,70));
    p.drawRect(0,0,this->width,this->height);
}

void BookmarkWidget::on_clicked_bookmarkerGroup(int index){
    qDebug()<<index;
    int gid = this->gidArr[index];
    QVector<QVector<QVariant>> bookmarkItems = root->Browser::m_bookmark->getItemsByGid(root->Browser::userid,gid);
    qDebug()<<bookmarkItems;
    int count = 0;
    BookmarkItem* temp=new BookmarkItem(scrollWidget,20,0,":/icon/../image/setting.png","test_title","test_description");
    BookmarkItem* temp2=new BookmarkItem(scrollWidget,20,135,":/icon/../image/setting.png","test_kkkkkk","test_description");
    //todo: 计算需要的高度
    scrollWidget->setFixedSize(width,800+count*135);
}
