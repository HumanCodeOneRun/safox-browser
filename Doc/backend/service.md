## service与生命周期：
* mainapplication有一个全局的servicelocator，初始化时向其加入实例化的model类指针作为service。
* mainwindow获得一个servicelocator，来获取service
* 这样的话就保证了顺序，然后因为model实例化都是在mainapplication里的，这样就保证了生命周期和程序一致

##特例：history
* 因为history将用户的历史记录保存在内存中，所以hitory和uid一对一，生命周期和当前uid一致
* 即切换用户要删除原有history对象，再新建一个，和其他model类不同（全局）