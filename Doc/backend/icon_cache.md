## icon cache
* 代码逻辑如下：
    * 每当访问一个网站，**需要前端同学调用一次IconManager::check_local_cache**，将其icon保存到运行目录的**icon_cache**文件夹
    * 前端可以通过传入url.host()来获取addbookmark或者addhistory等的icon字段 
* 接口
    * check_local_cache(const QUrl& url, const QIcon& icon)
        * 每当访问一个页面需要调用一次
        * 用于保存icon至本地
    * get_local_cache(const QUrl& url)
        * 可对目标url调用url.host()传入本接口来获取本地的icon文件路径