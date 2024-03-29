# MySQL 安装说明

## 1. 安装支持 RISC-V 架构及视频输出的 QEMU 模拟器

使用发行版提供的预编译软件包。

```
dnf install qemu-system-riscv
```

## 2. 系统镜像的使用

### 2.1 镜像下载

在[镜像源](https://mirror.iscas.ac.cn/openeuler-sig-riscv/openEuler-RISC-V/preview/openEuler-22.03-V1-riscv64/QEMU/)下载文件 `fw_payload_oe_qemuvirt.elf`、`openEuler-22.03-V1-riscv64-qemu.qcow2.tar.zst` 与 `preview_start_vm.sh` ，并放置在同一个文件夹内，路径不可含有中文。

### 2.2 部署与启动

1. 解压 \*.tar.zst 文件；

```
tar -I zstdmt -xvf ./openEuler-22.03-V1-riscv64-qemu.qcow2.tar.zst
```

2. 执行启动脚本；

```
bash preview_start_vm.sh
```

3. 登录用户，默认的用户名为 `root` ，密码为 `openEuler12#$`。

## 3. 安装 MySQL

执行以下指令。

```
# dnf install mysql-server
```

> 安装过程中，有些包可能会已经以依赖的形式被安装了，没关系直接跳过。

提示 `Complete!` 即安装完成。

## 4. 运行 MySQL

执行以下指令，使 MySQL 服务启动。

```
# systemctl start mysqld
```