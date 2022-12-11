# DDE 安装说明

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

## 3. 安装 DDE

1. 执行以下指令；

```
dnf install dde
```

> 安装过程中，有些包可能会已经以依赖的形式被安装了，没关系直接跳过。

2. 安装完成提示 `Success` 后关闭 QEMU 模拟器。

```
poweroff
```

## 4. 运行 DDE

1. 使用文本编辑器打开 `preview_start_vm.sh`，在 `-smp` 与 `-kernel` 两行之间插入以下内容，以添加视频及音频输出；

```
-display sdl \
-audiodev pa,id=snd0 \
```

2. 执行启动脚本。

```
bash preview_start_vm.sh
```

> QEMU 模拟器环境下启动 DDE 需要一些时间。