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

## 3. 编译与安装 MPICH

### 3.1 直接从 `dnf` 安装现有版本

1. 执行以下指令；

```
$ sudo dnf install mpich
```

提示 `Complete!` 即安装完成；

2. 使用编辑器编辑 shell 的 profile；

3. 添加环境变量；

```
export PATH="/usr/lib64/mpich/bin:$PATH"
export LD_LIBRARY_PATH="/usr/lib64/mpich/lib:$LD_LIBRARY_PATH"
```

4. 重载 profile；

5. 执行以下命令，检查环境变量是否正常；

```
$ which mpirun
```

若回显 `/usr/lib64/mpich/bin/mpirun`，则环境变量配置正常，安装完成。

#### 3.2.1 获取源代码

1. 在 [MPI 网站](https://www.mpich.org/downloads/)下载最新稳定版源代码压缩文件 `mpich-4.1.tar.gz`；

2. 解压 \*.tar.gz 文件；

```
$ tar -xzf ./mpich-4.1.tar.gz
```

#### 3.2.2 编译与安装

1. 进入解压输出文件所在文件夹；

2. 执行 `configure` 脚本，安装过程中可能需要某些依赖；

```
$ ./configure --prefix=/opt --disable-fortran
```

3. 执行 `make` 编译脚本；

```
$ make -j$(nproc)
```

4. 安装 MPICH。

```
$ sudo make install
```

#### 3.2.3 配置环境变量

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
