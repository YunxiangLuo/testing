# OpenMPI 使用说明

## 1. 构建 OpenMPI 官方示例程序并测试

### 1.1 准备示例程序

1. 进入源代码的示例程序文件夹

    ```
    cd openmpi-4.1.4/examples
    ```

2. 使用 make 编译测试用代码

    ```
    make all
    ```

### 1.2 测试运行 hello 程序：使用 mpirun 运行 hello_c

```
mpirun -np 4 ./hello_c
```

输出如下：

```
Hello, world, I am 0 of 4
Hello, world, I am 1 of 4
Hello, world, I am 2 of 4
Hello, world, I am 3 of 4
```

### 1.3 测试接收同步消息：使用 mpirun 运行 connectivity_c

```
mpirun -np 4 ./connectivity_c
```

输出如下：

```
Connectivity test on 4 processes PASSED.
```

### 1.4 测试点对点进程通信：使用 mpirun 运行 ring_c

```
mpirun -np 4 ./ring_c
```

输出如下：

```
Process 0 sending 10 to 1, tag 201 (4 processes in ring)
Process 0 sent to 1
Process 0 decremented value: 9
Process 0 decremented value: 8
Process 0 decremented value: 7
Process 0 decremented value: 6
Process 0 decremented value: 5
Process 0 decremented value: 4
Process 0 decremented value: 3
Process 0 decremented value: 2
Process 0 decremented value: 1
Process 0 decremented value: 0
Process 0 exiting
Process 2 exiting
Process 3 exiting
Process 1 exiting
```

## 2. 构建其他程序并测试

1. 获取测试用的仓库

    ```
    git clone https://github.com/mpitutorial/mpitutorial
    ```

2. 进入代码目录

    ```
    cd mpitutorial/tutorials
    ```

### 2.1 测试使用 Scatter 和 Gather 计算平均数

```
./run.py all_avg
```

输出如下：

```
mpirun -n 4  ./mpi-scatter-gather-and-allgather/code/all_avg 100
Avg of all elements from proc 0 is 0.499618
Avg of all elements from proc 1 is 0.499618
Avg of all elements from proc 2 is 0.499618
Avg of all elements from proc 3 is 0.499618
```

### 2.2 测试发送接收消息

```
./run.py ping_pong
```

输出如下：

```
mpirun -n 2  ./mpi-send-and-receive/code/ping_pong
0 sent and incremented ping_pong_count 1 to 1
0 received ping_pong_count 2 from 1
0 sent and incremented ping_pong_count 3 to 1
0 received ping_pong_count 4 from 1
0 sent and incremented ping_pong_count 5 to 1
0 received ping_pong_count 6 from 1
0 sent and incremented ping_pong_count 7 to 1
0 received ping_pong_count 8 from 1
0 sent and incremented ping_pong_count 9 to 1
0 received ping_pong_count 10 from 1
1 received ping_pong_count 1 from 0
1 sent and incremented ping_pong_count 2 to 0
1 received ping_pong_count 3 from 0
1 sent and incremented ping_pong_count 4 to 0
1 received ping_pong_count 5 from 0
1 sent and incremented ping_pong_count 6 to 0
1 received ping_pong_count 7 from 0
1 sent and incremented ping_pong_count 8 to 0
1 received ping_pong_count 9 from 0
1 sent and incremented ping_pong_count 10 to 0
```

### 2.3 测试计算并行排名

```
./run.py random_rank
```

输出如下：

```
mpirun -n 4  ./performing-parallel-rank-with-mpi/code/random_rank 100
Rank for 0.840188 on process 0 - 1
Rank for 0.045389 on process 1 - 0
Rank for 0.914437 on process 2 - 2
Rank for 0.982946 on process 3 - 3
```
