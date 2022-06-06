#include "downloadwidget.h"
#include "ui_downloadwidget.h"
#include <browserwindow.h>

DownloadItemWidget::DownloadItemWidget(QWidget *parent,QString iconUrl,QString title,QString downloadUrl,BrowserWindow* root):QWidget(parent),downloadUrl(downloadUrl),root(root){
    this->setGeometry(0,0,250,60);
    this->setStyleSheet("QWidget{background-color:transparent;}"
                        "QLabel{color:white;font-size:15px;background-color:transparent;}");

    downloading = true;

    /* icon */
    QLabel* iconLabel = new QLabel(this);
    iconLabel->setGeometry(0,10,40,40);
//    iconLabel->setPixmap(QPixmap(IconManager::get_local_cache(iconUrl)).scaled(iconLabel->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation));
    iconLabel->setPixmap(QPixmap(iconUrl));
    iconLabel->show();
//    iconLabel->setStyleSheet("QLabel{background-color:grey;}");

    /* title */
    QLabel* downloadTitle = new QLabel(this);
    downloadTitle->setGeometry(60,10,102,20);
    QFontMetrics fontWidth(downloadTitle->font());//得到每个字符的宽度
    QString elideNote = fontWidth.elidedText(title, Qt::ElideRight, 102);//最大宽度170px
    downloadTitle->setText(elideNote);//显示省略号的字符串
    downloadTitle->setToolTip(title);//设置tooltips

    /* 进度条 */
    progress = new QProgressBar(this);
    progress->setStyleSheet("QProgressBar::chunk"
                            "{"
                            "border-radius:11px;"
                            "background:qlineargradient(spread:pad,x1:0,y1:0,x2:1,y2:0,stop:0 #01FAFF,stop:1  #26B4FF);"
                            "border-radius:5px;"
                            "border:1px solid black;"
                            "background-color:skyblue;"
                            "width:8px;margin:0.5px;"
                            "}"
                            "QProgressBar"
                            "{"
                            "height:20px;"
                            "text-align:center;"
                            "font-size:14px;"
                            "color:white;"
                            "border-radius:11px;"
                            "background: #1D5573 ;"
                            "}");
    progress->setGeometry(60,30,125,20);
    progress->setValue(0);

    /* 开始/暂停按钮 */
    startBtn = new QToolButton(this);
    startBtn->setGeometry(192,18,24,24);
    QIcon start = QIcon(":/icon/image/pause.png");
    startBtn->setIcon(start);
    connect(startBtn,&QToolButton::clicked,this,&DownloadItemWidget::go);

    /* 取消按钮 */
    deleteBtn = new QToolButton(this);
    deleteBtn->setGeometry(226,18,24,24);
    QIcon del = QIcon(":/icon/image/close.png");
    deleteBtn->setIcon(del);
    connect(deleteBtn,&QToolButton::clicked,this,&DownloadItemWidget::del);

    auto item_map = root->Browser::m_downloadMgr->get_items();
    down_load_item = item_map[downloadUrl];
    qDebug()<<down_load_item.get();
    QObject::connect(down_load_item.get(), &DownloadItem::bytes_received_changed,this,&DownloadItemWidget::changeIndex);
}

DownloadItemWidget::~DownloadItemWidget(){

}

void DownloadItemWidget::go(){
    if(progress->value()>= 100){
        return;
    }
    if(downloading == true){
        root->Browser::m_downloadMgr->on_pause(downloadUrl);
        startBtn->setIcon(QIcon(":/icon/image/play.png"));
        downloading = false;
    }else{
        root->Browser::m_downloadMgr->on_resume(downloadUrl);
        startBtn->setIcon(QIcon(":/icon/image/pause.png"));
        downloading = true;
    }
}

void DownloadItemWidget::del(){
    root->Browser::m_downloadMgr->on_delete(downloadUrl);
    emit on_del_passSignal();
    this->close();
}

void DownloadItemWidget::changeIndex(qint64 receiveSize){
    qDebug()<<"receiveSize:"<<receiveSize;
    int prog = double(down_load_item->get_bytes_received())/double(down_load_item->get_bytes_total())*100;
    qDebug()<<prog;
    progress->setValue(prog);
}

DownloadWidget::DownloadWidget(QWidget *parent,QToolButton* btn,BrowserWindow* root) :
    QWidget(parent),root(root),
    ui(new Ui::DownloadWidget)
{
    ui->setupUi(this);
    int x = btn->x()-300+btn->width();
    int y = btn->y()+btn->height();
    this->setGeometry(x,y,300,400);

    items = new QScrollArea(this);
    items->horizontalScrollBar()->setStyleSheet("QScrollBar{height:0px;}");
    items->setStyleSheet("QScrollArea{background-color:transparent;}");
    items->setGeometry(10,10,280,380);
    scrollWidget = new QWidget();
    scrollWidget->setStyleSheet("QWidget{background-color:transparent;}");
    labelLayout=new QVBoxLayout();
    scrollWidget->setLayout(labelLayout);

    //todo: 与download的对接
    index = 0;
    scrollWidget->setFixedSize(QSize(280,index*60));
    items->setWidget(scrollWidget);

    connect(root,&BrowserWindow::add_download,this,&DownloadWidget::addItem);
}

DownloadWidget::~DownloadWidget()
{
    delete ui;
}

void DownloadWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);

    /* 绘制downloadWidget背景 */
    p.setPen(Qt::NoPen);
    p.setBrush(QColor(35, 38, 43, 255));
    p.drawRect(0,0,this->width(),this->height());
}

void DownloadWidget::addItem(QString url,QString name,QString iconUrl){
//    qDebug()<<url<<" "<<name;
    index++;
    DownloadItemWidget* item = new DownloadItemWidget(this,iconUrl,name,url,root);
    connect(item,&DownloadItemWidget::on_del_passSignal,this,[=](){
        index--;
        scrollWidget->setFixedSize(QSize(280,10+index*60));
    });
    labelLayout->addWidget(item);
    scrollWidget->setFixedSize(QSize(280,10+index*60));
    items->setWidget(scrollWidget);
}
