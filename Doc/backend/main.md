#main中window和mainapplication的交互逻辑
* 首先在mainapplication里面实例化model,然后把指针注册到service里
* mainapplication 写一个getwindow实例化一个browserwindow,并show,返回window指针.
* 当browserwindow实例化时通过getservice来获取model指针

这样的话就保证了顺序，然后因为model实例化都是在mainapplication里的，这样就保证了生命周期和程序一致

##特例：history
* 因为history将用户的历史记录保存在内存中，所以hitory和uid一对一，生命周期和当前uid一致
* 即切换用户要删除原有history对象，再新建一个，和其他model类不同（全局）

##关于DEFAULT_USER
* mainapplication 有一个默认user，在mainapplication初始化的时候initDefaultUser()插入默认用户。
* ```
  #define DEFAULT_USR_ID 1
  #define DEFAULT_USR_NAME "default_usr"
  #define DEFAULT_USR_PWD "123456"

  ```
* 因为插入user uid自增，第一个为1
