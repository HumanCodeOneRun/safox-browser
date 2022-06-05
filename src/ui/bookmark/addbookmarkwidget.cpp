#include "addbookmarkwidget.h"
#include "ui_addbookmarkwidget.h"
#include "src/ui/browserwindow/browserwindow.h"
addbookmarkwidget::addbookmarkwidget(QWidget *parent,int x,int y,int width,int height,BrowserWindow* root) :
    QWidget(parent),width(width),height(height),root(root),
    ui(new Ui::addbookmarkwidget)
{

    qDebug("init addbookmarkwidget");
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose,true);
    //ui部分
    this->setGeometry(x,y,width,height);
    this->setStyleSheet("QWidget{background:rgba(46,50,53,70);}");

    Vlayout=new QVBoxLayout();
    title = new QLabel(this);
    title->setGeometry(20,15,56,20);
    title->setStyleSheet("QLabel{color:white;font-size:14px;}");

    //书签名
    BM_name = new QLineEdit(this);
    //BM_name->setText("Type here to search");
    BM_name->setGeometry(20,50,260,35);
    BM_name->setStyleSheet("QLineEdit{background-color:rgba(51, 53, 54, 255);color:rgba(255, 255, 255, 128);font-size:15px;border:none;}");

    //书签分组
    qDebug("start load group");
    loadBookmarkGroup();

    //保存和取消按钮
    Hlayout = new QHBoxLayout();
    buttonwidget=new QWidget(this);
    buttonwidget->setGeometry(20,130,260,90);
    buttonwidget->setStyleSheet("QWidget{background:rgba(46,50,53,70);}");
    BM_save=new QPushButton("保存",root);
    BM_cancel=new QPushButton("取消",root);
    //控制添加或编辑的flag
    saveFlag=1;

    this->setFocusPolicy(Qt::NoFocus);

    Hlayout->addWidget(BM_save);
    Hlayout->addWidget(BM_cancel);
    BM_save->setFixedSize(90,35);
    BM_cancel->setFixedSize(90,35);

    buttonwidget->setLayout(Hlayout);
    connect(this,&addbookmarkwidget::add,this,[=](){
        title->setText("新增书签");
        const QString name=root->my_tab->currentWebView()->getTitle();
        BM_name->setText(name);
        BM_group->setEditable(true);
        emit AddBookmark();
    });
    connect(this,&addbookmarkwidget::edit,this,[=](){
        title->setText("编辑书签");
        const QString name=Booktitle;
        BM_group->setEditable(false);
        BM_name->setText(name);
        emit EditBookmark();
    });
    connect(this,&addbookmarkwidget::AddBookmark,this,&addbookmarkwidget::on_clicked_add);
    connect(this,&addbookmarkwidget::EditBookmark,this,&addbookmarkwidget::on_clicked_edit);
    connect(BM_save,&QPushButton::clicked,this,[=](){
        if (saveFlag){
            //添加
            root->Browser::m_bookmark->addBookmark(root->Browser::userid,this->BM_name->text(),root->my_tab->currentWebView()->getUrl(),this->BM_group->currentText(),root->my_tab->currentWebView()->getIconUrl());
            this->hide();
        }
        else if(!saveFlag){
            //编辑
           const QString Gname=BM_group->currentText();
           const QString name=BM_name->text();
           BM_group->setCurrentText(Gname);
           root->Browser::m_bookmark->editBookmark(root->Browser::userid,this->id,name,QUrl(this->url),Gname);
           this->hide();
        }
    });
    connect(BM_cancel,&QPushButton::clicked,this,&addbookmarkwidget::on_clicked_BM_cancel);
}

addbookmarkwidget::~addbookmarkwidget()
{
    delete ui;
}
void addbookmarkwidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);

    /* 绘制Widget背景 */
    p.setPen(Qt::NoPen);
    p.setBrush(QColor(46,50,53,178));
    p.drawRect(0,0,this->width,this->height);
}
void addbookmarkwidget::loadBookmarkGroup(){
    /* 书签分组下拉框 */
    QComboBox* markerGroup = new QComboBox(this);
    BM_group=markerGroup;
    markerGroup->setGeometry(20,100,260,35);
    markerGroup->setStyleSheet("QComboBox{color:white;}");


    /* 读取书签分组 */
    qDebug("load group");
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
    qDebug("end group");
    //connect(markerGroup,&QComboBox::currentIndexChanged,this,&addbookmarkwidget::on_clicked_bookmarkerGroup);
}
void addbookmarkwidget::on_clicked_add(){
    qDebug("click add");
    saveFlag=1;
}
void addbookmarkwidget::on_clicked_edit(){
    qDebug("click edit");
    saveFlag=0;
}
void addbookmarkwidget::on_clicked_BM_cancel(){
    this->close();
}
void addbookmarkwidget::on_clicked_addbookmark(){
    emit add();
}
void addbookmarkwidget::on_clicked_editbookmark(){
    emit edit();
}
void addbookmarkwidget::focusOutEvent(QFocusEvent *e){
    Q_UNUSED(e);
    if(!this->BM_group->hasFocus()&&!this->BM_name->hasFocus()&&!this->BM_save->hasFocus()&&!this->BM_cancel->hasFocus()){
        this->close();
    }
}
/*
void addbookmarkwidget::mouseMoveEvent(QMouseEvent* event){
    event->accept();
}

void addbookmarkwidget::mouseReleaseEvent(QMouseEvent* event){
    event->accept();
}
*/
