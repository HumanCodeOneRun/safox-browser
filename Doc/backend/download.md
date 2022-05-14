## Downloads Module

* 前端同学对于每个view，需要connect一下downloadrequest与on_requested，并将获取到的用户自定义信息传递到on_requested中

* 另外三个则是下载界面的删除、暂停、恢复，可能需要每次记录一下每个下载的url用来传参

### slots
```c++
void on_requested(QWebEngineDownloadRequest* request, const QUrl& url, const QUrl& icon,const QString& save_path,  const QString& name);
void on_delete(const QString& url);
void on_pause(const QString& url);
void on_resume(const QString& url);

// 用来获取下载列表
QVector< std::shared_ptr<DownloadItem> > get_items();
```

* 几个信号是用于前端展示下载效果的
    1. download_items_num_changed是新增/删除了下载任务，需要刷新一下前端展示页面的信号

    2. bytes_received_changed是实时的已下载数据数，单位为bytes

    3. bytes_total_changed是获取下载时的总数据数，当下载开始会发出这个信号，单位为bytes

    4. finish_changed是下载完成的信号
### signals
```c++
// downloadmanager.h
void download_items_num_changed();

// downloaditem.h
void bytes_received_changed(qint64);
void bytes_total_changed(qint64);
void finish_changed(bool);
```