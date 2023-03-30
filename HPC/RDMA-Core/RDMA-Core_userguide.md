# RDMA-Core 使用说明

## 1. 构建测试环境与程序

1. 在之前的 build 目录中，执行以下命令，clone 以下 GitHub 仓库；

```
$ git clone https://github.com/animeshtrivedi/rdma-example.git test1
```

2. 执行以下命令，进入 `test1` 文件夹；

```
$ cd test1
```

3. 执行以下命令，修改 CMake 配置；
```
$ sed -i "s/\/home\/atr\/local/\.\./" CMakeLists.txt
```

4. 执行以下命令开始编译；
```
$ cmake . && make
```

5. 在本机上模拟 RDMA 环境（需要两个网卡，包括 loopback）；

6. 执行以下命令加载模块；

```
$ sudo modprobe siw
```

7. 执行以下命令，添加第一张网卡；

```
$ sudo rdma link add siw0 type siw netdev lo
```

8. 执行以下命令，添加第二张网卡（可执行 `ip a` 查询当前网卡名称）；

```
$ sudo rdma link add siw1 type siw netdev <网卡名称>
```

9. 执行以下命令，后台运行服务端；

```
$ nohup ./bin/rdma_server &
```

10. 执行以下命令，测试客户端通信结果；

```
$ ./bin/rdma_client -a <本机 IP 地址> -s hello
```

回显如下，服务端自动退出。

```
Passed string is : hello , with count 5
Trying to connect to server at : 123.123.123.123 port: 20886
The client is connected successfully
---------------------------------------------------------
buffer attr, addr: 0x562563c546e0 , len: 5 , stag : 0x9c148800
---------------------------------------------------------
...
SUCCESS, source and destination buffers match
Client resource clean up is complete
[1]  + done       nohup ./bin/rdma_server
```
