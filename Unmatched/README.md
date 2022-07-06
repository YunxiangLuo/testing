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
U-Boot SPL 2021.07-dirty (Dec 09 2021 - 13:57:38 +0800)
Trying to boot from MMC1


U-Boot 2021.07-dirty (Dec 09 2021 - 13:57:38 +0800)

CPU:   rv64imafdc
Model: SiFive HiFive Unmatched A00
DRAM:  16 GiB
MMC:   spi@10050000:mmc@0: 0
Loading Environment from nowhere... OK
EEPROM: SiFive PCB EEPROM format v1
Product ID: 0002 (HiFive Unmatched)
PCB revision: 3
BOM revision: B
BOM variant: 0
Serial number: SF105SZ212200757
Ethernet MAC address: 70:b3:d5:92:f9:c6
CRC: b4ce16dc
In:    serial@10010000
Out:   serial@10010000
Err:   serial@10010000
Model: SiFive HiFive Unmatched A00
Net:   eth0: ethernet@10090000
Hit any key to stop autoboot:  0
PCIE-0: Link up (Gen1-x8, Bus0)

Device 0: unknown device
starting USB...
Bus xhci_pci: Register 4000840 NbrPorts 4
Starting the controller
USB XHCI 1.00
scanning bus xhci_pci for devices... 5 USB Device(s) found
       scanning usb for storage devices... 0 Storage Device(s) found

Device 0: unknown device
switch to partitions #0, OK
mmc0 is current device
Scanning mmc 0:3...
Found /boot/extlinux/extlinux.conf
Retrieving file: /boot/extlinux/extlinux.conf
399 bytes read in 6 ms (64.5 KiB/s)
1:      Linux openEuler-riscv
Retrieving file: /boot/Image
21457920 bytes read in 18130 ms (1.1 MiB/s)
append: earlyprintk rw root=/dev/mmcblk0p3 rootfstype=ext4 rootwait console=ttySIF0,115200 LANG=en_US.UTF-8 earlycon
Retrieving file: /boot/hifive-unmatched-a00.dtb
10931 bytes read in 15 ms (710.9 KiB/s)
Moving Image from 0x84000000 to 0x80200000, end=816de000
## Flattened Device Tree blob at 88000000
   Booting using the fdt blob at 0x88000000
   Using Device Tree in place at 0000000088000000, end 0000000088005ab2

Starting kernel ...

