# OpenMPI 安装说明

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

3. 登录用户，默认的用户名为 `openeuler` ，密码为 `openEuler12#$`。注意，OpenMPI 默认不允许使用 `root` 用户来运行。

## 3. 编译与安装 OpenMPI

### 3.1 获取源代码

1. 在 [OpenMPI 网站](https://www.open-mpi.org/software/)下载最新稳定版源代码压缩文件 `openmpi-4.1.4.tar.bz2`；

2. 解压 \*.tar.bz2 文件；

```
$ tar -xjf ./openmpi-4.1.4.tar.bz2
```

### 3.2 编译与安装

1. 进入解压输出文件所在文件夹；

2. 安装所需依赖，个别依赖可能会提示已经安装，可忽略；

```
$ sudo dnf install binutils-devel gcc-c++ autoconf automake libtool
```

3. 执行 `configure` 脚本；

```
$ ./configure --prefix=/opt
```

4. 执行 `make` 编译脚本；

```
$ make -j$(nproc) all
```

5. 安装 OpenMPI。

```
$ sudo make install
```

### 3.3 配置环境变量

1. 使用编辑器编辑 shell 的 profile；

2. 添加环境变量；

```
export PATH="/opt/bin:$PATH"
export LD_LIBRARY_PATH="/opt/lib:$LD_LIBRARY_PATH"
```

3. 重载 profile；

4. 执行以下命令，检查环境变量是否正常；

```
$ which mpirun
```

若回显 `/opt/bin/mpirun`，则环境变量配置正常，安装完成。
