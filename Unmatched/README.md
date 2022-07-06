# openEuler RISC-V 镜像 Unmatched 开发板安装测试 

预计测试结果：刷写成功，启动成功，启动Xfce桌面成功。

实际测试结果：刷写成功，串口启动成功，未能进入Xfce桌面（HDMI独立显示卡接显示器）。

## 1 准备工作

### 1.1 准备硬件

1）Unmatched开发板：由Unmatched获取得到开发板。

2）64G micro-sd卡及读卡器：SanDisk TF/MicroSD卡，容量64GB，速度U1，带读卡器。

3）MicroUSB线。

4）电源适配器。

5）连接Unmatched开发板的MicroUSB接口到计算机USB接口。

如下图：

![figure_1](./images/figure_1.jpg)

### 1.2 准备系统镜像

Unmatched的系统镜像下载连接地址如下： https://mirror.iscas.ac.cn/openeuler-sig-riscv/openEuler-RISC-V/testing/20220622/v0.2/Unmatched/

考虑到要安装验证Firefox浏览器，我们可以下载openeuler-unmatched-xfce.img.tar.zst，连接如下： https://mirror.iscas.ac.cn/openeuler-sig-riscv/openEuler-RISC-V/testing/20220622/v0.2/Unmatched/openeuler-unmatched-xfce.img.tar.zst

其他文件均无需下载。

```bash
wget https://mirror.iscas.ac.cn/openeuler-sig-riscv/openEuler-RISC-V/testing/20220622/v0.2/Unmatched/openeuler-unmatched-xfce.img.tar.zst
```

### 1.3 刷写镜像

1. 解压镜像文件

```bash
sudo apt install zstd -y
tar -I zstdmt -xvf ./openeuler-unmatched-xfce.img.tar.zst
```

2. 镜像刷写

将64G micro-sd卡装入读卡器后，插入笔记本电脑。笔记本电脑通常带一个硬盘，所以sd卡对应设备是/dev/sdb

```bash
sudo dd if=./openeuler-unmatched-xfce.img of=/dev/sdb bs=1M iflag=fullblock oflag=direct conv=fsync status=progress
```

### 1.4 安装串口调试软件

1）将MicroUSB接线连接到电脑USB口。

2）检查设备管理器中的COM端口，会添加2个COM端口，选择最后一个，如这里COM6。

![figure_2](./images/figure_2.png)

3）使用Xmodem安装固件。

安装teraterm，https://mobaxterm.mobatek.net/download.html

    选择菜单setup->Serial port setup
    Speed设置为115200
    Data设置为8bit
    Paritv设置为none
    Stoo bits设置为1bit
    Flowcontrol设置为none

![figure_4](./images/figure_4.png)

### 1.5 启动Unmatched

将64G micro-sd卡装入Unmatched sd卡槽，连接tpye-c电源启动，启动报错如下

```
bootloader version:211102-0b86f96
ddr 0x00000000, 1M test
ddr 0x00100000, 2M test
DDR clk 2133M,Version: 211102-d086aee                                                                                    0 crc flash: 5595e732, crc ddr: 5595e732
crc check PASSED

bootloader.

OpenSBI v1.0
   ____                    _____ ____ _____
  / __ \                  / ____|  _ \_   _|
 | |  | |_ __   ___ _ __ | (___ | |_) || |
 | |  | | '_ \ / _ \ '_ \ \___ \|  _ < | |
 | |__| | |_) |  __/ | | |____) | |_) || |_
  \____/| .__/ \___|_| |_|_____/|____/_____|
        | |
        |_|

Platform Name             : StarFive VisionFive V1
Platform Features         : medeleg
Platform HART Count       : 2
Platform IPI Device       : aclint-mswi
Platform Timer Device     : aclint-mtimer @ 6250000Hz
Platform Console Device   : uart8250
Platform HSM Device       : ---
Platform Reboot Device    : ---
Platform Shutdown Device  : ---
Firmware Base             : 0x80000000
Firmware Size             : 296 KB
Runtime SBI Version       : 0.3

Domain0 Name              : root
Domain0 Boot HART         : 1
Domain0 HARTs             : 0*,1*
Domain0 Region00          : 0x0000000002000000-0x000000000200ffff (I)
Domain0 Region01          : 0x0000000080000000-0x000000008007ffff ()
Domain0 Region02          : 0x0000000000000000-0xffffffffffffffff (R,W,X)
Domain0 Next Address      : 0x0000000080200000
Domain0 Next Arg1         : 0x0000000082200000
Domain0 Next Mode         : S-mode
Domain0 SysReset          : yes

Boot HART ID              : 1
Boot HART Domain          : root
Boot HART ISA             : rv64imafdcsux
Boot HART Features        : scounteren,mcounteren
Boot HART PMP Count       : 16
Boot HART PMP Granularity : 4096
Boot HART PMP Address Bits: 36
Boot HART MHPM Count      : 2
Boot HART MIDELEG         : 0x0000000000000222
Boot HART MEDELEG         : 0x000000000000b109


U-Boot 2022.01-rc4-VisionFive-g0c08d335c5 (Dec 30 2021 - 08:30:15 +0800)StarFive

CPU:   rv64imafdc
Model: StarFive VisionFive V1
DRAM:  8 GiB
MMC:   mmc@10000000: 0, mmc@10010000: 1
Loading Environment from SPIFlash... cadence_spi spi@11860000: Can't get reset: -524
SF: Detected gd25lq128 with page size 256 Bytes, erase size 4 KiB, total 16 MiB
*** Warning - bad CRC, using default environment

StarFive EEPROM format v1

--------EEPROM INFO--------
Vendor : StarFive Technology Co., Ltd.
Product full SN: VF7100A1-2206-D008E000-0000035C
data version: 0x1
PCB revision: 0x1
BOM revision: A
Ethernet MAC address: 6c:cf:39:00:03:5b
--------EEPROM INFO--------

In:    serial@12440000
Out:   serial@12440000
Err:   serial@12440000
Net:   dwmac.10020000
MMC CD is 0x0, force to True.
MMC CD is 0x0, force to True.
switch to partitions #0, OK
mmc0 is current device
MMC CD is 0x0, force to True.
MMC CD is 0x0, force to True.
Can't set block device
** Invalid partition 3 **
Couldn't find partition mmc 0:3
Can't set block device
Autoboot in 2 seconds
dwmac.10020000 Waiting for PHY auto negotiation to complete......... TIMEOUT !
Could not initialize PHY dwmac.10020000
dwmac.10020000 Waiting for PHY auto negotiation to complete......... TIMEOUT !
Could not initialize PHY dwmac.10020000
MMC CD is 0x0, force to True.
MMC CD is 0x0, force to True.
switch to partitions #0, OK
mmc0 is current device
Scanning mmc 0:1...
Found /boot/extlinux/extlinux.conf
Invalid pxefile address: /boot/extlinux/extlinux.conf
SCRIPT FAILED: continuing...
MMC CD is 0x1, force to True.
Card did not respond to voltage select! : -110
Disk mmc@10010000.blk not ready
EFI boot manager: Cannot load any image
VisionFive #


```