[    0.000000] Linux version 5.13.19 (abuild@oerv-obs-worker-08) (gcc_old (GCC) 10.3.1, GNU ld (GNU Binutils) 2.37) #1 SMP Thu Jun 9 07:00:51 UTC 2022
[    0.000000] OF: fdt: Ignoring memory range 0x80000000 - 0x80200000
[    0.000000] Machine model: SiFive HiFive Unmatched A00
[    0.000000] earlycon: sifive0 at MMIO 0x0000000010010000 (options '')
[    0.000000] printk: bootconsole [sifive0] enabled
[    0.000000] efi: UEFI not found.
[    0.000000] Zone ranges:
[    0.000000]   DMA32    [mem 0x0000000080200000-0x00000000ffffffff]
[    0.000000]   Normal   [mem 0x0000000100000000-0x000000047fffffff]
[    0.000000] Movable zone start for each node
[    0.000000] Early memory node ranges
[    0.000000]   node   0: [mem 0x0000000080200000-0x000000047fffffff]
[    0.000000] Initmem setup node 0 [mem 0x0000000080200000-0x000000047fffffff]
[    0.000000] On node 0, zone DMA32: 512 pages in unavailable ranges
[    0.000000] SBI specification v0.2 detected
[    0.000000] SBI implementation ID=0x1 Version=0x9
[    0.000000] SBI TIME extension detected
[    0.000000] SBI IPI extension detected
[    0.000000] SBI RFENCE extension detected
[    0.000000] software IO TLB: mapped [mem 0x00000000fbfff000-0x00000000fffff000] (64MB)
[    0.000000] SBI v0.2 HSM extension detected
[    0.000000] CPU with hartid=0 is not available
[    0.000000] CPU with hartid=0 is not available
[    0.000000] riscv: ISA extensions acdfim
[    0.000000] riscv: ELF capabilities acdfim
[    0.000000] percpu: Embedded 28 pages/cpu s74648 r8192 d31848 u114688
[    0.000000] Built 1 zonelists, mobility grouping on.  Total pages: 4128264
[    0.000000] Kernel command line: earlyprintk rw root=/dev/mmcblk0p3 rootfstype=ext4 rootwait console=ttySIF0,115200 LANG=en_US.UTF-8 earlycon
[    0.000000] Dentry cache hash table entries: 2097152 (order: 12, 16777216 bytes, linear)
[    0.000000] Inode-cache hash table entries: 1048576 (order: 11, 8388608 bytes, linear)
[    0.000000] Sorting __ex_table...
[    0.000000] mem auto-init: stack:off, heap alloc:off, heap free:off
[    0.000000] Memory: 16383264K/16775168K available (12854K kernel code, 2308K rwdata, 4960K rodata, 823K init, 409K bss, 391904K reserved, 0K cma-reserved)
[    0.000000] SLUB: HWalign=64, Order=0-3, MinObjects=0, CPUs=4, Nodes=1
[    0.000000] ftrace: allocating 45223 entries in 177 pages
[    0.000000] ftrace: allocated 177 pages with 4 groups
[    0.000000] trace event string verifier disabled
[    0.000000] rcu: Hierarchical RCU implementation.
[    0.000000] rcu:     RCU restricting CPUs from NR_CPUS=8 to nr_cpu_ids=4.
[    0.000000]  Rude variant of Tasks RCU enabled.
[    0.000000]  Tracing variant of Tasks RCU enabled.
[    0.000000] rcu: RCU calculated value of scheduler-enlistment delay is 25 jiffies.
[    0.000000] rcu: Adjusting geometry for rcu_fanout_leaf=16, nr_cpu_ids=4
[    0.000000] NR_IRQS: 64, nr_irqs: 64, preallocated irqs: 0
[    0.000000] CPU with hartid=0 is not available
[    0.000000] riscv-intc: unable to find hart id for /cpus/cpu@0/interrupt-controller
[    0.000000] riscv-intc: 64 local interrupts mapped
[    0.000000] plic: interrupt-controller@c000000: mapped 69 interrupts with 4 handlers for 9 contexts.
[    0.000000] random: get_random_bytes called from start_kernel+0x438/0x616 with crng_init=0
[    0.000000] riscv_timer_init_dt: Registering clocksource cpuid [0] hartid [3]
[    0.000000] clocksource: riscv_clocksource: mask: 0xffffffffffffffff max_cycles: 0x1d854df40, max_idle_ns: 3526361616960 ns
[    0.000002] sched_clock: 64 bits at 1000kHz, resolution 1000ns, wraps every 2199023255500ns
[    0.008542] Console: colour dummy device 80x25
[    0.012858] Calibrating delay loop (skipped), value calculated using timer frequency.. 2.00 BogoMIPS (lpj=4000)
[    0.022851] pid_max: default: 32768 minimum: 301
[    0.028418] Mount-cache hash table entries: 32768 (order: 6, 262144 bytes, linear)
[    0.036097] Mountpoint-cache hash table entries: 32768 (order: 6, 262144 bytes, linear)
[    0.045992] ASID allocator disabled
[    0.048887] rcu: Hierarchical SRCU implementation.
[    0.053832] EFI services will not be available.
[    0.058491] smp: Bringing up secondary CPUs ...
[    0.064995] smp: Brought up 1 node, 4 CPUs
[    0.071909] devtmpfs: initialized
[    0.077316] clocksource: jiffies: mask: 0xffffffff max_cycles: 0xffffffff, max_idle_ns: 7645041785100000 ns
[    0.086346] futex hash table entries: 1024 (order: 4, 65536 bytes, linear)
[    0.094191] NET: Registered protocol family 16
[    0.098372] thermal_sys: Registered thermal governor 'step_wise'
[    0.182066] raid6: int64x8  gen()   701 MB/s
[    0.259642] raid6: int64x8  xor()   482 MB/s
[    0.327759] raid6: int64x4  gen()  1141 MB/s
[    0.395834] raid6: int64x4  xor()   642 MB/s
[    0.463945] raid6: int64x2  gen()  1103 MB/s
[    0.532020] raid6: int64x2  xor()   649 MB/s
[    0.600168] raid6: int64x1  gen()   776 MB/s
[    0.668223] raid6: int64x1  xor()   484 MB/s
[    0.671712] raid6: using algorithm int64x4 gen() 1141 MB/s
[    0.677191] raid6: .... xor() 642 MB/s, rmw enabled
[    0.682055] raid6: using intx1 recovery algorithm
[    0.686915] iommu: Default domain type: Translated
[    0.691827] vgaarb: loaded
[    0.694614] SCSI subsystem initialized
[    0.698399] usbcore: registered new interface driver usbfs
[    0.703623] usbcore: registered new interface driver hub
[    0.708846] usbcore: registered new device driver usb
[    0.713968] EDAC MC: Ver: 3.0.0
[    0.717361] Advanced Linux Sound Architecture Driver Initialized.
[    0.724160] clocksource: Switched to clocksource riscv_clocksource
[    0.830387] VFS: Disk quotas dquot_6.6.0
[    0.833652] VFS: Dquot-cache hash table entries: 512 (order 0, 4096 bytes)
[    0.846674] NET: Registered protocol family 2
[    0.857532] IP idents hash table entries: 262144 (order: 9, 2097152 bytes, linear)
[    0.879247] tcp_listen_portaddr_hash hash table entries: 8192 (order: 5, 131072 bytes, linear)
[    0.887768] TCP established hash table entries: 131072 (order: 8, 1048576 bytes, linear)
[    0.899657] TCP bind hash table entries: 65536 (order: 8, 1048576 bytes, linear)
[    0.910601] TCP: Hash tables configured (established 131072 bind 65536)
[    0.919056] MPTCP token hash table entries: 16384 (order: 6, 393216 bytes, linear)
[    0.926464] UDP hash table entries: 8192 (order: 6, 262144 bytes, linear)
[    0.933813] UDP-Lite hash table entries: 8192 (order: 6, 262144 bytes, linear)
[    0.941746] NET: Registered protocol family 1
[    0.946354] RPC: Registered named UNIX socket transport module.
[    0.951542] RPC: Registered udp transport module.
[    0.956215] RPC: Registered tcp transport module.
[    0.960898] RPC: Registered tcp NFSv4.1 backchannel transport module.
[    0.967330] NET: Registered protocol family 44
[    0.971766] PCI: CLS 0 bytes, default 64
[    0.976496] Initialise system trusted keyrings
[    0.980385] workingset: timestamp_bits=46 max_order=22 bucket_order=0
[    0.994365] NFS: Registering the id_resolver key type
[    0.998680] Key type id_resolver registered
[    1.002824] Key type id_legacy registered
[    1.006919] nfs4filelayout_init: NFSv4 File Layout Driver Registering...
[    1.013511] nfs4flexfilelayout_init: NFSv4 Flexfile Layout Driver Registering...
[    1.020890] Installing knfsd (copyright (C) 1996 okir@monad.swb.de).
[    1.028609] SGI XFS with ACLs, security attributes, realtime, scrub, repair, quota, no debug enabled
[    1.038502] 9p: Installing v9fs 9p2000 file system support
[    1.077085] NET: Registered protocol family 38
[    1.080775] xor: measuring software checksum speed
[    1.089325]    8regs           :  2610 MB/sec
[    1.096689]    8regs_prefetch  :  2608 MB/sec
[    1.103796]    32regs          :  2793 MB/sec
[    1.110908]    32regs_prefetch :  2793 MB/sec
[    1.114491] xor: using function: 32regs_prefetch (2793 MB/sec)
[    1.120314] Key type asymmetric registered
[    1.124394] Asymmetric key parser 'x509' registered
[    1.129295] Block layer SCSI generic (bsg) driver version 0.4 loaded (major 251)
[    1.136777] io scheduler mq-deadline registered
[    1.141165] io scheduler kyber registered
[    2.203776] shpchp: Standard Hot Plug PCI Controller Driver version: 0.4
[    2.231415] fu740-pcie e00000000.pcie: host bridge /soc/pcie@e00000000 ranges:
[    2.237990] fu740-pcie e00000000.pcie:       IO 0x0060080000..0x006008ffff -> 0x0060080000
[    2.246214] fu740-pcie e00000000.pcie:      MEM 0x0060090000..0x0070ffffff -> 0x0060090000
[    2.254443] fu740-pcie e00000000.pcie:      MEM 0x2000000000..0x3fffffffff -> 0x2000000000
[    2.369157] fu740-pcie e00000000.pcie: invalid resource
[    2.373632] fu740-pcie e00000000.pcie: iATU unroll: enabled
[    2.379182] fu740-pcie e00000000.pcie: Detected iATU regions: 8 outbound, 8 inbound
[    2.486862] fu740-pcie e00000000.pcie: Link up
[    2.490696] fu740-pcie e00000000.pcie: PCI host bridge to bus 0000:00
[    2.496980] pci_bus 0000:00: root bus resource [bus 00-ff]
[    2.502441] pci_bus 0000:00: root bus resource [io  0x0000-0xffff] (bus address [0x60080000-0x6008ffff])
[    2.511905] pci_bus 0000:00: root bus resource [mem 0x60090000-0x70ffffff]
[    2.518766] pci_bus 0000:00: root bus resource [mem 0x2000000000-0x3fffffffff pref]
[    2.526454] pci 0000:00:00.0: [f15e:0000] type 01 class 0x060400
[    2.532417] pci 0000:00:00.0: reg 0x10: [mem 0x00000000-0x000fffff]
[    2.538662] pci 0000:00:00.0: reg 0x38: [mem 0x00000000-0x0000ffff pref]
[    2.545397] pci 0000:00:00.0: supports D1
[    2.549341] pci 0000:00:00.0: PME# supported from D0 D1 D3hot
[    2.556060] pci 0000:01:00.0: [1b21:2824] type 01 class 0x060400
[    2.561379] pci 0000:01:00.0: enabling Extended Tags
[    2.566372] pci 0000:01:00.0: PME# supported from D0 D3hot D3cold
[    2.584799] pci 0000:01:00.0: bridge configuration invalid ([bus 00-00]), reconfiguring
[    2.592216] pci 0000:02:00.0: [1b21:2824] type 01 class 0x060400
[    2.598113] pci 0000:02:00.0: enabling Extended Tags
[    2.603108] pci 0000:02:00.0: PME# supported from D0 D3hot D3cold
[    2.609429] pci 0000:02:02.0: [1b21:2824] type 01 class 0x060400
[    2.615136] pci 0000:02:02.0: enabling Extended Tags
[    2.620131] pci 0000:02:02.0: PME# supported from D0 D3hot D3cold
[    2.626407] pci 0000:02:03.0: [1b21:2824] type 01 class 0x060400
[    2.632160] pci 0000:02:03.0: enabling Extended Tags
[    2.637160] pci 0000:02:03.0: PME# supported from D0 D3hot D3cold
[    2.643443] pci 0000:02:04.0: [1b21:2824] type 01 class 0x060400
[    2.649184] pci 0000:02:04.0: enabling Extended Tags
[    2.654180] pci 0000:02:04.0: PME# supported from D0 D3hot D3cold
[    2.660537] pci 0000:02:08.0: [1b21:2824] type 01 class 0x060400
[    2.666208] pci 0000:02:08.0: enabling Extended Tags
[    2.671205] pci 0000:02:08.0: PME# supported from D0 D3hot D3cold
[    2.677934] pci 0000:02:00.0: bridge configuration invalid ([bus 00-00]), reconfiguring
[    2.685196] pci 0000:02:02.0: bridge configuration invalid ([bus 00-00]), reconfiguring
[    2.693183] pci 0000:02:03.0: bridge configuration invalid ([bus 00-00]), reconfiguring
[    2.701171] pci 0000:02:04.0: bridge configuration invalid ([bus 00-00]), reconfiguring
[    2.709170] pci 0000:02:08.0: bridge configuration invalid ([bus 00-00]), reconfiguring
[    2.717843] pci_bus 0000:03: busn_res: [bus 03-ff] end is updated to 03
[    2.723921] pci 0000:04:00.0: [1b21:1142] type 00 class 0x0c0330
[    2.729782] pci 0000:04:00.0: reg 0x10: [mem 0x00000000-0x00007fff 64bit]
[    2.736707] pci 0000:04:00.0: PME# supported from D3cold
[    2.752798] pci_bus 0000:04: busn_res: [bus 04-ff] end is updated to 04
[    2.758825] pci 0000:05:00.0: [8086:3165] type 00 class 0x028000
[    2.764704] pci 0000:05:00.0: reg 0x10: [mem 0x00000000-0x00001fff 64bit]
[    2.771696] pci 0000:05:00.0: PME# supported from D0 D3hot D3cold
[    2.788812] pci_bus 0000:05: busn_res: [bus 05-ff] end is updated to 05
[    2.795368] pci_bus 0000:06: busn_res: [bus 06-ff] end is updated to 06
[    2.801423] pci 0000:07:00.0: [1002:68f9] type 00 class 0x030000
[    2.807302] pci 0000:07:00.0: reg 0x10: [mem 0x00000000-0x0fffffff 64bit pref]
[    2.814494] pci 0000:07:00.0: reg 0x18: [mem 0x00000000-0x0001ffff 64bit]
[    2.821259] pci 0000:07:00.0: reg 0x20: initial BAR value 0x00000000 invalid
[    2.828282] pci 0000:07:00.0: reg 0x20: [io  size 0x0100]
[    2.833691] pci 0000:07:00.0: reg 0x30: [mem 0x00000000-0x0001ffff pref]
[    2.840370] pci 0000:07:00.0: enabling Extended Tags
[    2.845416] pci 0000:07:00.0: supports D1 D2
[    2.849660] pci 0000:07:00.0: 16.000 Gb/s available PCIe bandwidth, limited by 2.5 GT/s PCIe x8 link at 0000:02:08.0 (capable of 32.000 Gb/s with 2.5 GT/s PCIe x16 link)
[    2.864795] pci 0000:07:00.0: vgaarb: VGA device added: decodes=io+mem,owns=none,locks=none
[    2.873100] pci 0000:07:00.1: [1002:aa68] type 00 class 0x040300
[    2.879046] pci 0000:07:00.1: reg 0x10: [mem 0x00000000-0x00003fff 64bit]
[    2.885855] pci 0000:07:00.1: enabling Extended Tags
[    2.890842] pci 0000:07:00.1: supports D1 D2
[    2.904813] pci_bus 0000:07: busn_res: [bus 07-ff] end is updated to 07
[    2.910698] pci_bus 0000:02: busn_res: [bus 02-ff] end is updated to 07
[    2.917284] pci_bus 0000:01: busn_res: [bus 01-ff] end is updated to 07
[    2.923923] pci 0000:00:00.0: BAR 15: assigned [mem 0x2000000000-0x200fffffff 64bit pref]
[    2.932043] pci 0000:00:00.0: BAR 0: assigned [mem 0x60100000-0x601fffff]
[    2.938818] pci 0000:00:00.0: BAR 14: assigned [mem 0x60200000-0x604fffff]
[    2.945678] pci 0000:00:00.0: BAR 6: assigned [mem 0x60090000-0x6009ffff pref]
[    2.952886] pci 0000:00:00.0: BAR 13: assigned [io  0x0000-0x0fff]
[    2.959056] pci 0000:01:00.0: BAR 15: assigned [mem 0x2000000000-0x200fffffff 64bit pref]
[    2.967218] pci 0000:01:00.0: BAR 14: assigned [mem 0x60200000-0x604fffff]
[    2.974079] pci 0000:01:00.0: BAR 13: assigned [io  0x0000-0x0fff]
[    2.980252] pci 0000:02:08.0: BAR 15: assigned [mem 0x2000000000-0x200fffffff 64bit pref]
[    2.988412] pci 0000:02:02.0: BAR 14: assigned [mem 0x60200000-0x602fffff]
[    2.995273] pci 0000:02:03.0: BAR 14: assigned [mem 0x60300000-0x603fffff]
[    3.002135] pci 0000:02:08.0: BAR 14: assigned [mem 0x60400000-0x604fffff]
[    3.008996] pci 0000:02:08.0: BAR 13: assigned [io  0x0000-0x0fff]
[    3.015165] pci 0000:02:00.0: PCI bridge to [bus 03]
[    3.020134] pci 0000:04:00.0: BAR 0: assigned [mem 0x60200000-0x60207fff 64bit]
[    3.027429] pci 0000:02:02.0: PCI bridge to [bus 04]
[    3.032373] pci 0000:02:02.0:   bridge window [mem 0x60200000-0x602fffff]
[    3.039150] pci 0000:05:00.0: BAR 0: assigned [mem 0x60300000-0x60301fff 64bit]
[    3.046456] pci 0000:02:03.0: PCI bridge to [bus 05]
[    3.051388] pci 0000:02:03.0:   bridge window [mem 0x60300000-0x603fffff]
[    3.058167] pci 0000:02:04.0: PCI bridge to [bus 06]
[    3.063128] pci 0000:07:00.0: BAR 0: assigned [mem 0x2000000000-0x200fffffff 64bit pref]
[    3.071207] pci 0000:07:00.0: BAR 2: assigned [mem 0x60400000-0x6041ffff 64bit]
[    3.078500] pci 0000:07:00.0: BAR 6: assigned [mem 0x60420000-0x6043ffff pref]
[    3.085693] pci 0000:07:00.1: BAR 0: assigned [mem 0x60440000-0x60443fff 64bit]
[    3.093005] pci 0000:07:00.0: BAR 4: assigned [io  0x0000-0x00ff]
[    3.099075] pci 0000:02:08.0: PCI bridge to [bus 07]
[    3.104020] pci 0000:02:08.0:   bridge window [io  0x0000-0x0fff]
[    3.110103] pci 0000:02:08.0:   bridge window [mem 0x60400000-0x604fffff]
[    3.116876] pci 0000:02:08.0:   bridge window [mem 0x2000000000-0x200fffffff 64bit pref]
[    3.124957] pci 0000:01:00.0: PCI bridge to [bus 02-07]
[    3.130163] pci 0000:01:00.0:   bridge window [io  0x0000-0x0fff]
[    3.136247] pci 0000:01:00.0:   bridge window [mem 0x60200000-0x604fffff]
[    3.143020] pci 0000:01:00.0:   bridge window [mem 0x2000000000-0x200fffffff 64bit pref]
[    3.151101] pci 0000:00:00.0: PCI bridge to [bus 01-07]
[    3.156313] pci 0000:00:00.0:   bridge window [io  0x0000-0x0fff]
[    3.162388] pci 0000:00:00.0:   bridge window [mem 0x60200000-0x604fffff]
[    3.169162] pci 0000:00:00.0:   bridge window [mem 0x2000000000-0x200fffffff 64bit pref]
[    3.177876] pcieport 0000:00:00.0: AER: enabled with IRQ 46
[    3.182942] pcieport 0000:01:00.0: enabling device (0000 -> 0003)
[    3.189529] pcieport 0000:02:02.0: enabling device (0000 -> 0002)
[    3.195300] pcieport 0000:02:03.0: enabling device (0000 -> 0002)
[    3.201685] pcieport 0000:02:08.0: enabling device (0000 -> 0003)
[    3.207496] pci 0000:04:00.0: enabling device (0000 -> 0002)
[    3.212919] pci 0000:07:00.1: D0 power state depends on 0000:07:00.0
[    3.219279] switchtec: loaded.
[    3.222440] L2CACHE: DataError @ 0x00000003.AFF7EB30
[    3.227170] L2CACHE: No. of Banks in the cache: 4
[    3.231782] L2CACHE: No. of ways per bank: 16
[    3.236125] L2CACHE: Sets per bank: 512
[    3.239944] L2CACHE: Bytes per cache block: 64
[    3.244373] L2CACHE: Index of the largest way enabled: 15
[    3.290475] Serial: 8250/16550 driver, 4 ports, IRQ sharing disabled
[    3.297237] 10010000.serial: ttySIF0 at MMIO 0x10010000 (irq = 1, base_baud = 115200) is a SiFive UART v0
[    3.306100] printk: console [ttySIF0] enabled
[    3.306100] printk: console [ttySIF0] enabled
[    3.314748] printk: bootconsole [sifive0] disabled
[    3.314748] printk: bootconsole [sifive0] disabled
[    3.324584] 10011000.serial: ttySIF1 at MMIO 0x10011000 (irq = 2, base_baud = 115200) is a SiFive UART v0
[    3.349661] loop: module loaded
[    3.367279] ------------[ cut here ]------------
[    3.371135] WARNING: CPU: 0 PID: 1 at block/blk-mq.c:3075 blk_mq_release+0x48/0xba
[    3.378687] Modules linked in:
[    3.381730] CPU: 0 PID: 1 Comm: swapper/0 Not tainted 5.13.19 #1
[    3.387721] Hardware name: SiFive HiFive Unmatched A00 (DT)
[    3.393281] epc : blk_mq_release+0x48/0xba
[    3.397362]  ra : blk_release_queue+0xd0/0x154
[    3.401792] epc : ffffffff80620176 ra : ffffffff80612b74 sp : ffffffe080087c30
[    3.409000]  gp : ffffffff81472780 tp : ffffffe080088000 t0 : 0000000000000040
[    3.416210]  t1 : 0000000000000238 t2 : 0000000000000152 s0 : ffffffe080087c60
[    3.423419]  s1 : ffffffe0823d8080 a0 : ffffffe0823d8000 a1 : ffffffe081bfeda0
[    3.430628]  a2 : 0000000000000001 a3 : ffffffe08235b630 a4 : ffffffe08235b630
[    3.437837]  a5 : 0000000000000000 a6 : ffffffe08235ac00 a7 : fffffffffffffffa
[    3.445047]  s2 : ffffffe0823d8000 s3 : ffffffe0823d8000 s4 : 0000000000000000
[    3.452256]  s5 : ffffffff81479248 s6 : 0000000000000001 s7 : ffffffff80d4a5b8
[    3.459465]  s8 : ffffffff812320a0 s9 : 0000000000000008 s10: ffffffff80c8f97c
[    3.466674]  s11: 0000000000000000 t3 : fc00000000000000 t4 : 7f00000000000000
[    3.473883]  t5 : ffffffff814c3460 t6 : ffffffff814c3468
[    3.479181] status: 0000000200000120 badaddr: 0000000000000001 cause: 0000000000000003
[    3.487088] [<ffffffff80620176>] blk_mq_release+0x48/0xba
[    3.492472] [<ffffffff80612b74>] blk_release_queue+0xd0/0x154
[    3.498203] [<ffffffff806a9c1c>] kobject_put+0x96/0xee
[    3.503328] [<ffffffff8060ff30>] blk_put_queue+0x24/0x2c
[    3.508626] [<ffffffff8062500c>] disk_release+0x66/0x90
[    3.513838] [<ffffffff807c6692>] device_release+0x40/0x84
[    3.519223] [<ffffffff806a9c1c>] kobject_put+0x96/0xee
[    3.524348] [<ffffffff807c67f8>] put_device+0x22/0x2c
[    3.529385] [<ffffffff80624420>] put_disk+0x28/0x32
[    3.534250] [<ffffffff807ea026>] nbd_dev_add+0x21c/0x268
[    3.539548] [<ffffffff80cb3db0>] nbd_init+0x152/0x176
[    3.544586] [<ffffffff8000283e>] do_one_initcall+0x4c/0x1c2
[    3.550145] [<ffffffff80c90940>] kernel_init_freeable+0x272/0x2d6
[    3.556225] [<ffffffff80c8650c>] kernel_init+0x22/0x11c
[    3.561437] [<ffffffff80003bf2>] ret_from_exception+0x0/0xc
[    3.567003] ---[ end trace a2cf64b40dc847ac ]---
[    3.578129] Rounding down aligned max_sectors from 4294967295 to 4294967288
[    3.584598] db_root: cannot open: /etc/target
[    3.589371] sifive_spi 10040000.spi: mapped; irq=4, cs=1
[    3.594714] spi-nor spi0.0: is25wp256 (32768 Kbytes)
[    3.601214] sifive_spi 10050000.spi: mapped; irq=6, cs=1
[    3.607215] libphy: Fixed MDIO Bus: probed
[    3.611071] macb 10090000.ethernet: Registered clk switch 'sifive-gemgxl-mgmt'
[    3.618345] libphy: MACB_mii_bus: probed
[    3.622776] macb 10090000.ethernet eth0: Cadence GEM rev 0x10070109 at 0x10090000 irq 7 (70:b3:d5:92:f9:c6)
[    3.631890] e1000e: Intel(R) PRO/1000 Network Driver
[    3.636724] e1000e: Copyright(c) 1999 - 2015 Intel Corporation.
[    3.642930] ehci_hcd: USB 2.0 'Enhanced' Host Controller (EHCI) Driver
[    3.649148] ehci-pci: EHCI PCI platform driver
[    3.653611] ohci_hcd: USB 1.1 'Open' Host Controller (OHCI) Driver
[    3.659747] ohci-pci: OHCI PCI platform driver
[    3.664216] uhci_hcd: USB Universal Host Controller Interface driver
[    3.670766] xhci_hcd 0000:04:00.0: xHCI Host Controller
[    3.675865] xhci_hcd 0000:04:00.0: new USB bus registered, assigned bus number 1
[    3.823885] xhci_hcd 0000:04:00.0: hcc params 0x0200e080 hci version 0x100 quirks 0x0000000010800410
[    3.833112] usb usb1: New USB device found, idVendor=1d6b, idProduct=0002, bcdDevice= 5.13
[    3.840635] usb usb1: New USB device strings: Mfr=3, Product=2, SerialNumber=1
[    3.847834] usb usb1: Product: xHCI Host Controller
[    3.852698] usb usb1: Manufacturer: Linux 5.13.19 xhci-hcd
[    3.858169] usb usb1: SerialNumber: 0000:04:00.0
[    3.863157] hub 1-0:1.0: USB hub found
[    3.866550] hub 1-0:1.0: 2 ports detected
[    3.870820] xhci_hcd 0000:04:00.0: xHCI Host Controller
[    3.875834] xhci_hcd 0000:04:00.0: new USB bus registered, assigned bus number 2
[    3.883113] xhci_hcd 0000:04:00.0: Host supports USB 3.0 SuperSpeed
[    3.890218] usb usb2: We don't know the algorithms for LPM for this host, disabling LPM.
[    3.897771] usb usb2: New USB device found, idVendor=1d6b, idProduct=0003, bcdDevice= 5.13
[    3.905800] usb usb2: New USB device strings: Mfr=3, Product=2, SerialNumber=1
[    3.913005] usb usb2: Product: xHCI Host Controller
[    3.917869] usb usb2: Manufacturer: Linux 5.13.19 xhci-hcd
[    3.923341] usb usb2: SerialNumber: 0000:04:00.0
[    3.928273] hub 2-0:1.0: USB hub found
[    3.931701] hub 2-0:1.0: 2 ports detected
[    3.936071] usbcore: registered new interface driver usb-storage
[    3.941821] usbcore: registered new interface driver usbserial_generic
[    3.948209] usbserial: USB Serial support registered for generic
[    3.954301] mousedev: PS/2 mouse device common for all mice
[    3.959794] usbcore: registered new interface driver usbtouchscreen
[    3.966121] i2c /dev entries driver
[    3.971080] da9063 0-0058: Device detected (chip-ID: 0x61, var-ID: 0x73)
[    3.991028] da9063-onkey da9063-onkey: DMA mask not set
[    3.999021] input: da9063-onkey as /devices/platform/soc/10030000.i2c/i2c-0/0-0058/da9063-onkey/input/input0
[    4.008408] da9063-rtc da9063-rtc: DMA mask not set
[    4.015368] random: fast init done
[    4.028959] da9063-rtc da9063-rtc: registered as rtc0
[    4.034456] da9063-rtc da9063-rtc: setting system clock to 2000-01-02T18:26:11 UTC (946837571)
[    4.042609] poweroff-gpio gpio-poweroff: gpio_poweroff_probe: pm_power_off function already registered
[    4.051625] poweroff-gpio: probe of gpio-poweroff failed with error -16
[    4.096309] da9063-watchdog da9063-watchdog: DMA mask not set
[    4.102467] softdog: initialized. soft_noboot=0 soft_margin=60 sec soft_panic=0 (nowayout=0)
[    4.110160] softdog:              soft_reboot_cmd=<not set> soft_active_on_boot=0
[    4.117732] EDAC DEVICE0: Giving out device to module Sifive ECC Manager controller sifive_edac.0: DEV sifive_edac.0 (INTERRUPT)
[    4.154603] mmc_spi spi1.0: SD/MMC host mmc0, no DMA, no WP, no poweroff, cd polling
[    4.162175] ledtrig-cpu: registered to indicate activity on CPUs
[    4.167759] usbcore: registered new interface driver usbhid
[    4.173150] usbhid: USB HID core driver
[    4.177203] usbcore: registered new interface driver snd-usb-audio
[    4.183450] Initializing XFRM netlink socket
[    4.187927] NET: Registered protocol family 10
[    4.195392] Segment Routing with IPv6
[    4.198309] RPL Segment Routing with IPv6
[    4.200174] usb 1-1: new full-speed USB device number 2 using xhci_hcd
[    4.202956] NET: Registered protocol family 17
[    4.213280] bridge: filtering via arp/ip/ip6tables is no longer available by default. Update your scripts to load br_netfilter if you need this.
[    4.226507] 9pnet: Installing 9P2000 support
[    4.230672] NET: Registered protocol family 36
[    4.234885] Key type dns_resolver registered
[    4.239816] Loading compiled-in X.509 certificates
[    4.245011] Btrfs loaded, crc32c=crc32c-generic, zoned=yes
[    4.251196] ALSA device list:
[    4.252877] mmc0: host does not support reading read-only switch, assuming write-enable
[    4.253410]   No soundcards found.
[    4.261407] mmc0: new SDHC card on SPI
[    4.270010] mmcblk0: mmc0:0000 SD32G 29.7 GiB
[    4.306232]  mmcblk0: p1 p2 p3
[    4.516500] usb 1-1: New USB device found, idVendor=046d, idProduct=c534, bcdDevice=29.01
[    4.523930] usb 1-1: New USB device strings: Mfr=1, Product=2, SerialNumber=0
[    4.531045] usb 1-1: Product: USB Receiver
[    4.535127] usb 1-1: Manufacturer: Logitech
[    4.553465] usb 2-2: new SuperSpeed USB device number 2 using xhci_hcd
[    4.584048] usb 2-2: New USB device found, idVendor=174c, idProduct=3074, bcdDevice= 0.01
[    4.591485] usb 2-2: New USB device strings: Mfr=2, Product=3, SerialNumber=1
[    4.598586] usb 2-2: Product: AS2107
[    4.602145] usb 2-2: Manufacturer: ASMedia
[    4.606227] usb 2-2: SerialNumber: USB2.0 Hub
[    4.693731] input: Logitech USB Receiver as /devices/platform/soc/e00000000.pcie/pci0000:00/0000:00:00.0/0000:01:00.0/0000:02:02.0/0000:04:00.0/usb1/1-1/1-1:1.0/0003:046D:C534.0001/input/input1
[    4.759882] hub 2-2:1.0: USB hub found
[    4.763577] hub 2-2:1.0: 4 ports detected
[    4.768561] hid-generic 0003:046D:C534.0001: input: USB HID v1.11 Keyboard [Logitech USB Receiver] on usb-0000:04:00.0-1/input0
[    4.802155] input: Logitech USB Receiver Mouse as /devices/platform/soc/e00000000.pcie/pci0000:00/0000:00:00.0/0000:01:00.0/0000:02:02.0/0000:04:00.0/usb1/1-1/1-1:1.1/0003:046D:C534.0002/input/input2
[    4.819532] input: Logitech USB Receiver Consumer Control as /devices/platform/soc/e00000000.pcie/pci0000:00/0000:00:00.0/0000:01:00.0/0000:02:02.0/0000:04:00.0/usb1/1-1/1-1:1.1/0003:046D:C534.0002/input/input3
[    4.896424] input: Logitech USB Receiver System Control as /devices/platform/soc/e00000000.pcie/pci0000:00/0000:00:00.0/0000:01:00.0/0000:02:02.0/0000:04:00.0/usb1/1-1/1-1:1.1/0003:046D:C534.0002/input/input4
[    4.914466] hid-generic 0003:046D:C534.0002: input,hiddev96: USB HID v1.11 Mouse [Logitech USB Receiver] on usb-0000:04:00.0-1/input1
[    5.120286] usb 1-2: new high-speed USB device number 3 using xhci_hcd
[    5.366161] usb 1-2: New USB device found, idVendor=174c, idProduct=2074, bcdDevice= 0.01
[    5.373590] usb 1-2: New USB device strings: Mfr=2, Product=3, SerialNumber=1
[    5.380707] usb 1-2: Product: AS2107
[    5.384265] usb 1-2: Manufacturer: ASMedia
[    5.388346] usb 1-2: SerialNumber: USB2.0 Hub
[    5.461626] hub 1-2:1.0: USB hub found
[    5.464822] hub 1-2:1.0: 4 ports detected
[    5.868177] usb 1-2.4: new full-speed USB device number 4 using xhci_hcd
[    6.153062] usb 1-2.4: New USB device found, idVendor=8087, idProduct=0a2a, bcdDevice= 0.01
[    6.160665] usb 1-2.4: New USB device strings: Mfr=0, Product=0, SerialNumber=0
[    6.318728] EXT4-fs (mmcblk0p3): recovery complete
[    6.325847] EXT4-fs (mmcblk0p3): mounted filesystem with ordered data mode. Opts: (null). Quota mode: none.
[    6.334906] VFS: Mounted root (ext4 filesystem) on device 179:3.
[    6.352801] devtmpfs: mounted
[    6.365253] Freeing unused kernel memory: 820K
[    6.368966] Kernel memory protection not selected by kernel config.
[    6.375218] Run /sbin/init as init process
[   13.963944] systemd[1]: systemd v249-26.oe2203 running in system mode (+PAM +AUDIT +SELINUX -APPARMOR +IMA -SMACK +SECCOMP +GCRYPT +GNUTLS -OPENSSL +ACL +BLKID -CURL -ELFUTILS -FIDO2 +IDN2 -IDN -IPTC +KMOD -LIBCRYPTSETUP +LIBFDISK +PCRE2 -PWQUALITY +P11KIT -QRENCODE +BZIP2 +LZ4 +XZ +ZLIB -ZSTD +XKBCOMMON +UTMP +SYSVINIT default-hierarchy=legacy)
[   13.994149] systemd[1]: Detected architecture riscv64.

