#include "bookmarkwidget.h"
#include "ui_bookmarkwidget.h"
Browser* temp = new Browser();
BookmarkWidget::BookmarkWidget(QWidget *parent,int x,int y,int width,int height) :
    QWidget(parent),
    ui(new Ui::BookmarkWidget)
{
    ui->setupUi(this);
    this->width = width;
    this->height = height;
    this->bookmark = new BookmarkModel();

    /* ui部分 */
    this->setGeometry(x,y,width,height);
    this->setStyleSheet("QWidget{background:rgba(46,50,53,70);}");

    QLabel* title = new QLabel(this);
    title->setText("书签列表");
    title->setGeometry(20,15,56,20);
    title->setStyleSheet("QLabel{color:rgba(225,225,225,100);font-size:14px;}");

    searchKey = new QLineEdit(this);
    searchKey->setText("Type here to search");
    searchKey->setGeometry(20,50,260,35);
    searchKey->setStyleSheet("QLineEdit{background-color:rgba(51, 53, 54, 100);color:rgba(255, 255, 255, 50);font-size:15px;border:none;}");
    QAction * pActLeft = new QAction(this);
    pActLeft->setIcon(QIcon(":/icon/image/search.png"));
    searchKey->addAction(pActLeft,QLineEdit::LeadingPosition);

    this->bookmark->addBookmarkGroup(temp->userid,"firstGroup",QUrl("www.testIcon.com"));
    this->userBookmark = this->bookmark->initGetGroups(temp->userid);
    this->bookmark->addBookmark(temp->userid,"testPage",QUrl("www.test.com"),"firstGroup",QUrl("www.testIcon.com"));
    qDebug("vector:");
    qDebug()<<this->userBookmark;


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

void BookmarkWidget::loadBookmarker(){

}
