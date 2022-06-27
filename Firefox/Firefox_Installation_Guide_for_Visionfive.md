# Firefox for openeuler on Visionfive安装说明

注：感谢袁老师！本文档来源于https://gitee.com/samuel_yuan/riscv-openeuler-visionfive/blob/master/chapter2-Verify-openeuler-GUI-APP-on-visionfive/Verify-firefox-for-openeuler-on-visionfive.md

在Visionfive开发板上的openeuler操作系统中安装Firefox浏览器。

## 1. 系统安装

### 1.1 系统镜像准备

随着openeuler的更新，社区提供了unmatched、D1、visionfive等三种系统镜像，其中visionfive的系统镜像下载连接地址如下：
https://mirror.iscas.ac.cn/openeuler-sig-riscv/openEuler-RISC-V/testing/20220622/v0.2/Visionfive/

考虑到要安装验证Firefox浏览器，我们可以下载openeuler-visionfive-xfce.img.tar.zst，连接如下：
https://mirror.iscas.ac.cn/openeuler-sig-riscv/openEuler-RISC-V/testing/20220622/v0.2/Visionfive/openeuler-visionfive-xfce.img.tar.zst

其他文件均无需下载。

### 1.2 安装系统镜像

1）将下载文件解压缩为镜像文件：openeuler-visionfive-xfce.img

2）查看镜像文件的分区状况：

```bash
fdisk -lu openeuler-visionfive-xfce.img
```

显示如下信息：

```bash
isk openeuler-visionfive-xfce.img：6 GiB，6442450944 字节，12582912 个扇区
单元：扇区 / 1 * 512 = 512 字节
扇区大小(逻辑/物理)：512 字节 / 512 字节
I/O 大小(最小/最佳)：512 字节 / 512 字节
磁盘标签类型：gpt
磁盘标识符：A00236E5-7867-4B5F-B323-5556FA50534B

设备                           起点     末尾     扇区 大小 类型
openeuler-visionfive-xfce.img1  256 12582878 12582623   6G 未知
```

3）计算偏移量
起点是256扇区单元，每单元512字节，计算得出偏移量。
256*512=131072

4）挂载镜像文件到rootfs目录中

```bash
sudo mount -o loop,offset=131072 openeuler-visionfive-xfce.img /home/riscv/riscv64-linux/rootfs/
```

5）拷贝rootfs中的系统文件至micro sd卡的系统分区中

```bash
sudo cp -r /home/riscv/riscv64-linux/rootfs/* /media/riscv/rootfs/
sync
```

6）拷贝rootfs/boot中的相关文件至micro sd卡的启动分区中

```bash
sudo cp -r /home/riscv/riscv64-linux/rootfs/boot/jh7100-starfive-visionfive-v1.dtb /media/riscv/715D-A517/
sudo cp -r /home/riscv/riscv64-linux/rootfs/boot/Image.gz /media/riscv/715D-A517/
```

7）文件系统复制完成取消挂载

```bash
sudo umount /home/riscv/riscv64-linux/rootfs
```

## 2. 安装Firefox浏览器

### 2.1 准备工作

1）将准备好的micro sd卡插入visionfive开发板，并启动。考虑到我们运行的文件系统已包含xfce，如果开发板连接了显示器，那么可以看到启动系统会自动进入到xfce的用户登陆界面。

root 默认密码为 openEuler12#$

2）连接visionfive开发板的40-Pin GPIO端和Usb转uart串口通信模块，通过MobaXterm访问系统。

3）正常登陆后，设置时间，如：

```bash
date -s "2022-06-25 21:15:50"
```

### 2.2 安装Firefox浏览器

```bash
dnf install firefox
```