Welcome to openEuler 22.03 LTS!

[   14.179892] systemd[1]: Hostname set to <openEuler-riscv64>.
[   14.851228] systemd-rc-local-generator[132]: /etc/rc.d/rc.local is not marked executable, skipping.
[   18.877980] random: lvmconfig: uninitialized urandom read (4 bytes read)
[   19.157800] systemd[1]: Configuration file /usr/lib/systemd/system/upower.service is marked executable. Please remove executable permission bits. Proceeding anyway.
[   19.176585] systemd[1]: Configuration file /usr/lib/systemd/system/dbus.socket is marked executable. Please remove executable permission bits. Proceeding anyway.
[   19.193576] systemd[1]: /usr/lib/systemd/system/dbus.socket:5: ListenStream= references a path below legacy directory /var/run/, updating /var/run/dbus/system_bus_socket  /run/dbus/system_bus_socket; please update the unit file accordingly.
[   19.226691] systemd[1]: Configuration file /usr/lib/systemd/system/systemd-udevd-kernel.socket is marked executable. Please remove executable permission bits. Proceeding anyway.
[   19.246896] systemd[1]: Configuration file /usr/lib/systemd/system/systemd-udevd.service is marked executable. Please remove executable permission bits. Proceeding anyway.
[   19.326447] systemd[1]: Configuration file /usr/lib/systemd/system/systemd-remount-fs.service is marked executable. Please remove executable permission bits. Proceeding anyway.
[   19.372068] systemd[1]: Configuration file /usr/lib/systemd/system/systemd-hwdb-update.service is marked executable. Please remove executable permission bits. Proceeding anyway.
[   19.402084] systemd[1]: Configuration file /usr/lib/systemd/system/systemd-udevd-control.socket is marked executable. Please remove executable permission bits. Proceeding anyway.
[   19.458119] systemd[1]: Configuration file /usr/lib/systemd/system/dm-event.socket is marked executable. Please remove executable permission bits. Proceeding anyway.
[   19.476749] systemd[1]: Configuration file /usr/lib/systemd/system/dm-event.service is marked executable. Please remove executable permission bits. Proceeding anyway.
[   19.495344] systemd[1]: Configuration file /usr/lib/systemd/system/dbus.service is marked executable. Please remove executable permission bits. Proceeding anyway.
[   19.552666] systemd[1]: Configuration file /usr/lib/systemd/system/dnf-makecache.timer is marked executable. Please remove executable permission bits. Proceeding anyway.
[   19.571590] systemd[1]: Configuration file /usr/lib/systemd/system/dnf-makecache.service is marked executable. Please remove executable permission bits. Proceeding anyway.
[   19.598320] systemd[1]: Configuration file /usr/lib/systemd/system/NetworkManager-wait-online.service is marked executable. Please remove executable permission bits. Proceeding anyway.
[   19.619515] systemd[1]: Configuration file /usr/lib/systemd/system/NetworkManager.service is marked executable. Please remove executable permission bits. Proceeding anyway.
[   19.666886] systemd[1]: Configuration file /usr/lib/systemd/system/systemd-udev-trigger.service is marked executable. Please remove executable permission bits. Proceeding anyway.
[   19.690417] systemd[1]: Configuration file /usr/lib/systemd/system/systemd-udev-trigger.service.d/systemd-udev-trigger-no-reload.conf is marked executable. Please remove executable permission bits. Proceeding anyway.
[   19.712213] systemd[1]: Configuration file /usr/lib/systemd/system/systemd-tmpfiles-setup-dev.service is marked executable. Please remove executable permission bits. Proceeding anyway.
[   19.733799] systemd[1]: Configuration file /usr/lib/systemd/system/systemd-timesyncd.service is marked executable. Please remove executable permission bits. Proceeding anyway.
[   19.761142] systemd[1]: Configuration file /usr/lib/systemd/system/systemd-random-seed.service is marked executable. Please remove executable permission bits. Proceeding anyway.
[   19.786467] systemd[1]: Configuration file /usr/lib/systemd/system/systemd-modules-load.service is marked executable. Please remove executable permission bits. Proceeding anyway.
[   19.845480] systemd[1]: Configuration file /usr/lib/systemd/system/systemd-vconsole-setup.service is marked executable. Please remove executable permission bits. Proceeding anyway.
[   19.903574] systemd[1]: Configuration file /usr/lib/systemd/system/initrd-udevadm-cleanup-db.service is marked executable. Please remove executable permission bits. Proceeding anyway.
[   19.925109] systemd[1]: Configuration file /usr/lib/systemd/system/systemd-udev-settle.service is marked executable. Please remove executable permission bits. Proceeding anyway.
[   19.983511] systemd[1]: Configuration file /usr/lib/systemd/system/lvm2-monitor.service is marked executable. Please remove executable permission bits. Proceeding anyway.
[   20.006773] systemd[1]: Configuration file /usr/lib/systemd/system/kmod-static-nodes.service is marked executable. Please remove executable permission bits. Proceeding anyway.
[   20.125463] systemd[1]: Configuration file /usr/lib/systemd/system/sshd.service is marked executable. Please remove executable permission bits. Proceeding anyway.
[   20.143381] systemd[1]: Configuration file /usr/lib/systemd/system/sshd-keygen.target is marked executable. Please remove executable permission bits. Proceeding anyway.
[   20.162070] systemd[1]: Configuration file /usr/lib/systemd/system/sshd-keygen@.service is marked executable. Please remove executable permission bits. Proceeding anyway.
[   20.183476] systemd[1]: Configuration file /usr/lib/systemd/system/sshd-keygen@.service is marked executable. Please remove executable permission bits. Proceeding anyway.
[   20.200577] systemd[1]: Configuration file /usr/lib/systemd/system/sshd-keygen@.service is marked executable. Please remove executable permission bits. Proceeding anyway.
[   20.289455] systemd[1]: Configuration file /usr/lib/systemd/system/rtkit-daemon.service is marked executable. Please remove executable permission bits. Proceeding anyway.
[   20.307446] systemd[1]: /usr/lib/systemd/system/rtkit-daemon.service:32: Unknown key name 'ControlGroup' in section 'Service', ignoring.
[   20.320311] systemd[1]: Configuration file /usr/lib/systemd/system/accounts-daemon.service is marked executable. Please remove executable permission bits. Proceeding anyway.
[   20.343867] systemd[1]: Configuration file /usr/lib/systemd/system/lightdm.service is marked executable. Please remove executable permission bits. Proceeding anyway.
[   20.367810] systemd[1]: Queued start job for default target Graphical Interface.
[   20.375961] random: systemd: uninitialized urandom read (16 bytes read)
[   20.423717] systemd[1]: Created slice Slice /system/getty.
[  OK  ] Created slice Slice /system/getty.
[   20.434878] random: systemd: uninitialized urandom read (16 bytes read)
[   20.442942] systemd[1]: Created slice Slice /system/modprobe.
[  OK  ] Created slice Slice /system/modprobe.
[   20.454286] random: systemd: uninitialized urandom read (16 bytes read)
[   20.462491] systemd[1]: Created slice Slice /system/serial-getty.
[  OK  ] Created slice Slice /system/serial-getty.
[   20.476892] systemd[1]: Created slice Slice /system/sshd-keygen.
[  OK  ] Created slice Slice /system/sshd-keygen.
[   20.490548] systemd[1]: Created slice User and Session Slice.
[  OK  ] Created slice User and Session Slice.
[   20.502160] systemd[1]: Started Dispatch Password Requests to Console Directory Watch.
[  OK  ] Started Dispatch Password ts to Console Directory Watch.
[   20.519077] systemd[1]: Started Forward Password Requests to Wall Directory Watch.
[  OK  ] Started Forward Password Ruests to Wall Directory Watch.
[   20.535016] systemd[1]: Set up automount Arbitrary Executable File Formats File System Automount Point.
[  OK  ] Set up automount Arbitrarys File System Automount Point.
[   20.552257] systemd[1]: Reached target User and Group Name Lookups.
[  OK  ] Reached target User and Group Name Lookups.
[   20.564907] systemd[1]: Reached target Path Units.
[  OK  ] Reached target Path Units.
[   20.575100] systemd[1]: Reached target Remote File Systems.
[  OK  ] Reached target Remote File Systems.
[   20.586616] systemd[1]: Reached target Slice Units.
[  OK  ] Reached target Slice Units.
[   20.596986] systemd[1]: Reached target Swaps.
[  OK  ] Reached target Swaps.
[   20.606292] systemd[1]: Listening on Device-mapper event daemon FIFOs.
[  OK  ] Listening on Device-mapper event daemon FIFOs.
[   20.630649] systemd[1]: Listening on Process Core Dump Socket.
[  OK  ] Listening on Process Core Dump Socket.
[   20.643031] systemd[1]: Listening on initctl Compatibility Named Pipe.
[  OK  ] Listening on initctl Compatibility Named Pipe.
[   20.657003] systemd[1]: Listening on Journal Socket (/dev/log).
[  OK  ] Listening on Journal Socket (/dev/log).
[   20.669676] systemd[1]: Listening on Journal Socket.
[  OK  ] Listening on Journal Socket.
[   20.680170] systemd[1]: Listening on udev Control Socket.
[  OK  ] Listening on udev Control Socket.
[   20.691534] systemd[1]: Listening on udev Kernel Socket.
[  OK  ] Listening on udev Kernel Socket.
[   20.703011] systemd[1]: Condition check resulted in Huge Pages File System being skipped.
[   20.714874] systemd[1]: Mounting POSIX Message Queue File System...
         Mounting POSIX Message Queue File System...
