## DatabaseTaskScheduler：
* 本质是一个含有自定义多个线程的线程池，默认为4线程
    1. 维护一个任务队列
    2. 所有数据库操作都加入到任务队列中
    3. 维护数据库中带有连接的线程，用他们来执行数据库操作
* 工作线程每处理一个task调用dao进行数据库操作时，都会在当前线程获取连接。
* 实现数据库并发操作

### 使用：
* 整个应用共享一个，生命周期应与主程序相同，使用前需要先实例化instance,然后调用instance.run()

各个model类使用scheduler instance完成数据库操作

获取数据库操作返回值使用异步操作：
    把数据库操作封装成回调函数加入任务队列
    使用promise存储返回值
    使用future从promise获取返回值

