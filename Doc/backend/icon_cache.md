## icon cache
* 代码逻辑如下：
    * 当访问一个网站，就会自动将其icon保存到运行目录的**icon_cache**文件夹
    * 文件名是url的host+.png
    * 前端可以通过传入url.host()+".png"来设置addbookmark或者addhistory等的icon字段 