[   20.731566] systemd[1]: Mounting Kernel Debug File System...
         Mounting Kernel Debug File System...
[   20.746121] systemd[1]: Mounting Kernel Trace File System...
         Mounting Kernel Trace File System...
[   20.767326] systemd[1]: Mounting Temporary Directory /tmp...
         Mounting Temporary Directory /tmp...
[   20.778524] systemd[1]: Condition check resulted in Create List of Static Device Nodes being skipped.
[   20.793633] systemd[1]: Starting Monitoring of LVM2 mirrors, snapshots etc. using dmeventd or progress polling...
         Starting Monitoring of LVMmeventd or progress polling...
[   20.815792] systemd[1]: Starting Load Kernel Module configfs...
         Starting Load Kernel Module configfs...
[   20.832325] systemd[1]: Starting Load Kernel Module drm...
         Starting Load Kernel Module drm...
[   20.848210] systemd[1]: Starting Load Kernel Module fuse...
         Starting Load Kernel Module fuse...
[   21.123739] systemd[1]: Condition check resulted in Set Up Additional Binary Formats being skipped.
[   21.133279] systemd[1]: systemd-journald.service: unit configures an IP firewall, but the local system does not support BPF/cgroup firewalling.
[   21.145451] systemd[1]: (This warning is only shown for the first unit using IP firewalling.)
[   21.160316] systemd[1]: Starting Journal Service...
         Starting Journal Service...
