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
]HELLO! BOOT0 is starting!
[405]BOOT0 commit : 2337244-dirty

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

[00.647]DRAM:  1 GiB
[00.649]Relocation Offset is: 3deeb000
[00.654]secure enable bit: 0
[00.656]CPU=1008 MHz,PLL6=600 Mhz,AHB=200 Mhz, APB1=100Mhz  MBus=300Mhz
initr_ledc
unable to find ledc node in device tree.
[00.667]flash init start
[00.670]workmode = 0,storage type = 0
[00.676]sunxi-spinand-phy: not detect any munufacture from id table
[00.682]sunxi-spinand-phy: get spi-nand Model from fdt fail
[00.687]sunxi-spinand-phy: get phy info from fdt fail

device nand0 <nand>, # parts = 4
 #: name		size		offset		mask_flags
 0: boot0               0x00100000	0x00000000	1
 1: uboot               0x00300000	0x00100000	1
 2: secure_storage      0x00100000	0x00400000	1
 3: sys                 0x0fb00000	0x00500000	0

active partition: nand0,0 - (boot0) 0x00100000 @ 0x00000000

defaults:
mtdids  : nand0=nand
mtdparts: mtdparts=nand:1024k@0(boot0)ro,3072k@1048576(uboot)ro,1024k@4194304(secure_storage)ro,-(sys)
[01.022]ubi0: attaching mtd4
[01.416]ubi0: scanning is finished
[01.426]ubi0: attached mtd4 (name "sys", size 251 MiB)
[01.431]ubi0: PEB size: 262144 bytes (256 KiB), LEB size: 258048 bytes
[01.437]ubi0: min./max. I/O unit sizes: 4096/4096, sub-page size 2048
[01.443]ubi0: VID header offset: 2048 (aligned 2048), data offset: 4096
[01.449]ubi0: good PEBs: 1004, bad PEBs: 0, corrupted PEBs: 0
[01.455]ubi0: user volume: 9, internal volumes: 1, max. volumes count: 128
[01.461]ubi0: max/mean erase counter: 2/1, WL threshold: 4096, image sequence number: 0
[01.469]ubi0: available PEBs: 0, total reserved PEBs: 1004, PEBs reserved for bad PEB handling: 40
[01.478]sunxi flash init ok
[01.480]line:714 init_clocks
__clk_init: clk pll_periph0x2 already initialized
register fix_factor clk error
[01.491]drv_disp_init
partno erro : can't find partition bootloader
** Unable to read file lcd_compatible_index.txt **
[01.726]do_fat_fsload for lcd config failed
request pwm success, pwm2:pwm2:0x2000c00.
[01.741]drv_disp_init finish
[01.743]boot_gui_init:start
[01.746]set disp.dev2_output_type fail. using defval=0
[01.938]boot_gui_init:finish
[02.350]LCD open finish
partno erro : can't find partition bootloader
54 bytes read in 1 ms (52.7 KiB/s)
[02.512]bmp_name=bootlogo.bmp size 38454
38454 bytes read in 5 ms (7.3 MiB/s)
[02.727]Loading Environment from SUNXI_FLASH... OK
[02.761]Item0 (Map) magic is bad
[02.763]usb burn from boot
delay time 0
weak:otg_phy_config
[02.775]usb prepare ok
[03.578]overtime
[03.582]do_burn_from_boot usb : no usb exist
[03.606]update bootcmd
[03.628]change working_fdt 0x7eaaad70 to 0x7ea8ad70
partno erro : can't find partition bootloader
** Unable to read file lcd_compatible_index.txt **
[03.679]do_fat_fsload for lcd config failed
partno erro : can't find partition bootloader
[03.706]please enable FAT_WRITE for lcd compatible first
partno erro : can't find partition bootloader
** Unable to read file lcd_compatible_index.txt **
[03.740]do_fat_fsload for lcd config failed
[03.745]libfdt fdt_path_offset() for lcd
[03.748]update dts
Hit any key to stop autoboot:  0 
dsp0:gpio init config fail
DSP0 start ok, img length 252960, booting from 0x400660
Android's image name: d1-nezha
No reserved memory region found in source FDT
[04.700]
Starting kernel ...

