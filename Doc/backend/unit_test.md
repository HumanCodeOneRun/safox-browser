## how to write your own unit test?
* 可参考bookmarkgroup_test.cpp，每增加一个test记得在tests/CMakeLists.txt上更新一下
* 比如我想加一个history的test，需要命名为history_test.cpp，然后在CMakeLists上加上
```
safox_add_test(history)
```


## how to run a unit test?
```
cmake .. -Dsafox_TEST=ON
cmake --build .
ctest

```