[   21.302360] systemd[1]: Condition check resulted in Load Kernel Modules being skipped.
[   21.314831] systemd[1]: Starting Remount Root and Kernel File Systems...
         Starting Remount Root and Kernel File Systems...
[   21.332335] systemd[1]: Starting Apply Kernel Variables...
         Starting Apply Kernel Variables...
[   21.347817] systemd[1]: Starting Coldplug All udev Devices...
         Starting Coldplug All udev Devices...
[   21.370091] systemd[1]: Mounted POSIX Message Queue File System.
[  OK  ] Mounted POSIX Message Queue File System.
[   21.383104] systemd[1]: Mounted Kernel Debug File System.
[  OK  ] Mounted Kernel Debug File System.
[   21.401697] systemd[1]: Mounted Kernel Trace File System.
[  OK  ] Mounted Kernel Trace File System.
[   21.414556] systemd[1]: Mounted Temporary Directory /tmp.
[  OK  ] Mounted Temporary Directory /tmp.
[   21.427797] systemd[1]: Finished Monitoring of LVM2 mirrors, snapshots etc. using dmeventd or progress polling.
[  OK  ] Finished Monitoring of LVM dmeventd or progress polling.
[   21.453921] systemd[1]: modprobe@configfs.service: Deactivated successfully.
[   21.462008] systemd[1]: Finished Load Kernel Module configfs.
[  OK  ] Finished Load Kernel Module configfs.
[   21.474869] systemd[1]: modprobe@drm.service: Deactivated successfully.
[   21.482328] systemd[1]: Finished Load Kernel Module drm.
[  OK  ] Finished Load Kernel Module drm.
[   21.494574] systemd[1]: modprobe@fuse.service: Deactivated successfully.
[   21.521097] systemd[1]: Finished Load Kernel Module fuse.
[  OK  ] Finished Load Kernel Module fuse.
[   21.536600] systemd[1]: Finished Remount Root and Kernel File Systems.
[  OK  ] Finished Remount Root and Kernel File Systems.
[   21.554926] systemd[1]: Finished Apply Kernel Variables.
[  OK  ] Finished Apply Kernel Variables.
[   21.567460] systemd[1]: Condition check resulted in FUSE Control File System being skipped.
[   21.579830] systemd[1]: Mounting Kernel Configuration File System...
         Mounting Kernel Configuration File System...
