# 遗传算法求解车辆路径问题

毛一琛 唐海洪



## 文件说明

`ga_vrp.cpp` ：算法代码

`test` ：用以测试的可执行文件

`data` ：测试数据

`out`：测试结果

`variations_article` ：扩展问题的部分参考文献



## 测试方法

用如下命令测试：

` ./test {Run,Test,Ortool} {0,1,2,3,4,5,6,7}`

`Run` 、`Test` 、 `Ortool` 分别代表选用我们的程序、测试程序、or-tool程序

第二个参数选 `0` 是测试所有数据，`1~7` 分别是测试对应编号的数据

注意 `./test Run 0` 用时较长，本地测试时间在11分钟左右
