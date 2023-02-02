# MPICH 安装说明

## 1. 安装支持 RISC-V 架构及视频输出的 QEMU 模拟器

使用发行版提供的预编译软件包。

```
dnf install qemu-system-riscv
```

## 2. 系统镜像的使用

### 2.1 镜像下载

在[镜像源](https://mirror.iscas.ac.cn/openeuler-sig-riscv/openEuler-RISC-V/preview/openEuler-22.03-V2-riscv64/QEMU/)下载文件 `fw_payload_oe_qemuvirt.elf`、`openEuler-22.03-V2-base-qemu-preview.qcow2.tar.zst` 与 `start_vm.sh` ，并放置在同一个文件夹内，路径不可含有中文。

### 2.2 部署与启动

1. 解压 \*.tar.zst 文件；

```
tar -I zstdmt -xvf ./openEuler-22.03-V2-base-qemu-preview.qcow2.tar.zst
```

2. 执行启动脚本；

```
bash start_vm.sh
```

3. 登录用户，默认的用户名为 `openeuler` ，密码为 `openEuler12#$`。

## 3. 编译与安装 OpenMPI

### 3.1 获取源代码

1. 在 [RDMA-Core GitHub 仓库](https://github.com/linux-rdma/rdma-core/releases/)下载最新稳定版源代码压缩文件 `rdma-core-44.0.tar.gz`；

2. 解压 \*.tar.gz 文件；

```
$ tar -xzf ./rdma-core-44.0.tar.gz
```

### 3.2 编译与安装

1. 进入解压输出文件所在文件夹；

2. 执行 `build.sh` 脚本，安装过程中需要 CMake 和常用编译工具；

```
$ ./build.sh
```

3. 执行以下命令，检查编译所生成的文件。

```
$ cd build && ls
```