[   21.732798] systemd[1]: Condition check resulted in Rebuild Hardware Database being skipped.
[   21.746208] systemd[1]: Starting Load/Save Random Seed...
         Starting Load/Save Random Seed...
[   21.756928] systemd[1]: Condition check resulted in Create System Users being skipped.
[   21.769448] systemd[1]: Starting Create Static Device Nodes in /dev...
         Starting Create Static Device Nodes in /dev...
[   21.786915] systemd[1]: Started Journal Service.
[  OK  ] Started Journal Service.
[  OK  ] Mounted Kernel Configuration File System.
         Starting Flush Journal to Persistent Storage...
[   22.083477] systemd-journald[153]: Received client request to flush runtime journal.
[  OK  ] Finished Flush Journal to Persistent Storage.
[  OK  ] Finished Create Static Device Nodes in /dev.
[  OK  ] Reached target Preparation for Local File Systems.
[  OK  ] Reached target Local File Systems.
         Starting Create Volatile Files and Directories...
         Starting Rule-based Managefor Device Events and Files...
[  OK  ] Finished Coldplug All udev Devices.
[  OK  ] Finished Create Volatile Files and Directories.
         Starting Network Time Synchronization...
         Starting Record System Boot/Shutdown in UTMP...
[  OK  ] Finished Record System Boot/Shutdown in UTMP.
[  OK  ] Started Rule-based Manager for Device Events and Files.
[  OK  ] Found device /dev/ttySIF0.
[  OK  ] Found device /dev/hvc0.
[  OK  ] Started Network Time Synchronization.
[  OK  ] Reached target System Initialization.
[  OK  ] Started dnf makecache --timer.
[  OK  ] Started Daily Cleanup of Temporary Directories.
[  OK  ] Reached target System Time Set.
[  OK  ] Reached target Timer Units.
[  OK  ] Listening on D-Bus System Message Bus Socket.
[  OK  ] Reached target Socket Units.
[  OK  ] Reached target Basic System.
         Starting Accounts Service...
         Starting D-Bus System Message Bus...
         Starting Update RTC With System Clock...
