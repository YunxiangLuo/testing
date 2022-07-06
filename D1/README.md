# openEuler RISC-V 镜像 D1 开发板安装测试 

预计测试结果：刷写成功，启动成功。

实际测试结果：刷写成功，但启动失败。

## 1 准备工作

### 1.1 准备硬件

1）D1开发板：由D1获取得到开发板。

2）64G micro-sd卡及读卡器：SanDisk TF/MicroSD卡，容量64GB，速度U1，带读卡器。

3）Usb转uart串口通信模块：丢石头 PL2303，3.3/5V电平输出，type A接口，10PIN散头杜邦线。

4）电源适配器及type-c线。

5）连接D1开发板的3-Pin DEBUG端和Usb转uart串口通信模块。

照片：

![figure_3](./images/figure_3.jpg)

### 1.2 准备系统镜像

D1的系统镜像下载连接地址如下： https://mirror.iscas.ac.cn/openeuler-sig-riscv/openEuler-RISC-V/testing/20220622/v0.2/D1/

考虑到要安装验证Firefox浏览器，我们可以下载openeuler-d1-xfce.img.tar.zst，连接如下： https://mirror.iscas.ac.cn/openeuler-sig-riscv/openEuler-RISC-V/testing/20220622/v0.2/D1/openeuler-d1-xfce.img.tar.zst

其他文件均无需下载。

```bash
wget https://mirror.iscas.ac.cn/openeuler-sig-riscv/openEuler-RISC-V/testing/20220622/v0.2/D1/openeuler-d1-xfce.img.tar.zst
```

### 1.3 刷写镜像

以下步骤适用于Ubuntu20.04，如适用Windows操作系统，解压请下载[zstd](./zstd-v1.4.4-win32.zip)`zstd.exe -d ./openeuler-d1-xfce.img.tar.zst`，刷写请下载[win32diskimager](./win32diskimager-1.0.0-install.exe)

1. 解压镜像文件

```bash
sudo apt install zstd -y
tar -I zstdmt -xvf ./openeuler-d1-xfce.img.tar.zst
```

2. 镜像刷写

将64G micro-sd卡装入读卡器后，插入笔记本电脑。笔记本电脑通常带一个硬盘，所以sd卡对应设备是/dev/sdb

```bash
sudo dd if=./openeuler-d1-xfce.img of=/dev/sdb bs=1M iflag=fullblock oflag=direct conv=fsync status=progress
```

### 1.4 安装串口调试软件

1）将Usb转uart串口通信模块连接到电脑usb口。

2）检查设备管理器中的COM端口，例如COM4。

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

### 1.5 启动D1

将64G micro-sd卡装入D1 sd卡槽，连接tpye-c电源启动，启动报错如下，回车后进入Tina Linux