[    0.000000] OF: fdt: Ignoring memory range 0x40000000 - 0x40200000
[    0.000000] Linux version 5.4.61 (wuhuabin@AwExdroid86) (riscv64-unknown-linux-gnu-gcc (C-SKY RISCV To Binutils) 2.32) #49 PREEMPT Wed Apr 28 09:23:43 UTC 2021
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
[    0.000000] Kernel command line: ubi.mtd=sys ubi.block=0,rootfs earlyprintk=sunxi-uart,0x02500000 clk_tyS0,115200 loglevel=8 root=/dev/ubiblock0_5 rootfstype=squashfs init=/sbin/init partitions=mbr@ubi0_0:bo@ubi0_3:boot@ubi0_4:rootfs@ubi0_5:dsp0@ubi0_6:recovery@ubi0_7:UDISK@ubi0_8: cma=8M snum= mac_addr= wifi_mt.hardware=sun20iw1p1 boot_type=5 androidboot.boot_type=5 gpt=1 uboot_message=2018.05-00107-gc22c3d075c(0
[    0.000000] Dentry cache hash table entries: 131072 (order: 8, 1048576 bytes, linear)
[    0.000000] Inode-cache hash table entries: 65536 (order: 7, 524288 bytes, linear)
[    0.000000] Sorting __ex_table...
[    0.000000] mem auto-init: stack:off, heap alloc:off, heap free:off
[    0.000000] Memory: 1008024K/1046528K available (5944K kernel code, 655K rwdata, 2062K rodata, 208K in-reserved)
[    0.000000] SLUB: HWalign=64, Order=0-3, MinObjects=0, CPUs=1, Nodes=1
[    0.000000] rcu: Preemptible hierarchical RCU implementation.
[    0.000000] 	Tasks RCU enabled.
[    0.000000] rcu: RCU calculated value of scheduler-enlistment delay is 10 jiffies.
[    0.000000] NR_IRQS: 0, nr_irqs: 0, preallocated irqs: 0
[    0.000000] plic: mapped 200 interrupts with 1 handlers for 2 contexts.
[    0.000000] riscv_timer_init_dt: Registering clocksource cpuid [0] hartid [0]
[    0.000000] clocksource: riscv_clocksource: mask: 0xffffffffffffffff max_cycles: 0x588fe9dc0, max_idle
[    0.000006] sched_clock: 64 bits at 24MHz, resolution 41ns, wraps every 4398046511097ns
[    0.000023] riscv_timer_clockevent depends on broadcast, but no broadcast function available
[    0.000331] clocksource: timer: mask: 0xffffffff max_cycles: 0xffffffff, max_idle_ns: 79635851949 ns
[    0.000931] Console: colour dummy device 80x25
[    0.000973] Calibrating delay loop (skipped), value calculated using timer frequency.. 48.00 BogoMIPS 
[    0.000989] pid_max: default: 32768 minimum: 301
[    0.001188] Mount-cache hash table entries: 2048 (order: 2, 16384 bytes, linear)
[    0.001217] Mountpoint-cache hash table entries: 2048 (order: 2, 16384 bytes, linear)
[    0.002942] ASID allocator initialised with 65536 entries
[    0.003107] rcu: Hierarchical SRCU implementation.
[    0.003809] devtmpfs: initialized
[    0.015705] random: get_random_u32 called from bucket_table_alloc.isra.31+0x4e/0x15e with crng_init=0
[    0.016580] clocksource: jiffies: mask: 0xffffffff max_cycles: 0xffffffff, max_idle_ns: 19112604462750
[    0.016611] futex hash table entries: 256 (order: 0, 6144 bytes, linear)
[    0.017046] pinctrl core: initialized pinctrl subsystem
[    0.018376] NET: Registered protocol family 16
[    0.020303] DMA: preallocated 256 KiB pool for atomic allocations
[    0.020923] cpuidle: using governor menu
[    0.066040] rtc_ccu: sunxi ccu init OK
[    0.072535] clock: sunxi ccu init OK
[    0.073467] clock: sunxi ccu init OK
[    0.112315] iommu: Default domain type: Translated 
[    0.112487] sunxi iommu: irq = 4
[    0.113660] SCSI subsystem initialized
[    0.114001] usbcore: registered new interface driver usbfs
[    0.114102] usbcore: registered new interface driver hub
[    0.114206] usbcore: registered new device driver usb
[    0.114386] mc: Linux media interface: v0.10
[    0.114448] videodev: Linux video capture interface: v2.00
[    0.115409] Advanced Linux Sound Architecture Driver Initialized.
[    0.116002] Bluetooth: Core ver 2.22
[    0.116081] NET: Registered protocol family 31
[    0.116092] Bluetooth: HCI device and connection manager initialized
[    0.116112] Bluetooth: HCI socket layer initialized
[    0.116124] Bluetooth: L2CAP socket layer initialized
[    0.116159] Bluetooth: SCO socket layer initialized
[    0.116439] pwm module init!
[    0.117967] g2d 5410000.g2d: Adding to iommu group 0
[    0.118452] G2D: rcq version initialized.major:250
[    0.119000] input: sunxi-keyboard as /devices/virtual/input/input0
[    0.120595] clocksource: Switched to clocksource riscv_clocksource
[    0.132325] sun8iw20-pinctrl 2000000.pinctrl: initialized sunXi PIO driver
[    0.148042] NET: Registered protocol family 2
[    0.148815] tcp_listen_portaddr_hash hash table entries: 512 (order: 1, 8192 bytes, linear)
[    0.148879] TCP established hash table entries: 8192 (order: 4, 65536 bytes, linear)
[    0.148982] TCP bind hash table entries: 8192 (order: 4, 65536 bytes, linear)
[    0.149064] TCP: Hash tables configured (established 8192 bind 8192)
[    0.149254] UDP hash table entries: 512 (order: 2, 16384 bytes, linear)
[    0.149316] UDP-Lite hash table entries: 512 (order: 2, 16384 bytes, linear)
[    0.149600] NET: Registered protocol family 1
[    0.150922] sun8iw20-pinctrl 2000000.pinctrl: 2000000.pinctrl supply vcc-pc not found, using dummy reg
[    0.151494] spi spi0: spi0 supply spi not found, using dummy regulator
[    0.151762] sunxi_spi_resource_get()2062 - [spi0] SPI MASTER MODE
[    0.151872] sunxi_spi_clk_init()2138 - [spi0] mclk 100000000
[    0.152542] sunxi_spi_probe()2542 - [spi0]: driver probe succeed, base ffffffd00405a000, irq 31
[    0.154413] Initialise system trusted keyrings
[    0.154661] workingset: timestamp_bits=62 max_order=18 bucket_order=0
[    0.162188] squashfs: version 4.0 (2009/01/31) Phillip Lougher
[    0.181880] Key type asymmetric registered
[    0.181894] Asymmetric key parser 'x509' registered
[    0.181918] io scheduler mq-deadline registered
[    0.181926] io scheduler kyber registered
[    0.181946] atomic64_test: passed
[    0.183140] [DISP]disp_module_init
[    0.183705] disp 5000000.disp: Adding to iommu group 0
[    0.184302] [DISP] disp_init,line:2385:
[    0.184308] smooth display screen:0 type:1 mode:4
[    0.223051] display_fb_request,fb_id:0
[    0.252905] disp_al_manager_apply ouput_type:1
[    0.253069] [DISP] lcd_clk_config,line:731:
[    0.253082] disp 0, clk: pll(420000000),clk(420000000),dclk(70000000) dsi_rate(70000000)
[    0.253082]      clk real:pll(420000000),clk(420000000),dclk(105000000) dsi_rate(150000000)
[    0.253475] sun8iw20-pinctrl 2000000.pinctrl: 2000000.pinctrl supply vcc-pd not found, using dummy reg
[    0.254218] [DISP]disp_module_init finish
[    0.255129] sunxi_sid_init()497 - insmod ok
[    0.255677] pwm-regulator: supplied by regulator-dummy
[    0.262918] sun8iw20-pinctrl 2000000.pinctrl: 2000000.pinctrl supply vcc-pb not found, using dummy reg
[    0.263362] uart uart0: get regulator failed
[    0.263392] uart uart0: uart0 supply uart not found, using dummy regulator
[    0.263712] uart0: ttyS0 at MMIO 0x2500000 (irq = 18, base_baud = 1500000) is a SUNXI
[    0.263739] sw_console_setup()1808 - console setup baud 115200 parity n bits 8, flow n
[    1.051082] printk: console [ttyS0] enabled
[    1.056644] sun8iw20-pinctrl 2000000.pinctrl: 2000000.pinctrl supply vcc-pg not found, using dummy reg
[    1.068107] uart uart1: get regulator failed
[    1.072935] uart uart1: uart1 supply uart not found, using dummy regulator
[    1.081032] uart1: ttyS1 at MMIO 0x2500400 (irq = 19, base_baud = 1500000) is a SUNXI
[    1.090944] misc dump reg init
[    1.095027] sunxi-rfkill soc@3000000:rfkill@0: module version: v1.0.9
[    1.102273] sunxi-rfkill soc@3000000:rfkill@0: devm_pinctrl_get() failed!
[    1.109856] sunxi-rfkill soc@3000000:rfkill@0: get gpio chip_en failed
[    1.117221] sunxi-rfkill soc@3000000:rfkill@0: get gpio power_en failed
[    1.124641] sunxi-rfkill soc@3000000:rfkill@0: wlan_busnum (1)
[    1.131209] sunxi-rfkill soc@3000000:rfkill@0: Missing wlan_power.
[    1.138122] sunxi-rfkill soc@3000000:rfkill@0: wlan clock[0] (32k-fanout1)
[    1.145885] sunxi-rfkill soc@3000000:rfkill@0: wlan_regon gpio=204 assert=1
[    1.153744] sunxi-rfkill soc@3000000:rfkill@0: wlan_hostwake gpio=202 assert=1
[    1.161913] sunxi-rfkill soc@3000000:rfkill@0: wakeup source is enabled
[    1.169532] sunxi-rfkill soc@3000000:rfkill@0: Missing bt_power.
[    1.176346] sunxi-rfkill soc@3000000:rfkill@0: bt clock[0] (32k-fanout1)
[    1.183879] sunxi-rfkill soc@3000000:rfkill@0: bt_rst gpio=210 assert=0
[    1.192141] [ADDR_MGT] addr_mgt_probe: module version: v1.0.8
[    1.199742] [ADDR_MGT] addr_mgt_probe: success.
[    1.205786] sunxi-spinand: AW SPINand MTD Layer Version: 2.0 20201228
[    1.213102] sunxi-spinand-phy: AW SPINand Phy Layer Version: 1.10 20200306
[    1.221001] sunxi-spinand-phy: not detect any munufacture from id table
[    1.228403] sunxi-spinand-phy: get spi-nand Model from fdt fail
[    1.235065] sunxi-spinand-phy: get phy info from fdt fail
[    1.241175] sunxi-spinand-phy: not detect munufacture from fdt
[    1.247861] sunxi-spinand-phy: detect munufacture from id table: Mxic
[    1.255077] sunxi-spinand-phy: detect spinand id: ff0326c2 ffffffff
[    1.262120] sunxi-spinand-phy: ========== arch info ==========
[    1.268623] sunxi-spinand-phy: Model:               MX35LF2GE4AD
[    1.275372] sunxi-spinand-phy: Munufacture:         Mxic
[    1.281315] sunxi-spinand-phy: DieCntPerChip:       1
[    1.286941] sunxi-spinand-phy: BlkCntPerDie:        2048
[    1.292911] sunxi-spinand-phy: PageCntPerBlk:       64
[    1.298635] sunxi-spinand-phy: SectCntPerPage:      4
[    1.304286] sunxi-spinand-phy: OobSizePerPage:      64
[    1.310026] sunxi-spinand-phy: BadBlockFlag:        0x1
[    1.315873] sunxi-spinand-phy: OperationOpt:        0x7
[    1.321716] sunxi-spinand-phy: MaxEraseTimes:       65000
[    1.327748] sunxi-spinand-phy: EccFlag:             0x2
[    1.333594] sunxi-spinand-phy: EccType:             8
[    1.339237] sunxi-spinand-phy: EccProtectedType:    3
[    1.344887] sunxi-spinand-phy: ========================================
[    1.352278] sunxi-spinand-phy: 
[    1.355789] sunxi-spinand-phy: ========== physical info ==========
[    1.362703] sunxi-spinand-phy: TotalSize:    256 M
[    1.368040] sunxi-spinand-phy: SectorSize:   512 B
[    1.373428] sunxi-spinand-phy: PageSize:     2 K
[    1.378571] sunxi-spinand-phy: BlockSize:    128 K
[    1.383930] sunxi-spinand-phy: OOBSize:      64 B
[    1.389185] sunxi-spinand-phy: ========================================
[    1.396580] sunxi-spinand-phy: 
[    1.400077] sunxi-spinand-phy: ========== logical info ==========
[    1.406921] sunxi-spinand-phy: TotalSize:    256 M
[    1.412280] sunxi-spinand-phy: SectorSize:   512 B
[    1.417616] sunxi-spinand-phy: PageSize:     4 K
[    1.422812] sunxi-spinand-phy: BlockSize:    256 K
[    1.428149] sunxi-spinand-phy: OOBSize:      128 B
[    1.433507] sunxi-spinand-phy: ========================================
[    1.441052] sunxi-spinand-phy: block lock register: 0x00
[    1.447140] sunxi-spinand-phy: feature register: 0x11
[    1.452839] sunxi-spinand-phy: sunxi physic nand init end
[    1.459485] Creating 4 MTD partitions on "sunxi_mtd_nand":
[    1.465698] 0x000000000000-0x000000100000 : "boot0"
[    1.481832] 0x000000100000-0x000000500000 : "uboot"
[    1.487993] random: fast init done
[    1.521769] 0x000000500000-0x000000600000 : "secure_storage"
[    1.541776] 0x000000600000-0x000010000000 : "sys"
[    1.936216] random: crng init done
[    2.682297] libphy: Fixed MDIO Bus: probed
[    2.686922] CAN device driver interface
[    2.692801] sun8iw20-pinctrl 2000000.pinctrl: 2000000.pinctrl supply vcc-pe not found, using dummy reg
[    2.704163] sunxi gmac driver's version: 1.0.0
[    2.709265] gmac-power0: NULL
[    2.712619] gmac-power1: NULL
[    2.715924] gmac-power2: NULL
[    2.720404] Failed to alloc md5
[    2.724002] eth0: Use random mac address
[    2.728742] ehci_hcd: USB 2.0 'Enhanced' Host Controller (EHCI) Driver
[    2.736158] sunxi-ehci: EHCI SUNXI driver
[    2.741253] get ehci1-controller wakeup-source is fail.
[    2.747180] sunxi ehci1-controller don't init wakeup source
[    2.753529] [sunxi-ehci1]: probe, pdev->name: 4200000.ehci1-controller, sunxi_ehci: 0xffffffe0008d6748
[    2.767096] sunxi-ehci 4200000.ehci1-controller: 4200000.ehci1-controller supply drvvbus not found, us
[    2.779718] sunxi-ehci 4200000.ehci1-controller: EHCI Host Controller
[    2.787033] sunxi-ehci 4200000.ehci1-controller: new USB bus registered, assigned bus number 1
[    2.796861] sunxi-ehci 4200000.ehci1-controller: irq 49, io mem 0x04200000
[    2.830645] sunxi-ehci 4200000.ehci1-controller: USB 2.0 started, EHCI 1.00
[    2.838438] sunxi-ehci 4200000.ehci1-controller: ehci_irq: highspeed device connect
[    2.847963] hub 1-0:1.0: USB hub found
[    2.852319] hub 1-0:1.0: 1 port detected
[    2.857507] ohci_hcd: USB 1.1 'Open' Host Controller (OHCI) Driver
[    2.864504] sunxi-ohci: OHCI SUNXI driver
[    2.869560] get ohci1-controller wakeup-source is fail.
[    2.875573] sunxi ohci1-controller don't init wakeup source
[    2.881899] [sunxi-ohci1]: probe, pdev->name: 4200400.ohci1-controller, sunxi_ohci: 0xffffffe0008d7288
[    2.892338] sunxi-ohci 4200400.ohci1-controller: 4200400.ohci1-controller supply drvvbus not found, us
[    2.904883] sunxi-ohci 4200400.ohci1-controller: OHCI Host Controller
[    2.912155] sunxi-ohci 4200400.ohci1-controller: new USB bus registered, assigned bus number 2
[    2.922000] sunxi-ohci 4200400.ohci1-controller: irq 50, io mem 0x04200400
[    2.995670] hub 2-0:1.0: USB hub found
[    2.999911] hub 2-0:1.0: 1 port detected
[    3.005411] usbcore: registered new interface driver uas
[    3.011575] usbcore: registered new interface driver usb-storage
[    3.018387] usbcore: registered new interface driver ums-alauda
[    3.025136] usbcore: registered new interface driver ums-cypress
[    3.032001] usbcore: registered new interface driver ums-datafab
[    3.038766] usbcore: registered new interface driver ums_eneub6250
[    3.045817] usbcore: registered new interface driver ums-freecom
[    3.052619] usbcore: registered new interface driver ums-isd200
[    3.059276] usbcore: registered new interface driver ums-jumpshot
[    3.066224] usbcore: registered new interface driver ums-karma
[    3.073009] usbcore: registered new interface driver ums-onetouch
[    3.079953] usbcore: registered new interface driver ums-realtek
[    3.086793] usbcore: registered new interface driver ums-sddr09
[    3.093556] usbcore: registered new interface driver ums-sddr55
[    3.100217] usbcore: registered new interface driver ums-usbat
[    3.107954] sunxi_gpadc_init,1968, success
[    3.113548] sunxi-rtc 7090000.rtc: errata__fix_alarm_day_reg_default_value(): ALARM0_DAY_REG=0, set it
[    3.125847] sunxi-rtc 7090000.rtc: registered as rtc0
[    3.131664] sunxi-rtc 7090000.rtc: setting system clock to 1970-01-01T00:00:07 UTC (7)
[    3.140525] sunxi-rtc 7090000.rtc: sunxi rtc probed
[    3.146443] i2c /dev entries driver
[    3.150429] IR NEC protocol handler initialized
[    3.156363] sunxi cedar version 1.1
[    3.160563] sunxi-cedar 1c0e000.ve: Adding to iommu group 0
[    3.166853] VE: install start!!!
[    3.166853] 
[    3.172389] VE: cedar-ve the get irq is 6
[    3.172389] 
[    3.178730] VE: ve_debug_proc_info:000000004b2c7c0b, data:000000001472c533, lock:000000006675f5a8
[    3.178730] 
[    3.190361] VE: install end!!!
[    3.190361] 
[    3.196302] sunxi-wdt 6011000.watchdog: Watchdog enabled (timeout=16 sec, nowayout=0)
[    3.205465] Bluetooth: HCI UART driver ver 2.3
[    3.210454] Bluetooth: HCI UART protocol H4 registered
[    3.216221] Bluetooth: HCI UART protocol BCSP registered
[    3.222192] usb 1-1: new high-speed USB device number 2 using sunxi-ehci
[    3.229740] Bluetooth: XRadio Bluetooth LPM Mode Driver Ver 1.0.10
[    3.237134] [XR_BT_LPM] bluesleep_probe: bt_wake polarity: 1
[    3.243632] [XR_BT_LPM] bluesleep_probe: host_wake polarity: 1
[    3.250169] [XR_BT_LPM] bluesleep_probe: wakeup source is disabled!
[    3.250169] 
[    3.258880] [XR_BT_LPM] bluesleep_probe: uart_index(1)
[    3.268629] sunxi-mmc 4020000.sdmmc: SD/MMC/SDIO Host Controller Driver(v4.19 2021-03-24 19:50)
[    3.278646] sunxi-mmc 4020000.sdmmc: ***ctl-spec-caps*** 8
[    3.284870] sunxi-mmc 4020000.sdmmc: No vmmc regulator found
[    3.291250] sunxi-mmc 4020000.sdmmc: No vqmmc regulator found
[    3.297659] sunxi-mmc 4020000.sdmmc: No vdmmc regulator found
[    3.304150] sunxi-mmc 4020000.sdmmc: No vd33sw regulator found
[    3.310812] sunxi-mmc 4020000.sdmmc: No vd18sw regulator found
[    3.317319] sunxi-mmc 4020000.sdmmc: No vq33sw regulator found
[    3.323894] sunxi-mmc 4020000.sdmmc: No vq18sw regulator found
[    3.330880] sunxi-mmc 4020000.sdmmc: Got CD GPIO
[    3.336352] sunxi-mmc 4020000.sdmmc: set cd-gpios as 24M fail
[    3.343069] sunxi-mmc 4020000.sdmmc: sdc set ios:clk 0Hz bm PP pm UP vdd 21 width 1 timing LEGACY(SDR1
[    3.354250] sunxi-mmc 4020000.sdmmc: no vqmmc,Check if there is regulator
[    3.374404] sunxi-mmc 4020000.sdmmc: sdc set ios:clk 400000Hz bm PP pm ON vdd 21 width 1 timing LEGACY
[    3.398864] sunxi-mmc 4020000.sdmmc: detmode:gpio irq
[    3.398929] sunxi-mmc 4020000.sdmmc: sdc set ios:clk 400000Hz bm PP pm ON vdd 21 width 1 timing LEGACY
[    3.416889] sunxi-mmc 4021000.sdmmc: SD/MMC/SDIO Host Controller Driver(v4.19 2021-03-24 19:50)
[    3.426907] sunxi-mmc 4021000.sdmmc: ***ctl-spec-caps*** 8
[    3.433239] sunxi-mmc 4021000.sdmmc: No vmmc regulator found
[    3.439625] sunxi-mmc 4021000.sdmmc: No vqmmc regulator found
[    3.446162] sunxi-mmc 4021000.sdmmc: No vdmmc regulator found
[    3.452679] sunxi-mmc 4020000.sdmmc: sdc set ios:clk 400000Hz bm PP pm ON vdd 21 width 1 timing LEGACY
[    3.464325] sunxi-mmc 4021000.sdmmc: No vd33sw regulator found
[    3.470912] sunxi-mmc 4021000.sdmmc: No vd18sw regulator found
[    3.477436] sunxi-mmc 4021000.sdmmc: No vq33sw regulator found
[    3.484196] sunxi-mmc 4021000.sdmmc: No vq18sw regulator found
[    3.490898] sunxi-mmc 4021000.sdmmc: Cann't get pin bias hs pinstate,check if needed
[    3.500371] sunxi-mmc 4020000.sdmmc: sdc set ios:clk 400000Hz bm PP pm ON vdd 21 width 1 timing LEGACY
[    3.513314] sunxi-mmc 4021000.sdmmc: sdc set ios:clk 0Hz bm PP pm UP vdd 21 width 1 timing LEGACY(SDR1
[    3.524776] hub 1-1:1.0: USB hub found
[    3.529129] sunxi-mmc 4021000.sdmmc: no vqmmc,Check if there is regulator
[    3.536823] sunxi-mmc 4020000.sdmmc: sdc set ios:clk 400000Hz bm PP pm ON vdd 21 width 1 timing LEGACY
[    3.548442] hub 1-1:1.0: 4 ports detected
[    3.565522] sunxi-mmc 4021000.sdmmc: sdc set ios:clk 400000Hz bm PP pm ON vdd 21 width 1 timing LEGACY
[    3.589776] sunxi-mmc 4021000.sdmmc: detmode:manually by software
[    3.597503] sunxi-mmc 4021000.sdmmc: smc 1 p1 err, cmd 52, RTO !!
[    3.604636] sunxi_led_probe()1715 - start
[    3.609147] sunxi-mmc 4021000.sdmmc: smc 1 p1 err, cmd 52, RTO !!
[    3.616079] sunxi-mmc 4021000.sdmmc: sdc set ios:clk 400000Hz bm PP pm ON vdd 21 width 1 timing LEGACY
[    3.627809] sunxi_get_str_of_property()1560 - failed to get the string of propname led_regulator!
[    3.637968] sunxi_register_led_classdev()1448 - led_classdev start
[    3.646659] sunxi-mmc 4021000.sdmmc: sdc set ios:clk 400000Hz bm PP pm ON vdd 21 width 1 timing LEGACY
[    3.661282] mmc0: host does not support reading read-only switch, assuming write-enable
[    3.670774] sunxi_led_probe()1820 - finish
[    3.675963] usbcore: registered new interface driver usbhid
[    3.682420] usbhid: USB HID core driver
[    3.686764] sunxi-mmc 4020000.sdmmc: sdc set ios:clk 400000Hz bm PP pm ON vdd 21 width 1 timing SD-HS(
[    3.699111] sunxi-mmc 4021000.sdmmc: smc 1 p1 err, cmd 5, RTO !!
[    3.706728] sunxi-mmc 4021000.sdmmc: smc 1 p1 err, cmd 5, RTO !!
[    3.713643] sunxi-mmc 4020000.sdmmc: sdc set ios:clk 50000000Hz bm PP pm ON vdd 21 width 1 timing SD-H
[    3.725301] sunxi-mmc 4021000.sdmmc: smc 1 p1 err, cmd 5, RTO !!
[    3.732668] usbcore: registered new interface driver snd-usb-audio
[    3.739585] sunxi-mmc 4021000.sdmmc: smc 1 p1 err, cmd 5, RTO !!
[    3.746391] sunxi-mmc 4021000.sdmmc: sdc set ios:clk 0Hz bm PP pm OFF vdd 0 width 1 timing LEGACY(SDR1
[    3.757692] sunxi-mmc 4020000.sdmmc: sdc set ios:clk 50000000Hz bm PP pm ON vdd 21 width 4 timing SD-H
[    3.773217] sunxi-daudio 2034000.daudio: regulator missing or invalid
[    3.780845] mmc0: new high speed SDHC card at address aaaa
[    3.787454] [AUDIOCODEC][sunxi_codec_parse_params][2208]:digital_vol:0, lineout_vol:26, mic1gain:31, m_pwr_level:1
[    3.787454] 
[    3.805843] mmcblk0: mmc0:aaaa SD32G 29.7 GiB 
[    3.813100] [AUDIOCODEC][sunxi_codec_parse_params][2244]:adcdrc_cfg:0, adchpf_cfg:0, dacdrc_cfg:0, dac
[    3.825004] [AUDIOCODEC][sunxi_internal_codec_probe][2380]:codec probe finished
[    3.835359] debugfs: Directory '203034c.dummy_cpudai' with parent 'audiocodec' already present!
[    3.845427] [SNDCODEC][sunxi_card_init][583]:card init finished
[    3.853458] GPT:Primary header thinks Alt. header is not at the end of the disk.
[    3.861817] GPT:12582911 != 62333951
[    3.865798] GPT:Alternate GPT header not at the end of the disk.
[    3.872517] GPT:12582911 != 62333951
[    3.876518] GPT: Use GNU Parted to correct GPT errors.
[    3.882321]  mmcblk0: p1 p2 p3
[    3.887881] sunxi-codec-machine 2030340.sound: 2030000.codec <-> 203034c.dummy_cpudai mapping ok
[    3.899247] input: audiocodec sunxi Audio Jack as /devices/platform/soc@3000000/2030340.sound/sound/ca
[    3.911370] [SNDCODEC][sunxi_card_dev_probe][832]:register card finished
[    3.920555] NET: Registered protocol family 10
[    3.927146] Segment Routing with IPv6
[    3.931526] sit: IPv6, IPv4 and MPLS over IPv4 tunneling driver
[    3.938924] NET: Registered protocol family 17
[    3.943985] can: controller area network core (rev 20170425 abi 9)
[    3.951032] NET: Registered protocol family 29
[    3.956024] can: raw protocol (rev 20170425)
[    3.960823] can: broadcast manager protocol (rev 20170425 t)
[    3.967153] can: netlink gateway (rev 20190810) max_hops=1
[    3.973650] Bluetooth: RFCOMM TTY layer initialized
[    3.979105] Bluetooth: RFCOMM socket layer initialized
[    3.984968] Bluetooth: RFCOMM ver 1.11
[    3.990198] Loading compiled-in X.509 certificates
[    3.997929] HDMI 2.0 driver init start!
[    4.002296] boot_hdmi=false
[    4.005494] ERROR: pinctrl_get for HDMI2.0 DDC fail
[    4.012545] HDMI2.0 module init end
[    4.042307] twi twi2: twi2 supply twi not found, using dummy regulator
[    4.057509] pcf857x 2-0038: probed
[    4.067673] sunxi_i2c_probe()2262 - [i2c2] probe success
[    4.083624] debugfs: Directory '2031000.dmic' with parent 'snddmic' already present!
[    4.094340] sunxi-audio-card 2031060.sounddmic: snd-soc-dummy-dai <-> 2031000.dmic mapping ok
[    4.105266] debugfs: Directory '2034000.daudio' with parent 'sndhdmi' already present!
[    4.115882] sunxi-audio-card 20340a0.sounddaudio2: snd-soc-dummy-dai <-> 2034000.daudio mapping ok
[    4.127601] get ehci0-controller wakeup-source is fail.
[    4.133630] sunxi ehci0-controller don't init wakeup source
[    4.139850] [sunxi-ehci0]: probe, pdev->name: 4101000.ehci0-controller, sunxi_ehci: 0xffffffe0008d6388
[    4.153415] [sunxi-ehci0]: Not init ehci0
[    4.158375] get ohci0-controller wakeup-source is fail.
[    4.164360] sunxi ohci0-controller don't init wakeup source
[    4.170668] [sunxi-ohci0]: probe, pdev->name: 4101400.ohci0-controller, sunxi_ohci: 0xffffffe0008d6ec8
[    4.181074] [sunxi-ohci0]: Not init ohci0
[    4.186774] ubi0: attaching mtd3
[    4.350676] usb 1-1.4: new full-speed USB device number 3 using sunxi-ehci
[    4.558928] input: Logitech USB Receiver as /devices/platform/soc@3000000/4200000.ehci1-controller/usb1/input/input2
[    4.641759] hid-generic 0003:046D:C52E.0001: input: USB HID v1.11 Keyboard [Logitech USB Receiver] on 
[    4.669180] input: Logitech USB Receiver Mouse as /devices/platform/soc@3000000/4200000.ehci1-controll2E.0002/input/input3
[    4.689757] input: Logitech USB Receiver Consumer Control as /devices/platform/soc@3000000/4200000.ehc003:046D:C52E.0002/input/input4
[    4.771112] input: Logitech USB Receiver System Control as /devices/platform/soc@3000000/4200000.ehci13:046D:C52E.0002/input/input5
[    4.792213] hid-generic 0003:046D:C52E.0002: input: USB HID v1.11 Mouse [Logitech USB Receiver] on usb
[    5.263497] ubi0: scanning is finished
[    5.283348] ubi0: attached mtd3 (name "sys", size 250 MiB)
[    5.289500] ubi0: PEB size: 262144 bytes (256 KiB), LEB size: 258048 bytes
[    5.297206] ubi0: min./max. I/O unit sizes: 4096/4096, sub-page size 2048
[    5.304848] ubi0: VID header offset: 2048 (aligned 2048), data offset: 4096
[    5.312634] ubi0: good PEBs: 1000, bad PEBs: 0, corrupted PEBs: 0
[    5.319468] ubi0: user volume: 9, internal volumes: 1, max. volumes count: 128
[    5.327562] ubi0: max/mean erase counter: 2/1, WL threshold: 4096, image sequence number: 0
[    5.336937] ubi0: available PEBs: 16, total reserved PEBs: 984, PEBs reserved for bad PEB handling: 20
[    5.347363] ubi0: background thread "ubi_bgt0d" started, PID 72
[    5.356077] block ubiblock0_5: created from ubi0:5(rootfs)
[    5.364562] cfg80211: Loading compiled-in X.509 certificates for regulatory database
[    5.375568] cfg80211: Loaded X.509 cert 'sforshee: 00b28ddf47aef9cea7'
[    5.383179] platform regulatory.0: Direct firmware load for regulatory.db failed with error -2
[    5.392906] clk: Not disabling unused clocks
[    5.397671] ALSA device list:
[    5.401108] cfg80211: failed to load regulatory.db
[    5.406530]   #0: audiocodec
[    5.409741]   #1: snddmic
[    5.412743]   #2: sndhdmi
[    5.415672] alloc_fd: slot 0 not NULL!
[    5.424454] VFS: Mounted root (squashfs filesystem) readonly on device 254:0.
[    5.436133] devtmpfs: mounted
[    5.439638] Freeing unused kernel memory: 208K
[    5.444684] This architecture does not have kernel memory protection.
[    5.451979] Run /sbin/init as init process
[    6.341832] init: Console is alive
[    6.345927] init: - watchdog -
[    6.349485] init: - preinit -
/dev/by-name/UDISK already format by ubifs
[    7.732477] mount_root: mounting /dev/root
[    7.737594] mount_root: loading kmods from internal overlay
[    7.810676] hdmi_hpd_sys_config_release
[    8.026407] block: attempting to load /etc/config/fstab
[    8.071883] UBIFS (ubi0:8): Mounting in unauthenticated mode
[    8.078635] UBIFS (ubi0:8): background thread "ubifs_bgt0_8" started, PID 112
[    8.210090] UBIFS (ubi0:8): recovery needed
[    8.490665] UBIFS (ubi0:8): recovery completed
[    8.495780] UBIFS (ubi0:8): UBIFS: mounted UBI device 0, volume 8, name "UDISK"
[    8.504309] UBIFS (ubi0:8): LEB size: 258048 bytes (252 KiB), min./max. I/O unit sizes: 4096 bytes/409
[    8.515983] UBIFS (ubi0:8): FS size: 192503808 bytes (183 MiB, 746 LEBs), journal size 9420800 bytes (
[    8.527916] UBIFS (ubi0:8): reserved for root: 0 bytes (0 KiB)
[    8.534475] UBIFS (ubi0:8): media format: w4/r0 (latest is w5/r0), UUID ADE7E500-29FC-4456-9FC5-0D1338
[    8.550429] block: extroot: failed to read UUID from /tmp/extroot/overlay/etc/.extroot-uuid: 17 (File 
[    8.561974] block: extroot: UUID mismatch (root: e4aac755-48e1b7c8-b32425c0-67317875, overlay: ), but 
[    8.581661] mount_root: switched to extroot
[    8.603158] procd: - early -
[    8.606576] procd: - watchdog -
[    9.003368] procd: - watchdog -
[    9.007219] procd: - ubus -
[    9.021125] procd (1): /proc/124/oom_adj is deprecated, please use /proc/124/oom_score_adj instead.
[    9.251076] procd: - init -
Please press Enter to activate this console.
[   10.120757] fuse: init (API version 7.31)
[   10.494380] get ctp_power is fail, -22
[   10.498563] get ctp_power_ldo_vol is fail, -22
[   10.540788] sunxi_ctp_startup: ctp_power_io is invalid.
[   10.546665] get ctp_gesture_wakeup fail, no gesture wakeup
[   10.580825] gt9xxnew_ts 2-0014: 2-0014 supply ctp not found, using dummy regulator
[   10.756708] file system registered
[   10.841837] configfs-gadget 4100000.udc-controller: failed to start g1: -19
[   10.871192] sunxi_i2c_do_xfer()1816 - [i2c2] incomplete xfer (status: 0x20, dev addr: 0x14)
[   10.937285] sunxi_i2c_do_xfer()1816 - [i2c2] incomplete xfer (status: 0x20, dev addr: 0x14)
[   11.020932] sunxi_i2c_do_xfer()1816 - [i2c2] incomplete xfer (status: 0x20, dev addr: 0x14)
[   11.060808] sunxi_i2c_do_xfer()1816 - [i2c2] incomplete xfer (status: 0x20, dev addr: 0x14)
[   11.104951] sunxi_i2c_do_xfer()1816 - [i2c2] incomplete xfer (status: 0x20, dev addr: 0x14)
[   11.140834] read descriptors
[   11.144058] read strings
[   11.147609] <<-GTP-ERROR->> I2C Read: 0x8047, 1 bytes failed, errcode: -70! Process reset.
[   11.340697] <<-GTP-ERROR->> GTP i2c test failed time 1.
[   11.370857] sunxi_i2c_do_xfer()1816 - [i2c2] incomplete xfer (status: 0x20, dev addr: 0x14)
[   11.387119] sunxi_i2c_do_xfer()1816 - [i2c2] incomplete xfer (status: 0x20, dev addr: 0x14)
[   11.410754] sunxi_i2c_do_xfer()1816 - [i2c2] incomplete xfer (status: 0x20, dev addr: 0x14)
[   11.430713] sunxi_i2c_do_xfer()1816 - [i2c2] incomplete xfer (status: 0x20, dev addr: 0x14)
[   11.450718] sunxi_i2c_do_xfer()1816 - [i2c2] incomplete xfer (status: 0x20, dev addr: 0x14)
[   11.460070] <<-GTP-ERROR->> I2C Read: 0x8047, 1 bytes failed, errcode: -70! Process reset.
[   11.650721] <<-GTP-ERROR->> GTP i2c test failed time 2.
[   11.680922] sunxi_i2c_do_xfer()1816 - [i2c2] incomplete xfer (status: 0x20, dev addr: 0x14)
[   11.700709] sunxi_i2c_do_xfer()1816 - [i2c2] incomplete xfer (status: 0x20, dev addr: 0x14)
[   11.720712] sunxi_i2c_do_xfer()1816 - [i2c2] incomplete xfer (status: 0x20, dev addr: 0x14)
[   11.734621] sunxi_i2c_do_xfer()1816 - [i2c2] incomplete xfer (status: 0x20, dev addr: 0x14)
[   11.758033] sunxi_i2c_do_xfer()1816 - [i2c2] incomplete xfer (status: 0x20, dev addr: 0x14)
[   11.780768] <<-GTP-ERROR->> I2C Read: 0x8047, 1 bytes failed, errcode: -70! Process reset.
[   11.940700] <<-GTP-ERROR->> GTP i2c test failed time 3.
[   11.970885] sunxi_i2c_do_xfer()1816 - [i2c2] incomplete xfer (status: 0x20, dev addr: 0x14)
[   11.987822] sunxi_i2c_do_xfer()1816 - [i2c2] incomplete xfer (status: 0x20, dev addr: 0x14)
[   12.011333] sunxi_i2c_do_xfer()1816 - [i2c2] incomplete xfer (status: 0x20, dev addr: 0x14)
[   12.030935] sunxi_i2c_do_xfer()1816 - [i2c2] incomplete xfer (status: 0x20, dev addr: 0x14)
[   12.050716] sunxi_i2c_do_xfer()1816 - [i2c2] incomplete xfer (status: 0x20, dev addr: 0x14)
[   12.060067] <<-GTP-ERROR->> I2C Read: 0x8047, 1 bytes failed, errcode: -70! Process reset.
[   12.250684] <<-GTP-ERROR->> GTP i2c test failed time 4.
[   12.280958] sunxi_i2c_do_xfer()1816 - [i2c2] incomplete xfer (status: 0x20, dev addr: 0x14)
[   12.300706] sunxi_i2c_do_xfer()1816 - [i2c2] incomplete xfer (status: 0x20, dev addr: 0x14)
[   12.320710] sunxi_i2c_do_xfer()1816 - [i2c2] incomplete xfer (status: 0x20, dev addr: 0x14)
[   12.336317] sunxi_i2c_do_xfer()1816 - [i2c2] incomplete xfer (status: 0x20, dev addr: 0x14)
[   12.359852] sunxi_i2c_do_xfer()1816 - [i2c2] incomplete xfer (status: 0x20, dev addr: 0x14)
[   12.380784] <<-GTP-ERROR->> I2C Read: 0x8047, 1 bytes failed, errcode: -70! Process reset.
[   12.540688] <<-GTP-ERROR->> GTP i2c test failed time 5.
[   12.570676] I2C communication ERROR!
[   12.570712] regulator-dummy: Underflow of regulator enable count
[   12.586135] gt9xxnew_ts: probe of 2-0014 failed with error -1
[   15.120926] ======== XRADIO WIFI OPEN ========
[   15.130723] [XRADIO] Driver Label:XR_V02.16.84_P2P_HT40_01.31   
[   15.137477] [XRADIO] Allocated hw_priv @ 0000000003fe1008
[   15.161656] sunxi-rfkill soc@3000000:rfkill@0: bus_index: 1
[   15.187664] sunxi-rfkill soc@3000000:rfkill@0: wlan power on success
[   15.610679] sunxi-mmc 4021000.sdmmc: sdc set ios:clk 0Hz bm PP pm UP vdd 21 width 1 timing LEGACY(SDR1
[   15.621833] [XRADIO] Detect SDIO card 1
[   15.630733] sunxi-mmc 4021000.sdmmc: no vqmmc,Check if there is regulator
[   15.652905] sunxi-mmc 4021000.sdmmc: sdc set ios:clk 400000Hz bm PP pm ON vdd 21 width 1 timing LEGACY
[   15.693935] sunxi-mmc 4021000.sdmmc: sdc set ios:clk 400000Hz bm PP pm ON vdd 21 width 1 timing LEGACY
[   15.723691] sunxi-mmc 4021000.sdmmc: sdc set ios:clk 400000Hz bm PP pm ON vdd 21 width 1 timing LEGACY
[   15.761866] sunxi-mmc 4021000.sdmmc: sdc set ios:clk 400000Hz bm PP pm ON vdd 21 width 1 timing SD-HS(
[   15.790727] sunxi-mmc 4021000.sdmmc: sdc set ios:clk 50000000Hz bm PP pm ON vdd 21 width 1 timing SD-H
[   15.810807] sunxi-mmc 4021000.sdmmc: sdc set ios:clk 50000000Hz bm PP pm ON vdd 21 width 4 timing SD-H
[   15.841882] mmc1: new high speed SDIO card at address 0001
[   15.861287] [SBUS] XRadio Device:sdio clk=50000000
[   15.880749] [XRADIO] XRADIO_HW_REV 1.0 detected.
[   16.051290] [XRADIO] xradio_update_dpllctrl: DPLL_CTRL Sync=0x00c00000.
[   16.202519] [XRADIO] Bootloader complete
[   16.400813] [XRADIO] Firmware completed.
[   16.412134] [WSM] Firmware Label:XR_C09.08.52.64_DBG_02.100 2GHZ HT40 Jan  3 2020 13:14:37
[   16.440719] [XRADIO] Firmware Startup Done.
[   16.451126] [XRADIO_WRN] enable Multi-Rx!
[   16.463234] ieee80211 phy0: Selected rate control algorithm 'minstrel_ht'
[   16.520919] Error: Driver 'gt9xxnew_ts' is already registered, aborting...
[   17.262253] ieee80211_do_open: vif_type=2, p2p=0, ch=3, addr=24:e7:ec:f2:03:2f
[   17.270386] [STA] !!!xradio_vif_setup: id=0, type=2, p2p=0, addr=24:e7:ec:f2:03:2f
[   17.336075] [AP_WRN] BSS_CHANGED_ASSOC but driver is unjoined.
Trying to connect to SWUpdate...
[   22.970664] HDMI cable is connected
[   23.950877] error: invalid cea_vic code:0
[   23.955349] [HDMI2 error]: sink do not support this mode:0
[   24.600657] HDMI cable is disconnected
[   25.290664] HDMI cable is connected
[   26.270871] error: invalid cea_vic code:0
[   26.275367] [HDMI2 error]: sink do not support this mode:0
[   35.680669] usb1-vbus: disabling
[  645.400646] HDMI cable is disconnected
[  648.970652] HDMI cable is connected
[  649.870864] error: invalid cea_vic code:0
[  649.875473] [HDMI2 error]: sink do not support this mode:0
[  668.690644] HDMI cable is disconnected
[  672.260646] HDMI cable is connected
[  673.160861] error: invalid cea_vic code:0
[  673.165498] [HDMI2 error]: sink do not support this 
```