[  OK  ] Started resize rootfs.
         Starting RealtimeKit Scheduling Policy Service...
[  OK  ] Reached target sshd-keygen.target.
         Starting User Login Management...
         Starting Daemon for power management...
[  OK  ] Finished Update RTC With System Clock.
[   27.792217] random: crng init done
[   27.794865] random: 6 urandom warning(s) missed due to ratelimiting
[  OK  ] Finished Load/Save Random Seed.
[  OK  ] Started D-Bus System Message Bus.
         Starting Network Manager...
[  OK  ] Started User Login Management.
[  OK  ] Started RealtimeKit Scheduling Policy Service.
[  OK  ] Started Daemon for power management.
         Starting Authorization Manager...
[  OK  ] Started Network Manager.
[  OK  ] Reached target Network.
         Starting Network Manager Wait Online...
         Starting OpenSSH server daemon...
         Starting Permit User Sessions...
[  OK  ] Finished Permit User Sessions.
[  OK  ] Started Command Scheduler.
         Starting Light Display Manager...
[  OK  ] Started Serial Getty on hvc0.
[  OK  ] Started Serial Getty on ttySIF0.
[  OK  ] Reached target Login Prompts.
         Starting Hostname Service...
[  OK  ] Started Hostname Service.
[  OK  ] Started Authorization Manager.
[  OK  ] Started Accounts Service.
[  OK  ] Started Light Display Manager.
[  OK  ] Started OpenSSH server daemon.
[  OK  ] Reached target Multi-User System.
[  OK  ] Reached target Graphical Interface.
         Starting Record Runlevel Change in UTMP...
[  OK  ] Finished Record Runlevel Change in UTMP.

openEuler 22.03 LTS
Kernel 5.13.19 on an riscv64

openEuler-riscv64 login:
openEuler 22.03 LTS
Kernel 5.13.19 on an riscv64

openEuler-riscv64 login: 
```