```
[351]HELLO! BOOT0 is starting!
[354]BOOT0 commit : 2337244-dirty

OpenSBI v0.6
   ____                    _____ ____ _____
  / __ \                  / ____|  _ \_   _|
 | |  | |_ __   ___ _ __ | (___ | |_) || |
 | |  | | '_ \ / _ \ '_ \ \___ \|  _ < | |
 | |__| | |_) |  __/ | | |____) | |_) || |_
  \____/| .__/ \___|_| |_|_____/|____/_____|
        | |
        |_|

Platform Name          : T-HEAD Xuantie Platform
Platform HART Features : RV64ACDFIMSUVX
Platform Max HARTs     : 1
Current Hart           : 0
Firmware Base          : 0x40000400
Firmware Size          : 75 KB
Runtime SBI Version    : 0.2

MIDELEG : 0x0000000000000222
MEDELEG : 0x000000000000b1ff
PMP0    : 0x0000000040000000-0x000000004001ffff (A)
PMP1    : 0x0000000040000000-0x000000007fffffff (A,R,W,X)
PMP2    : 0x0000000000000000-0x0000000007ffffff (A,R,W)
PMP3    : 0x0000000009000000-0x000000000901ffff (?

U-Boot 2018.05-00107-gc22c3d075c (Apr 24 2021 - 07:52:58 +0000) Allwinner Technology

[00.596]DRAM:  1 GiB
[00.598]Relocation Offset is: 3deeb000
[00.603]secure enable bit: 0
[00.606]CPU=1008 MHz,PLL6=600 Mhz,AHB=200 Mhz, APB1=100Mhz  MBus=300Mhz
initr_ledc
unable to find ledc node in device tree.
[00.617]flash init start
[00.619]workmode = 0,storage type = 0
[00.625]sunxi-spinand-phy: not detect any munufacture from id table
[00.631]sunxi-spinand-phy: get spi-nand Model from fdt fail
[00.637]sunxi-spinand-phy: get phy info from fdt fail

device nand0 <nand>, # parts = 4
 #: name                size            offset          mask_flags
 0: boot0               0x00100000      0x00000000      1
 1: uboot               0x00300000      0x00100000      1
 2: secure_storage      0x00100000      0x00400000      1
 3: sys                 0x0fb00000      0x00500000      0

active partition: nand0,0 - (boot0) 0x00100000 @ 0x00000000

defaults:
mtdids  : nand0=nand
mtdparts: mtdparts=nand:1024k@0(boot0)ro,3072k@1048576(uboot)ro,1024k@4194304(secure_storage)ro,-(sys)
[00.975]ubi0: attaching mtd4
[01.371]ubi0: scanning is finished
[01.381]ubi0: attached mtd4 (name "sys", size 251 MiB)
[01.386]ubi0: PEB size: 262144 bytes (256 KiB), LEB size: 258048 bytes
[01.392]ubi0: min./max. I/O unit sizes: 4096/4096, sub-page size 2048
[01.398]ubi0: VID header offset: 2048 (aligned 2048), data offset: 4096
[01.405]ubi0: good PEBs: 1004, bad PEBs: 0, corrupted PEBs: 0
[01.410]ubi0: user volume: 9, internal volumes: 1, max. volumes count: 128
[01.417]ubi0: max/mean erase counter: 2/1, WL threshold: 4096, image sequence number: 0
[01.424]ubi0: available PEBs: 0, total reserved PEBs: 1004, PEBs reserved for bad PEB handling: 40
[01.433]sunxi flash init ok
[01.435]line:714 init_clocks
__clk_init: clk pll_periph0x2 already initialized
register fix_factor clk error
[01.446]drv_disp_init
partno erro : can't find partition bootloader
** Unable to read file lcd_compatible_index.txt **
[01.683]do_fat_fsload for lcd config failed
request pwm success, pwm2:pwm2:0x2000c00.
[01.697]drv_disp_init finish
[01.700]boot_gui_init:start
[01.703]set disp.dev2_output_type fail. using defval=0
[01.894]boot_gui_init:finish
[02.307]LCD open finish
partno erro : can't find partition bootloader
54 bytes read in 1 ms (52.7 KiB/s)
[02.469]bmp_name=bootlogo.bmp size 38454
38454 bytes read in 4 ms (9.2 MiB/s)
[02.685]Loading Environment from SUNXI_FLASH... OK
[02.719]Item0 (Map) magic is bad
[02.722]usb burn from boot
delay time 0
weak:otg_phy_config
[02.733]usb prepare ok
[03.536]overtime
[03.540]do_burn_from_boot usb : no usb exist
[03.564]update bootcmd
[03.586]change working_fdt 0x7eaaad70 to 0x7ea8ad70
partno erro : can't find partition bootloader
** Unable to read file lcd_compatible_index.txt **
[03.637]do_fat_fsload for lcd config failed
partno erro : can't find partition bootloader
[03.665]please enable FAT_WRITE for lcd compatible first
partno erro : can't find partition bootloader
** Unable to read file lcd_compatible_index.txt **
[03.699]do_fat_fsload for lcd config failed
[03.703]libfdt fdt_path_offset() for lcd
[03.707]update dts
Hit any key to stop autoboot:  0
dsp0:gpio init config fail
DSP0 start ok, img length 252960, booting from 0x400660
Android's image name: d1-nezha
No reserved memory region found in source FDT
[04.663]
Starting kernel ...

[    0.000000] OF: fdt: Ignoring memory range 0x40000000 - 0x40200000
[    0.000000] Linux version 5.4.61 (wuhuabin@AwExdroid86) (riscv64-unknown-linux-gnu-gcc (C-SKY RISCV Tools V1.8.4 B20200702) 8.1.0, GNU ld (GNU Binutils) 2.32) #49 PREEMPT Wed Apr 28 09:23:43 UTC 2021
[    0.000000] cma: Reserved 8 MiB at 0x000000007f800000
[    0.000000] Zone ranges:
[    0.000000]   DMA32    [mem 0x0000000040200000-0x000000007fffffff]
[    0.000000]   Normal   empty
[    0.000000] Movable zone start for each node
[    0.000000] Early memory node ranges
[    0.000000]   node   0: [mem 0x0000000040200000-0x000000007fffffff]
[    0.000000] Initmem setup node 0 [mem 0x0000000040200000-0x000000007fffffff]
[    0.000000] On node 0 totalpages: 261632
[    0.000000]   DMA32 zone: 3577 pages used for memmap
[    0.000000]   DMA32 zone: 0 pages reserved
[    0.000000]   DMA32 zone: 261632 pages, LIFO batch:63
[    0.000000] elf_hwcap is 0x20112d
[    0.000000] pcpu-alloc: s0 r0 d32768 u32768 alloc=1*32768
[    0.000000] pcpu-alloc: [0] 0
[    0.000000] Built 1 zonelists, mobility grouping on.  Total pages: 258055
[    0.000000] Kernel command line: ubi.mtd=sys ubi.block=0,rootfs earlyprintk=sunxi-uart,0x02500000 clk_ignore_unused initcall_debug=0 console=ttyS0,115200 loglevel=8 root=/dev/ubiblock0_5 rootfstype=squashfs init=/sbin/init partitions=mbr@ubi0_0:boot-resource@ubi0_1:env@ubi0_2:env-redund@ubi0_3:boot@ubi0_4:rootfs@ubi0_5:dsp0@ubi0_6:recovery@ubi0_7:UDISK@ubi0_8: cma=8M snum= mac_addr= wifi_mac= bt_mac= specialstr= gpt=1 androidboot.hardware=sun20iw1p1 boot_type=5 androidboot.boot_type=5 gpt=1 uboot_message=2018.05-00107-gc22c3d075c(04/24/20
[    0.000000] Dentry cache hash table entries: 131072 (order: 8, 1048576 bytes, linear)
[    0.000000] Inode-cache hash table entries: 65536 (order: 7, 524288 bytes, linear)
[    0.000000] Sorting __ex_table...
[    0.000000] mem auto-init: stack:off, heap alloc:off, heap free:off
[    0.000000] Memory: 1008024K/1046528K available (5944K kernel code, 655K rwdata, 2062K rodata, 208K init, 251K bss, 30312K reserved, 8192K cma-reserved)
[    0.000000] SLUB: HWalign=64, Order=0-3, MinObjects=0, CPUs=1, Nodes=1
[    0.000000] rcu: Preemptible hierarchical RCU implementation.
[    0.000000]  Tasks RCU enabled.
[    0.000000] rcu: RCU calculated value of scheduler-enlistment delay is 10 jiffies.
[    0.000000] NR_IRQS: 0, nr_irqs: 0, preallocated irqs: 0
[    0.000000] plic: mapped 200 interrupts with 1 handlers for 2 contexts.
[    0.000000] riscv_timer_init_dt: Registering clocksource cpuid [0] hartid [0]
[    0.000000] clocksource: riscv_clocksource: mask: 0xffffffffffffffff max_cycles: 0x588fe9dc0, max_idle_ns: 440795202592 ns
[    0.000005] sched_clock: 64 bits at 24MHz, resolution 41ns, wraps every 4398046511097ns
[    0.000022] riscv_timer_clockevent depends on broadcast, but no broadcast function available
[    0.000333] clocksource: timer: mask: 0xffffffff max_cycles: 0xffffffff, max_idle_ns: 79635851949 ns
[    0.000936] Console: colour dummy device 80x25
[    0.000977] Calibrating delay loop (skipped), value calculated using timer frequency.. 48.00 BogoMIPS (lpj=240000)
[    0.000993] pid_max: default: 32768 minimum: 301
[    0.001192] Mount-cache hash table entries: 2048 (order: 2, 16384 bytes, linear)
[    0.001221] Mountpoint-cache hash table entries: 2048 (order: 2, 16384 bytes, linear)
[    0.002951] ASID allocator initialised with 65536 entries
[    0.003114] rcu: Hierarchical SRCU implementation.
[    0.003812] devtmpfs: initialized
[    0.015693] random: get_random_u32 called from bucket_table_alloc.isra.31+0x4e/0x15e with crng_init=0
[    0.016566] clocksource: jiffies: mask: 0xffffffff max_cycles: 0xffffffff, max_idle_ns: 19112604462750000 ns
[    0.016597] futex hash table entries: 256 (order: 0, 6144 bytes, linear)
[    0.017033] pinctrl core: initialized pinctrl subsystem
[    0.018361] NET: Registered protocol family 16
[    0.020287] DMA: preallocated 256 KiB pool for atomic allocations
[    0.020910] cpuidle: using governor menu
[    0.066018] rtc_ccu: sunxi ccu init OK
[    0.072533] clock: sunxi ccu init OK
[    0.073467] clock: sunxi ccu init OK
[    0.112303] iommu: Default domain type: Translated
[    0.112476] sunxi iommu: irq = 4
[    0.113641] SCSI subsystem initialized
[    0.113979] usbcore: registered new interface driver usbfs
[    0.114081] usbcore: registered new interface driver hub
[    0.114185] usbcore: registered new device driver usb
[    0.114363] mc: Linux media interface: v0.10
[    0.114424] videodev: Linux video capture interface: v2.00
[    0.115380] Advanced Linux Sound Architecture Driver Initialized.
[    0.115973] Bluetooth: Core ver 2.22
[    0.116053] NET: Registered protocol family 31
[    0.116064] Bluetooth: HCI device and connection manager initialized
[    0.116083] Bluetooth: HCI socket layer initialized
[    0.116096] Bluetooth: L2CAP socket layer initialized
[    0.116130] Bluetooth: SCO socket layer initialized
[    0.116408] pwm module init!
[    0.117927] g2d 5410000.g2d: Adding to iommu group 0
[    0.118410] G2D: rcq version initialized.major:250
[    0.118957] input: sunxi-keyboard as /devices/virtual/input/input0
[    0.120553] clocksource: Switched to clocksource riscv_clocksource
[    0.132256] sun8iw20-pinctrl 2000000.pinctrl: initialized sunXi PIO driver
[    0.147971] NET: Registered protocol family 2
[    0.148745] tcp_listen_portaddr_hash hash table entries: 512 (order: 1, 8192 bytes, linear)
[    0.148809] TCP established hash table entries: 8192 (order: 4, 65536 bytes, linear)
[    0.148912] TCP bind hash table entries: 8192 (order: 4, 65536 bytes, linear)
[    0.148995] TCP: Hash tables configured (established 8192 bind 8192)
[    0.149181] UDP hash table entries: 512 (order: 2, 16384 bytes, linear)
[    0.149244] UDP-Lite hash table entries: 512 (order: 2, 16384 bytes, linear)
[    0.149527] NET: Registered protocol family 1
[    0.150851] sun8iw20-pinctrl 2000000.pinctrl: 2000000.pinctrl supply vcc-pc not found, using dummy regulator
[    0.151425] spi spi0: spi0 supply spi not found, using dummy regulator
[    0.151691] sunxi_spi_resource_get()2062 - [spi0] SPI MASTER MODE
[    0.151800] sunxi_spi_clk_init()2138 - [spi0] mclk 100000000
[    0.152473] sunxi_spi_probe()2542 - [spi0]: driver probe succeed, base ffffffd00405a000, irq 31
[    0.154348] Initialise system trusted keyrings
[    0.154600] workingset: timestamp_bits=62 max_order=18 bucket_order=0
[    0.162136] squashfs: version 4.0 (2009/01/31) Phillip Lougher
[    0.183287] Key type asymmetric registered
[    0.183302] Asymmetric key parser 'x509' registered
[    0.183326] io scheduler mq-deadline registered
[    0.183334] io scheduler kyber registered
[    0.183354] atomic64_test: passed
[    0.184550] [DISP]disp_module_init
[    0.185114] disp 5000000.disp: Adding to iommu group 0
[    0.185713] [DISP] disp_init,line:2385:
[    0.185719] smooth display screen:0 type:1 mode:4
[    0.224323] display_fb_request,fb_id:0
[    0.254168] disp_al_manager_apply ouput_type:1
[    0.254331] [DISP] lcd_clk_config,line:731:
[    0.254344] disp 0, clk: pll(420000000),clk(420000000),dclk(70000000) dsi_rate(70000000)
[    0.254344]      clk real:pll(420000000),clk(420000000),dclk(105000000) dsi_rate(150000000)
[    0.254735] sun8iw20-pinctrl 2000000.pinctrl: 2000000.pinctrl supply vcc-pd not found, using dummy regulator
[    0.255478] [DISP]disp_module_init finish
[    0.256396] sunxi_sid_init()497 - insmod ok
[    0.256949] pwm-regulator: supplied by regulator-dummy
[    0.264245] sun8iw20-pinctrl 2000000.pinctrl: 2000000.pinctrl supply vcc-pb not found, using dummy regulator
[    0.264689] uart uart0: get regulator failed
[    0.264722] uart uart0: uart0 supply uart not found, using dummy regulator
[    0.265042] uart0: ttyS0 at MMIO 0x2500000 (irq = 18, base_baud = 1500000) is a SUNXI
[    0.265069] sw_console_setup()1808 - console setup baud 115200 parity n bits 8, flow n
[    1.052376] printk: console [ttyS0] enabled
[    1.057964] sun8iw20-pinctrl 2000000.pinctrl: 2000000.pinctrl supply vcc-pg not found, using dummy regulator
[    1.069384] uart uart1: get regulator failed
[    1.074258] uart uart1: uart1 supply uart not found, using dummy regulator
[    1.082317] uart1: ttyS1 at MMIO 0x2500400 (irq = 19, base_baud = 1500000) is a SUNXI
[    1.092266] misc dump reg init
[    1.096284] sunxi-rfkill soc@3000000:rfkill@0: module version: v1.0.9
[    1.103529] sunxi-rfkill soc@3000000:rfkill@0: devm_pinctrl_get() failed!
[    1.111188] sunxi-rfkill soc@3000000:rfkill@0: get gpio chip_en failed
[    1.118478] sunxi-rfkill soc@3000000:rfkill@0: get gpio power_en failed
[    1.125930] sunxi-rfkill soc@3000000:rfkill@0: wlan_busnum (1)
[    1.132465] sunxi-rfkill soc@3000000:rfkill@0: Missing wlan_power.
[    1.139395] sunxi-rfkill soc@3000000:rfkill@0: wlan clock[0] (32k-fanout1)
[    1.147125] sunxi-rfkill soc@3000000:rfkill@0: wlan_regon gpio=204 assert=1
[    1.155023] sunxi-rfkill soc@3000000:rfkill@0: wlan_hostwake gpio=202 assert=1
[    1.163150] sunxi-rfkill soc@3000000:rfkill@0: wakeup source is enabled
[    1.170840] sunxi-rfkill soc@3000000:rfkill@0: Missing bt_power.
[    1.177560] sunxi-rfkill soc@3000000:rfkill@0: bt clock[0] (32k-fanout1)
[    1.185106] sunxi-rfkill soc@3000000:rfkill@0: bt_rst gpio=210 assert=0
[    1.193423] [ADDR_MGT] addr_mgt_probe: module version: v1.0.8
[    1.201016] [ADDR_MGT] addr_mgt_probe: success.
[    1.207040] sunxi-spinand: AW SPINand MTD Layer Version: 2.0 20201228
[    1.214321] sunxi-spinand-phy: AW SPINand Phy Layer Version: 1.10 20200306
[    1.222263] sunxi-spinand-phy: not detect any munufacture from id table
[    1.229644] sunxi-spinand-phy: get spi-nand Model from fdt fail
[    1.236338] sunxi-spinand-phy: get phy info from fdt fail
[    1.242385] sunxi-spinand-phy: not detect munufacture from fdt
[    1.249070] sunxi-spinand-phy: detect munufacture from id table: Mxic
[    1.256322] sunxi-spinand-phy: detect spinand id: ff0326c2 ffffffff
[    1.263331] sunxi-spinand-phy: ========== arch info ==========
[    1.269848] sunxi-spinand-phy: Model:               MX35LF2GE4AD
[    1.276565] sunxi-spinand-phy: Munufacture:         Mxic
[    1.282502] sunxi-spinand-phy: DieCntPerChip:       1
[    1.288147] sunxi-spinand-phy: BlkCntPerDie:        2048
[    1.294091] sunxi-spinand-phy: PageCntPerBlk:       64
[    1.299833] sunxi-spinand-phy: SectCntPerPage:      4
[    1.305487] sunxi-spinand-phy: OobSizePerPage:      64
[    1.311231] sunxi-spinand-phy: BadBlockFlag:        0x1
[    1.317068] sunxi-spinand-phy: OperationOpt:        0x7
[    1.322913] sunxi-spinand-phy: MaxEraseTimes:       65000
[    1.328926] sunxi-spinand-phy: EccFlag:             0x2
[    1.334800] sunxi-spinand-phy: EccType:             8
[    1.340428] sunxi-spinand-phy: EccProtectedType:    3
[    1.346078] sunxi-spinand-phy: ========================================
[    1.353500] sunxi-spinand-phy:
[    1.356997] sunxi-spinand-phy: ========== physical info ==========
[    1.363905] sunxi-spinand-phy: TotalSize:    256 M
[    1.369259] sunxi-spinand-phy: SectorSize:   512 B
[    1.374620] sunxi-spinand-phy: PageSize:     2 K
[    1.379763] sunxi-spinand-phy: BlockSize:    128 K
[    1.385149] sunxi-spinand-phy: OOBSize:      64 B
[    1.390388] sunxi-spinand-phy: ========================================
[    1.397811] sunxi-spinand-phy:
[    1.401332] sunxi-spinand-phy: ========== logical info ==========
[    1.408121] sunxi-spinand-phy: TotalSize:    256 M
[    1.413510] sunxi-spinand-phy: SectorSize:   512 B
[    1.418847] sunxi-spinand-phy: PageSize:     4 K
[    1.424012] sunxi-spinand-phy: BlockSize:    256 K
[    1.429364] sunxi-spinand-phy: OOBSize:      128 B
[    1.434725] sunxi-spinand-phy: ========================================
[    1.442246] sunxi-spinand-phy: block lock register: 0x00
[    1.448356] sunxi-spinand-phy: feature register: 0x11
[    1.454023] sunxi-spinand-phy: sunxi physic nand init end
[    1.460751] Creating 4 MTD partitions on "sunxi_mtd_nand":
[    1.466910] 0x000000000000-0x000000100000 : "boot0"
[    1.491764] 0x000000100000-0x000000500000 : "uboot"
[    1.497884] random: fast init done
[    1.531728] 0x000000500000-0x000000600000 : "secure_storage"
[    1.551735] 0x000000600000-0x000010000000 : "sys"
[    1.944421] random: crng init done
[    2.692245] libphy: Fixed MDIO Bus: probed
[    2.696849] CAN device driver interface
[    2.702713] sun8iw20-pinctrl 2000000.pinctrl: 2000000.pinctrl supply vcc-pe not found, using dummy regulator
[    2.714076] sunxi gmac driver's version: 1.0.0
[    2.719177] gmac-power0: NULL
[    2.722533] gmac-power1: NULL
[    2.725839] gmac-power2: NULL
[    2.730300] Failed to alloc md5
[    2.733898] eth0: Use random mac address
[    2.738639] ehci_hcd: USB 2.0 'Enhanced' Host Controller (EHCI) Driver
[    2.746058] sunxi-ehci: EHCI SUNXI driver
[    2.751159] get ehci1-controller wakeup-source is fail.
[    2.757088] sunxi ehci1-controller don't init wakeup source
[    2.763434] [sunxi-ehci1]: probe, pdev->name: 4200000.ehci1-controller, sunxi_ehci: 0xffffffe0008d6748, 0x:ffffffd004079000, irq_no:31
[    2.777001] sunxi-ehci 4200000.ehci1-controller: 4200000.ehci1-controller supply drvvbus not found, using dummy regulator
[    2.789622] sunxi-ehci 4200000.ehci1-controller: EHCI Host Controller
[    2.796940] sunxi-ehci 4200000.ehci1-controller: new USB bus registered, assigned bus number 1
[    2.806769] sunxi-ehci 4200000.ehci1-controller: irq 49, io mem 0x04200000
[    2.840603] sunxi-ehci 4200000.ehci1-controller: USB 2.0 started, EHCI 1.00
[    2.849339] hub 1-0:1.0: USB hub found
[    2.853658] hub 1-0:1.0: 1 port detected
[    2.858903] ohci_hcd: USB 1.1 'Open' Host Controller (OHCI) Driver
[    2.865901] sunxi-ohci: OHCI SUNXI driver
[    2.871010] get ohci1-controller wakeup-source is fail.
[    2.876976] sunxi ohci1-controller don't init wakeup source
[    2.883237] [sunxi-ohci1]: probe, pdev->name: 4200400.ohci1-controller, sunxi_ohci: 0xffffffe0008d7288
[    2.893712] sunxi-ohci 4200400.ohci1-controller: 4200400.ohci1-controller supply drvvbus not found, using dummy regulator
[    2.906225] sunxi-ohci 4200400.ohci1-controller: OHCI Host Controller
[    2.913544] sunxi-ohci 4200400.ohci1-controller: new USB bus registered, assigned bus number 2
[    2.923343] sunxi-ohci 4200400.ohci1-controller: irq 50, io mem 0x04200400
[    3.005619] hub 2-0:1.0: USB hub found
[    3.009857] hub 2-0:1.0: 1 port detected
[    3.015357] usbcore: registered new interface driver uas
[    3.021566] usbcore: registered new interface driver usb-storage
[    3.028338] usbcore: registered new interface driver ums-alauda
[    3.035088] usbcore: registered new interface driver ums-cypress
[    3.041951] usbcore: registered new interface driver ums-datafab
[    3.048719] usbcore: registered new interface driver ums_eneub6250
[    3.055769] usbcore: registered new interface driver ums-freecom
[    3.062574] usbcore: registered new interface driver ums-isd200
[    3.069232] usbcore: registered new interface driver ums-jumpshot
[    3.076184] usbcore: registered new interface driver ums-karma
[    3.082797] usbcore: registered new interface driver ums-onetouch
[    3.089740] usbcore: registered new interface driver ums-realtek
[    3.096572] usbcore: registered new interface driver ums-sddr09
[    3.103341] usbcore: registered new interface driver ums-sddr55
[    3.109999] usbcore: registered new interface driver ums-usbat
[    3.117655] sunxi_gpadc_init,1968, success
[    3.123212] sunxi-rtc 7090000.rtc: errata__fix_alarm_day_reg_default_value(): ALARM0_DAY_REG=0, set it to 1
[    3.135527] sunxi-rtc 7090000.rtc: registered as rtc0
[    3.141347] sunxi-rtc 7090000.rtc: setting system clock to 1970-01-01T00:00:07 UTC (7)
[    3.150209] sunxi-rtc 7090000.rtc: sunxi rtc probed
[    3.156121] i2c /dev entries driver
[    3.160109] IR NEC protocol handler initialized
[    3.165900] sunxi cedar version 1.1
[    3.170099] sunxi-cedar 1c0e000.ve: Adding to iommu group 0
[    3.176387] VE: install start!!!
[    3.176387]
[    3.181925] VE: cedar-ve the get irq is 6
[    3.181925]
[    3.188266] VE: ve_debug_proc_info:00000000d270e8e5, data:0000000057283f29, lock:00000000eee33918
[    3.188266]
[    3.199912] VE: install end!!!
[    3.199912]
[    3.205858] sunxi-wdt 6011000.watchdog: Watchdog enabled (timeout=16 sec, nowayout=0)
[    3.215022] Bluetooth: HCI UART driver ver 2.3
[    3.220009] Bluetooth: HCI UART protocol H4 registered
[    3.225773] Bluetooth: HCI UART protocol BCSP registered
[    3.231718] Bluetooth: XRadio Bluetooth LPM Mode Driver Ver 1.0.10
[    3.239000] [XR_BT_LPM] bluesleep_probe: bt_wake polarity: 1
[    3.245417] [XR_BT_LPM] bluesleep_probe: host_wake polarity: 1
[    3.252035] [XR_BT_LPM] bluesleep_probe: wakeup source is disabled!
[    3.252035]
[    3.260701] [XR_BT_LPM] bluesleep_probe: uart_index(1)
[    3.270406] sunxi-mmc 4020000.sdmmc: SD/MMC/SDIO Host Controller Driver(v4.19 2021-03-24 19:50)
[    3.280377] sunxi-mmc 4020000.sdmmc: ***ctl-spec-caps*** 8
[    3.286651] sunxi-mmc 4020000.sdmmc: No vmmc regulator found
[    3.292992] sunxi-mmc 4020000.sdmmc: No vqmmc regulator found
[    3.299421] sunxi-mmc 4020000.sdmmc: No vdmmc regulator found
[    3.305853] sunxi-mmc 4020000.sdmmc: No vd33sw regulator found
[    3.312381] sunxi-mmc 4020000.sdmmc: No vd18sw regulator found
[    3.318903] sunxi-mmc 4020000.sdmmc: No vq33sw regulator found
[    3.325433] sunxi-mmc 4020000.sdmmc: No vq18sw regulator found
[    3.332426] sunxi-mmc 4020000.sdmmc: Got CD GPIO
[    3.337897] sunxi-mmc 4020000.sdmmc: set cd-gpios as 24M fail
[    3.344566] sunxi-mmc 4020000.sdmmc: sdc set ios:clk 0Hz bm PP pm UP vdd 21 width 1 timing LEGACY(SDR12) dt B
[    3.355749] sunxi-mmc 4020000.sdmmc: no vqmmc,Check if there is regulator
[    3.375927] sunxi-mmc 4020000.sdmmc: sdc set ios:clk 400000Hz bm PP pm ON vdd 21 width 1 timing LEGACY(SDR12) dt B
[    3.400350] sunxi-mmc 4020000.sdmmc: detmode:gpio irq
[    3.406068] sunxi-mmc 4020000.sdmmc: sdc set ios:clk 400000Hz bm PP pm ON vdd 21 width 1 timing LEGACY(SDR12) dt B
[    3.418337] sunxi-mmc 4021000.sdmmc: SD/MMC/SDIO Host Controller Driver(v4.19 2021-03-24 19:50)
[    3.428456] sunxi-mmc 4021000.sdmmc: ***ctl-spec-caps*** 8
[    3.434723] sunxi-mmc 4021000.sdmmc: No vmmc regulator found
[    3.441106] sunxi-mmc 4021000.sdmmc: No vqmmc regulator found
[    3.447567] sunxi-mmc 4020000.sdmmc: sdc set ios:clk 400000Hz bm PP pm ON vdd 21 width 1 timing LEGACY(SDR12) dt B
[    3.459144] sunxi-mmc 4021000.sdmmc: No vdmmc regulator found
[    3.465621] sunxi-mmc 4021000.sdmmc: No vd33sw regulator found
[    3.472258] sunxi-mmc 4021000.sdmmc: No vd18sw regulator found
[    3.478830] sunxi-mmc 4021000.sdmmc: No vq33sw regulator found
[    3.485411] sunxi-mmc 4021000.sdmmc: No vq18sw regulator found
[    3.492011] sunxi-mmc 4021000.sdmmc: Cann't get pin bias hs pinstate,check if needed
[    3.500732] sunxi-mmc 4020000.sdmmc: sdc set ios:clk 400000Hz bm PP pm ON vdd 21 width 1 timing LEGACY(SDR12) dt B
[    3.513389] sunxi-mmc 4021000.sdmmc: sdc set ios:clk 0Hz bm PP pm UP vdd 21 width 1 timing LEGACY(SDR12) dt B
[    3.524572] sunxi-mmc 4021000.sdmmc: no vqmmc,Check if there is regulator
[    3.533522] sunxi-mmc 4020000.sdmmc: sdc set ios:clk 400000Hz bm PP pm ON vdd 21 width 1 timing LEGACY(SDR12) dt B
[    3.545137] sunxi-mmc 4021000.sdmmc: sdc set ios:clk 400000Hz bm PP pm ON vdd 21 width 1 timing LEGACY(SDR12) dt B
[    3.569480] sunxi-mmc 4021000.sdmmc: detmode:manually by software
[    3.577191] sunxi-mmc 4021000.sdmmc: smc 1 p1 err, cmd 52, RTO !!
[    3.584271] sunxi_led_probe()1715 - start
[    3.588764] sunxi-mmc 4021000.sdmmc: smc 1 p1 err, cmd 52, RTO !!
[    3.595662] sunxi-mmc 4021000.sdmmc: sdc set ios:clk 400000Hz bm PP pm ON vdd 21 width 1 timing LEGACY(SDR12) dt B
[    3.607321] sunxi_get_str_of_property()1560 - failed to get the string of propname led_regulator!
[    3.617415] sunxi_register_led_classdev()1448 - led_classdev start
[    3.626105] sunxi-mmc 4021000.sdmmc: sdc set ios:clk 400000Hz bm PP pm ON vdd 21 width 1 timing LEGACY(SDR12) dt B
[    3.641399] sunxi_led_probe()1820 - finish
[    3.646014] mmc0: host does not support reading read-only switch, assuming write-enable
[    3.655650] usbcore: registered new interface driver usbhid
[    3.662052] usbhid: USB HID core driver
[    3.666394] sunxi-mmc 4020000.sdmmc: sdc set ios:clk 400000Hz bm PP pm ON vdd 21 width 1 timing SD-HS(SDR25) dt B
[    3.678733] sunxi-mmc 4021000.sdmmc: smc 1 p1 err, cmd 5, RTO !!
[    3.686324] sunxi-mmc 4021000.sdmmc: smc 1 p1 err, cmd 5, RTO !!
[    3.693249] sunxi-mmc 4020000.sdmmc: sdc set ios:clk 50000000Hz bm PP pm ON vdd 21 width 1 timing SD-HS(SDR25) dt B
[    3.704904] sunxi-mmc 4021000.sdmmc: smc 1 p1 err, cmd 5, RTO !!
[    3.711955] usbcore: registered new interface driver snd-usb-audio
[    3.718870] sunxi-mmc 4021000.sdmmc: smc 1 p1 err, cmd 5, RTO !!
[    3.725672] sunxi-mmc 4021000.sdmmc: sdc set ios:clk 0Hz bm PP pm OFF vdd 0 width 1 timing LEGACY(SDR12) dt B
[    3.736992] sunxi-mmc 4020000.sdmmc: sdc set ios:clk 50000000Hz bm PP pm ON vdd 21 width 4 timing SD-HS(SDR25) dt B
[    3.752505] sunxi-daudio 2034000.daudio: regulator missing or invalid
[    3.760261] [AUDIOCODEC][sunxi_codec_parse_params][2208]:digital_vol:0, lineout_vol:26, mic1gain:31, mic2gain:31 pa_msleep:120, pa_level:1, pa_pwr_level:1
[    3.760261]
[    3.777596] mmc0: new high speed SDXC card at address e624
[    3.785063] mmcblk0: mmc0:e624 SD64G 59.5 GiB
[    3.792263] [AUDIOCODEC][sunxi_codec_parse_params][2244]:adcdrc_cfg:0, adchpf_cfg:0, dacdrc_cfg:0, dachpf:0
[    3.804159] [AUDIOCODEC][sunxi_internal_codec_probe][2380]:codec probe finished
[    3.814212] debugfs: Directory '203034c.dummy_cpudai' with parent 'audiocodec' already present!
[    3.824284] [SNDCODEC][sunxi_card_init][583]:card init finished
[    3.832871] GPT:Primary header thinks Alt. header is not at the end of the disk.
[    3.841264] sunxi-codec-machine 2030340.sound: 2030000.codec <-> 203034c.dummy_cpudai mapping ok
[    3.851127] GPT:12582911 != 124735487
[    3.855207] GPT:Alternate GPT header not at the end of the disk.
[    3.863332] input: audiocodec sunxi Audio Jack as /devices/platform/soc@3000000/2030340.sound/sound/card0/input1
[    3.874782] GPT:12582911 != 124735487
[    3.878860] GPT: Use GNU Parted to correct GPT errors.
[    3.885354] [SNDCODEC][sunxi_card_dev_probe][832]:register card finished
[    3.892934]  mmcblk0: p1 p2 p3
[    3.899774] NET: Registered protocol family 10
[    3.906309] Segment Routing with IPv6
[    3.910684] sit: IPv6, IPv4 and MPLS over IPv4 tunneling driver
[    3.918096] NET: Registered protocol family 17
[    3.923175] can: controller area network core (rev 20170425 abi 9)
[    3.930176] NET: Registered protocol family 29
[    3.935248] can: raw protocol (rev 20170425)
[    3.940010] can: broadcast manager protocol (rev 20170425 t)
[    3.946368] can: netlink gateway (rev 20190810) max_hops=1
[    3.952867] Bluetooth: RFCOMM TTY layer initialized
[    3.958323] Bluetooth: RFCOMM socket layer initialized
[    3.964218] Bluetooth: RFCOMM ver 1.11
[    3.969421] Loading compiled-in X.509 certificates
[    3.977145] HDMI 2.0 driver init start!
[    3.981562] boot_hdmi=false
[    3.984736] ERROR: pinctrl_get for HDMI2.0 DDC fail
[    3.991726] HDMI2.0 module init end
[    4.021483] twi twi2: twi2 supply twi not found, using dummy regulator
[    4.036649] pcf857x 2-0038: probed
[    4.046836] sunxi_i2c_probe()2262 - [i2c2] probe success
[    4.062780] debugfs: Directory '2031000.dmic' with parent 'snddmic' already present!
[    4.073114] sunxi-audio-card 2031060.sounddmic: snd-soc-dummy-dai <-> 2031000.dmic mapping ok
[    4.084023] debugfs: Directory '2034000.daudio' with parent 'sndhdmi' already present!
[    4.094652] sunxi-audio-card 20340a0.sounddaudio2: snd-soc-dummy-dai <-> 2034000.daudio mapping ok
[    4.106351] get ehci0-controller wakeup-source is fail.
[    4.112399] sunxi ehci0-controller don't init wakeup source
[    4.118619] [sunxi-ehci0]: probe, pdev->name: 4101000.ehci0-controller, sunxi_ehci: 0xffffffe0008d6388, 0x:ffffffd005422000, irq_no:2e
[    4.132200] [sunxi-ehci0]: Not init ehci0
[    4.137160] get ohci0-controller wakeup-source is fail.
[    4.143215] sunxi ohci0-controller don't init wakeup source
[    4.149435] [sunxi-ohci0]: probe, pdev->name: 4101400.ohci0-controller, sunxi_ohci: 0xffffffe0008d6ec8
[    4.159900] [sunxi-ohci0]: Not init ohci0
[    4.165593] ubi0: attaching mtd3
[    5.150828] ubi0: scanning is finished
[    5.170906] ubi0: attached mtd3 (name "sys", size 250 MiB)
[    5.177027] ubi0: PEB size: 262144 bytes (256 KiB), LEB size: 258048 bytes
[    5.184777] ubi0: min./max. I/O unit sizes: 4096/4096, sub-page size 2048
[    5.192390] ubi0: VID header offset: 2048 (aligned 2048), data offset: 4096
[    5.200170] ubi0: good PEBs: 1000, bad PEBs: 0, corrupted PEBs: 0
[    5.206991] ubi0: user volume: 9, internal volumes: 1, max. volumes count: 128
[    5.215111] ubi0: max/mean erase counter: 2/1, WL threshold: 4096, image sequence number: 0
[    5.224487] ubi0: available PEBs: 16, total reserved PEBs: 984, PEBs reserved for bad PEB handling: 20
[    5.234952] ubi0: background thread "ubi_bgt0d" started, PID 71
[    5.243587] block ubiblock0_5: created from ubi0:5(rootfs)
[    5.252087] cfg80211: Loading compiled-in X.509 certificates for regulatory database
[    5.263073] cfg80211: Loaded X.509 cert 'sforshee: 00b28ddf47aef9cea7'
[    5.270506] platform regulatory.0: Direct firmware load for regulatory.db failed with error -2
[    5.280333] clk: Not disabling unused clocks
[    5.285174] cfg80211: failed to load regulatory.db
[    5.290675] ALSA device list:
[    5.293987]   #0: audiocodec
[    5.297222]   #1: snddmic
[    5.300138]   #2: sndhdmi
[    5.303193] alloc_fd: slot 0 not NULL!
[    5.311998] VFS: Mounted root (squashfs filesystem) readonly on device 254:0.
[    5.323605] devtmpfs: mounted
[    5.327108] Freeing unused kernel memory: 208K
[    5.332188] This architecture does not have kernel memory protection.
[    5.339369] Run /sbin/init as init process
[    6.228878] init: Console is alive
[    6.233070] init: - watchdog -
[    6.236635] init: - preinit -
/dev/by-name/UDISK already format by ubifs
[    7.623642] mount_root: mounting /dev/root
[    7.628761] mount_root: loading kmods from internal overlay
[    7.790674] hdmi_hpd_sys_config_release
[    7.921582] block: attempting to load /etc/config/fstab
[    7.966876] UBIFS (ubi0:8): Mounting in unauthenticated mode
[    7.973732] UBIFS (ubi0:8): background thread "ubifs_bgt0_8" started, PID 112
[    8.102672] UBIFS (ubi0:8): recovery needed
[    8.387519] UBIFS (ubi0:8): recovery completed
[    8.393277] UBIFS (ubi0:8): UBIFS: mounted UBI device 0, volume 8, name "UDISK"
[    8.401547] UBIFS (ubi0:8): LEB size: 258048 bytes (252 KiB), min./max. I/O unit sizes: 4096 bytes/4096 bytes
[    8.412635] UBIFS (ubi0:8): FS size: 192503808 bytes (183 MiB, 746 LEBs), journal size 9420800 bytes (8 MiB, 37 LEBs)
[    8.424556] UBIFS (ubi0:8): reserved for root: 0 bytes (0 KiB)
[    8.431134] UBIFS (ubi0:8): media format: w4/r0 (latest is w5/r0), UUID C52479B2-BE6E-4AB0-AEA5-9287F7AC9F17, small LPT model
[    8.448075] block: extroot: UUID match (root: e4aac755-48e1b7c8-b32425c0-67317875, overlay: e4aac755-48e1b7c8-b32425c0-67317875)
[    8.469820] mount_root: switched to extroot
[    8.491540] procd: - early -
[    8.494907] procd: - watchdog -
[    8.883812] procd: - watchdog -
[    8.887699] procd: - ubus -
[    8.900810] procd (1): /proc/124/oom_adj is deprecated, please use /proc/124/oom_score_adj instead.
[    8.920619]
[    8.920619] insmod_device_driver
[    8.920619]
[    9.141018] procd: - init -
Please press Enter to activate this console.
[   10.368473] fuse: init (API version 7.31)
[   10.496641] file system registered
[   10.669675] configfs-gadget 4100000.udc-controller: failed to start g1: -19
[   10.677940] get ctp_power is fail, -22
[   10.682228] get ctp_power_ldo_vol is fail, -22
[   10.687198] sunxi_ctp_startup: ctp_power_io is invalid.
[   10.740713] get ctp_gesture_wakeup fail, no gesture wakeup
[   10.746860] gt9xxnew_ts 2-0014: 2-0014 supply ctp not found, using dummy regulator
[   10.954221] read descriptors
[   10.957448] read strings
[   11.110889] sunxi_i2c_do_xfer()1816 - [i2c2] incomplete xfer (status: 0x20, dev addr: 0x14)
[   11.128596] sunxi_i2c_do_xfer()1816 - [i2c2] incomplete xfer (status: 0x20, dev addr: 0x14)
[   11.150833] sunxi_i2c_do_xfer()1816 - [i2c2] incomplete xfer (status: 0x20, dev addr: 0x14)
[   11.170732] sunxi_i2c_do_xfer()1816 - [i2c2] incomplete xfer (status: 0x20, dev addr: 0x14)
[   11.185167] sunxi_i2c_do_xfer()1816 - [i2c2] incomplete xfer (status: 0x20, dev addr: 0x14)
[   11.208304] <<-GTP-ERROR->> I2C Read: 0x8047, 1 bytes failed, errcode: -70! Process reset.
[   11.390643] <<-GTP-ERROR->> GTP i2c test failed time 1.
[   11.420890] sunxi_i2c_do_xfer()1816 - [i2c2] incomplete xfer (status: 0x20, dev addr: 0x14)
[   11.440684] sunxi_i2c_do_xfer()1816 - [i2c2] incomplete xfer (status: 0x20, dev addr: 0x14)
[   11.460670] sunxi_i2c_do_xfer()1816 - [i2c2] incomplete xfer (status: 0x20, dev addr: 0x14)
[   11.474844] sunxi_i2c_do_xfer()1816 - [i2c2] incomplete xfer (status: 0x20, dev addr: 0x14)
[   11.498199] sunxi_i2c_do_xfer()1816 - [i2c2] incomplete xfer (status: 0x20, dev addr: 0x14)
[   11.520717] <<-GTP-ERROR->> I2C Read: 0x8047, 1 bytes failed, errcode: -70! Process reset.
[   11.680763] <<-GTP-ERROR->> GTP i2c test failed time 2.
[   11.710873] sunxi_i2c_do_xfer()1816 - [i2c2] incomplete xfer (status: 0x20, dev addr: 0x14)
[   11.727926] sunxi_i2c_do_xfer()1816 - [i2c2] incomplete xfer (status: 0x20, dev addr: 0x14)
[   11.751379] sunxi_i2c_do_xfer()1816 - [i2c2] incomplete xfer (status: 0x20, dev addr: 0x14)
[   11.770884] sunxi_i2c_do_xfer()1816 - [i2c2] incomplete xfer (status: 0x20, dev addr: 0x14)
[   11.790642] sunxi_i2c_do_xfer()1816 - [i2c2] incomplete xfer (status: 0x20, dev addr: 0x14)
[   11.799991] <<-GTP-ERROR->> I2C Read: 0x8047, 1 bytes failed, errcode: -70! Process reset.
[   11.990644] <<-GTP-ERROR->> GTP i2c test failed time 3.
[   12.020875] sunxi_i2c_do_xfer()1816 - [i2c2] incomplete xfer (status: 0x20, dev addr: 0x14)
[   12.039964] sunxi_i2c_do_xfer()1816 - [i2c2] incomplete xfer (status: 0x20, dev addr: 0x14)
[   12.060874] sunxi_i2c_do_xfer()1816 - [i2c2] incomplete xfer (status: 0x20, dev addr: 0x14)
[   12.080719] sunxi_i2c_do_xfer()1816 - [i2c2] incomplete xfer (status: 0x20, dev addr: 0x14)
[   12.096590] sunxi_i2c_do_xfer()1816 - [i2c2] incomplete xfer (status: 0x20, dev addr: 0x14)
[   12.119795] <<-GTP-ERROR->> I2C Read: 0x8047, 1 bytes failed, errcode: -70! Process reset.
[   12.300627] <<-GTP-ERROR->> GTP i2c test failed time 4.
[   12.330806] sunxi_i2c_do_xfer()1816 - [i2c2] incomplete xfer (status: 0x20, dev addr: 0x14)
[   12.350702] sunxi_i2c_do_xfer()1816 - [i2c2] incomplete xfer (status: 0x20, dev addr: 0x14)
[   12.369094] sunxi_i2c_do_xfer()1816 - [i2c2] incomplete xfer (status: 0x20, dev addr: 0x14)
[   12.386676] sunxi_i2c_do_xfer()1816 - [i2c2] incomplete xfer (status: 0x20, dev addr: 0x14)
[   12.409108] sunxi_i2c_do_xfer()1816 - [i2c2] incomplete xfer (status: 0x20, dev addr: 0x14)
[   12.418927] <<-GTP-ERROR->> I2C Read: 0x8047, 1 bytes failed, errcode: -70! Process reset.
[   12.580651] <<-GTP-ERROR->> GTP i2c test failed time 5.
[   12.650018] I2C communication ERROR!
[   12.650056] regulator-dummy: Underflow of regulator enable count
[   12.661324] gt9xxnew_ts: probe of 2-0014 failed with error -1
[   15.171039] ======== XRADIO WIFI OPEN ========
[   15.190690] [XRADIO] Driver Label:XR_V02.16.84_P2P_HT40_01.31
[   15.197442] [XRADIO] Allocated hw_priv @ 00000000f002c4dc
[   15.220648] sunxi-rfkill soc@3000000:rfkill@0: bus_index: 1
[   15.236900] sunxi-rfkill soc@3000000:rfkill@0: wlan power on success
[   15.660642] sunxi-mmc 4021000.sdmmc: sdc set ios:clk 0Hz bm PP pm UP vdd 21 width 1 timing LEGACY(SDR12) dt B
[   15.671755] [XRADIO] Detect SDIO card 1
[   15.690719] sunxi-mmc 4021000.sdmmc: no vqmmc,Check if there is regulator
[   15.710623] sunxi-mmc 4021000.sdmmc: sdc set ios:clk 400000Hz bm PP pm ON vdd 21 width 1 timing LEGACY(SDR12) dt B
[   15.753900] sunxi-mmc 4021000.sdmmc: sdc set ios:clk 400000Hz bm PP pm ON vdd 21 width 1 timing LEGACY(SDR12) dt B
[   15.783646] sunxi-mmc 4021000.sdmmc: sdc set ios:clk 400000Hz bm PP pm ON vdd 21 width 1 timing LEGACY(SDR12) dt B
[   15.821842] sunxi-mmc 4021000.sdmmc: sdc set ios:clk 400000Hz bm PP pm ON vdd 21 width 1 timing SD-HS(SDR25) dt B
[   15.850684] sunxi-mmc 4021000.sdmmc: sdc set ios:clk 50000000Hz bm PP pm ON vdd 21 width 1 timing SD-HS(SDR25) dt B
[   15.870801] sunxi-mmc 4021000.sdmmc: sdc set ios:clk 50000000Hz bm PP pm ON vdd 21 width 4 timing SD-HS(SDR25) dt B
[   15.901870] mmc1: new high speed SDIO card at address 0001
[   15.921178] [SBUS] XRadio Device:sdio clk=50000000
[   15.940707] [XRADIO] XRADIO_HW_REV 1.0 detected.
[   16.111277] [XRADIO] xradio_update_dpllctrl: DPLL_CTRL Sync=0x00c00000.
[   16.263850] [XRADIO] Bootloader complete
[   16.420773] [XRADIO] Firmware completed.
[   16.432106] [WSM] Firmware Label:XR_C09.08.52.64_DBG_02.100 2GHZ HT40 Jan  3 2020 13:14:37
[   16.460697] [XRADIO] Firmware Startup Done.
[   16.471151] [XRADIO_WRN] enable Multi-Rx!
[   16.483216] ieee80211 phy0: Selected rate control algorithm 'minstrel_ht'
[   16.540848] Error: Driver 'gt9xxnew_ts' is already registered, aborting...
[   17.268449] ieee80211_do_open: vif_type=2, p2p=0, ch=3, addr=10:a0:f3:a6:c0:44
[   17.294021] [STA] !!!xradio_vif_setup: id=0, type=2, p2p=0, addr=10:a0:f3:a6:c0:44
[   17.326132] [AP_WRN] BSS_CHANGED_ASSOC but driver is unjoined.
Trying to connect to SWUpdate...
[   35.680629] usb1-vbus: disabling
```

系统停在`[   35.680629] usb1-vbus: disabling`不动，回车后进入Tina Linux，如下

```
BusyBox v1.27.2 () built-in shell (ash)

 _____  _              __     _
|_   _||_| ___  _ _   |  |   |_| ___  _ _  _ _
  | |   _ |   ||   |  |  |__ | ||   || | ||_'_|
  | |  | || | || _ |  |_____||_||_|_||___||_,_|
  |_|  |_||_|_||_|_|  Tina is Based on OpenWrt!
 ----------------------------------------------
 Tina Linux (Neptune, 5C1C9C53)
 ----------------------------------------------
root@TinaLinux:/#

```
