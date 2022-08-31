# VLC安装说明

## 1. 编译安装支持视频输出的QEMU

- 略。详见[通过 QEMU 仿真 RISC-V 环境并启动 OpenEuler RISC-V 系统](https://github.com/openeuler-mirror/RISC-V/blob/master/doc/tutorials/vm-qemu-oErv.md)
- 注：镜像的安装部分有所不同，请参考以下镜像的下载安装。

## 2. 系统镜像的使用

### 2.1 镜像下载

#### 2.1.1 下载内容

- 下载 QEMU 目录下的[openeuler-qemu-xfce.raw.tar.zst](https://mirror.iscas.ac.cn/openeuler-sig-riscv/openEuler-RISC-V/devel/20220808/v0.4/QEMU/openeuler-qemu-xfce.raw.tar.zst)和 [start_vm_xfce.sh](https://mirror.iscas.ac.cn/openeuler-sig-riscv/openEuler-RISC-V/devel/20220808/v0.4/QEMU/start_vm_xfce.sh)
- 下载地址 [https://mirror.iscas.ac.cn/openeuler-sig-riscv/openEuler-RISC-V/devel/20220808/v0.4/QEMU/](https://mirror.iscas.ac.cn/openeuler-sig-riscv/openEuler-RISC-V/devel/20220808/v0.4/QEMU/)
- 下载有音频驱动的内核(目录下内核没有音频驱动，需要更新内核),
下载[内核](http://obs-backend.tarsier-infra.com:82/Factory:/RISC-V:/Kernel/22.03/riscv64/opensbi-qemu-1.0-1.oe2203.riscv64.rpm)软件包，找到 fw_payload_oe_qemuvirt.elf并提取。


#### 2.1.2 部署和启动

- 确认当前目录内包含 fw_payload_oe_qemuvirt.elf, 磁盘映像压缩包。
- 解压映像压缩包或使用解压工具解压磁盘映像。
- 调整启动参数
- 执行启动脚本

注：解压需要10.7G硬盘空间

```bash
sudo apt install zstd -y
tar -I zstdmt -xvf ./openeuler-qemu-xfce.raw.tar.zst
```

- 执行 `bash start_vm_xfce.sh`

注：QEMU下启动Xfce较慢，请耐心等待

   若终端提示
```bash
qemu-system-riscv64 - 'virtio-vga-gl' is not a valid device model name
```
则可将启动脚本的'-device virtio-vga \\' 一行更改为  'device virtio-gpu \\'

## 3. 安装与启动VLC

### 3.1 安装VLC

- 执行下列指令

```bash
dnf install vlc
```

- 安装过程中，有些包可能会已经以依赖的形式被安装了,请忽略此类信息。


### 3.2 启动vlc

- Xfce桌面下打开终端，输入`vlc` 启动 VLC。

```shell
vlc
```

- 点击vlc图标启动VLC，见Application->Multimedia，或Application->Multimedia->vlc
