# VLC安装说明

## 1. 编译安装支持视频输出的QEMU

- 略。详见[通过 QEMU 仿真 RISC-V 环境并启动 OpenEuler RISC-V 系统](https://github.com/openeuler-mirror/RISC-V/blob/master/doc/tutorials/vm-qemu-oErv.md)
- 注：建议优先考虑发行版提供的软件包或在有能力的情况下自行打包，不鼓励非必要情况的编译安装。镜像的安装部分有所不同，请参考以下镜像的下载安装。

## 2. 系统镜像的使用

### 2.1 镜像下载

#### 2.1.1 下载内容

- 下载 QEMU 目录下的[openeuler-qemu-xfce.qcow2.tar.zst](https://mirror.iscas.ac.cn/openeuler-sig-riscv/openEuler-RISC-V/testing/20220823/v0.1/QEMU/openeuler-qemu-xfce.qcow2.tar.zst), [fw_payload_oe_qemuvirt.elf](https://mirror.iscas.ac.cn/openeuler-sig-riscv/openEuler-RISC-V/testing/20220823/v0.1/QEMU/fw_payload_oe_qemuvirt.elf), [start_vm_xfce.sh](https://mirror.iscas.ac.cn/openeuler-sig-riscv/openEuler-RISC-V/testing/20220823/v0.1/QEMU/start_vm_xfce.sh), 
- [下载地址](https://mirror.iscas.ac.cn/openeuler-sig-riscv/openEuler-RISC-V/testing/20220823/v0.1/QEMU/)
- 下载有音频驱动的内核(QEMU目录下内核没有音频驱动，需要更新内核),
linux环境下下载并解压[内核](http://obs-backend.tarsier-infra.com:82/Factory:/RISC-V:/Kernel/22.03/riscv64/opensbi-qemu-1.0-1.oe2203.riscv64.rpm)软件包，找到 fw_payload_oe_qemuvirt.elf并提取，如若点击链接无反应，可尝试在新标签页打开下载链接。

![figure_68](./images/figure_68.png)

如图，可在下载的rpm包下的"/./boot/"位置中找到此文件，然后选中提取

windows系统下建议参阅附录使用WSL来运行，更新内核也在另一篇文章有其他可行的解决方法

#### 2.1.2 部署和启动

- 确认当前目录内包含 fw_payload_oe_qemuvirt.elf, 磁盘映像压缩包。
- 解压映像压缩包或使用解压工具解压磁盘映像。
- 调整启动参数
- 执行启动脚本

注：解压需要10.7G硬盘空间

```bash
sudo apt install zstd -y
tar -I zstdmt -xvf ./openeuler-qemu-xfce.qcow2.tar.zst
```

- 执行 `bash start_vm_xfce.sh`

注：QEMU下启动Xfce较慢，请耐心等待

脚本图像输出参数方面可能根据宿主机的环境变化而有些不同。若终端报错，可根据终端提醒，对脚本中'-display'与'-device virtio-vga//'两项进行更改，脚本参数更改具体据环境而变，可自行搜索学习，另外的方法为绕过直接图像输出使用vnc或spice等方式登陆远程桌面，详情可见附录(通过 QEMU 仿真 RISC-V 环境并启动 OpenEuler RISC-V 系统)。

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

### 附录及参考文章
[在 WSL 通过 QEMU 仿真 RISC-V 环境并启动 OpenEuler RISC-V 系统](https://github.com/ArielHeleneto/Work-PLCT/tree/master/qemuOnWSL) by [ArielHeleneto](https://github.com/ArielHeleneto)

[通过 QEMU 仿真 RISC-V 环境并启动 OpenEuler RISC-V 系统](https://github.com/ArielHeleneto/Work-PLCT/blob/master/awesomeqemu/README.md) by [ArielHeleneto](https://github.com/ArielHeleneto)
 
