## 连接与线程：
* 一个dao对应一个连接，用QThreadStorage存储连接信息
* 一个线程对应一个连接，是QT的规定。
* 工作线程每处理一个task调用dao进行数据库操作时，都会在当前线程获取连接。