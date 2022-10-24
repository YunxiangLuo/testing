# LibreOffice安装说明


## 1. 编译安装支持视频输出的QEMU

- 略。详见[通过 QEMU 仿真 RISC-V 环境并启动 OpenEuler RISC-V 系统](https://github.com/openeuler-mirror/RISC-V/blob/master/doc/tutorials/vm-qemu-oErv.md)
- 注：建议优先考虑发行版提供的软件包或在有能力的情况下自行打包，不鼓励非必要情况的编译安装。镜像的安装部分有所不同，请参考以下镜像的下载安装。

## 2. 系统镜像的使用

[使用Unmatched开发板安装RISC-V](https://gitee.com/yunxiangluo/Learn-Risc-V-openEuler-Programming/blob/master/chapter1/lab4/README.md)

### 2.1 镜像下载

#### 2.1.1 下载内容

- 下载 QEMU 目录下的[openEuler-22.03-V1-riscv64-qemu-xfce.qcow2.tar.zst](https://mirror.iscas.ac.cn/openeuler-sig-riscv/openEuler-RISC-V/preview/openEuler-22.03-V1-riscv64/QEMU/openEuler-22.03-V1-riscv64-qemu-xfce.qcow2.tar.zst), [preview_start_vm_xfce.sh](https://mirror.iscas.ac.cn/openeuler-sig-riscv/openEuler-RISC-V/preview/openEuler-22.03-V1-riscv64/QEMU/preview_start_vm_xfce.sh),[fw_payload_oe_qemuvirt.elf](https://mirror.iscas.ac.cn/openeuler-sig-riscv/openEuler-RISC-V/preview/openEuler-22.03-V1-riscv64/QEMU/fw_payload_oe_qemuvirt.elf)
- [下载地址](https://mirror.iscas.ac.cn/openeuler-sig-riscv/openEuler-RISC-V/preview/openEuler-22.03-V1-riscv64/QEMU/)


#### 2.1.2 部署和启动

#### 2.1.21 直接启动支持xfce的脚本

>已验证启动脚本在 Ubuntu22.04 环境下正常运行 

- 确认当前目录内包含`fw_payload_oe_qemuvirt.elf`, 磁盘映像压缩包，和启动脚本`preview_start_vm_xfce.sh`。
- 解压映像压缩包或使用解压工具解压磁盘映像。
- 调整启动参数
- 执行启动脚本

注：解压需要10.7G硬盘空间

```bash
sudo apt install zstd -y
tar -I zstd -xvf openEuler-22.03-V1-riscv64-qemu-xfce.qcow2.tar.zst
```

- 执行 `bash preview_start_vm_xfce.sh`

注：QEMU下启动Xfce较慢，请耐心等待


## 3. 安装与启动LibreOffice

### 3.1 安装LibreOffice

LibreOffice 应当已经预装在系统中。如果没有安装请使用对应的包管理器安装。

```bash
dnf install libreoffice
```

### 3.2 启动LibreOffice Writer

- Xfce桌面下点击 Application -> Office -> LibreOffice Writer 启动。



### 附录及参考文章
[在 WSL 通过 QEMU 仿真 RISC-V 环境并启动 OpenEuler RISC-V 系统](https://github.com/ArielHeleneto/Work-PLCT/tree/master/qemuOnWSL) by [ArielHeleneto](https://github.com/ArielHeleneto)

[通过 QEMU 仿真 RISC-V 环境并启动 OpenEuler RISC-V 系统](https://github.com/ArielHeleneto/Work-PLCT/blob/master/awesomeqemu/README.md) by [ArielHeleneto](https://github.com/ArielHeleneto)