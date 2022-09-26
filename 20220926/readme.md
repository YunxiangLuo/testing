# 操作系统镜像和软件源要求

## 提交测试截至时间：20220922（本周四）上午10点

## 缺陷修改截至时间：20220926（下周一）上午10点

## 提交规则：[ORSP004](https://gitee.com/openeuler/RISC-V/blob/master/proposal/ORSP004.md)

## 责任人：周嘉诚

## Bug分级

P1 / blocking 指阻塞性bug修复之前什么都不能干。例如用户数据丢失可能列为P1

P2 / important 指用户几乎总会遇到并影响使用，例如常用用例中程序崩溃、关键功能无法使用等

P3 / normal 指用户经常遇到并且影响使用体验的bug

P4 / improvement 不紧急的bug

P5 / wishlist

## 镜像和软件源要求：

### Unmatched开发板

> 计划9月26日星期一收到提交测试的镜像和软件源

- [ ] 1.1 刷写到TF卡上的镜像，应可以正常启动(P1)
- [ ] 1.2 刷写到nvme卡上的镜像，应可以正常启动。同时提供安装和设置文档。(P2)
- [ ] 1.3 镜像应自动支持wifi(P2)
- [ ] 1.4（同2.3） 镜像应自带xfce，功能正常（终端、截屏、显示设置等）(P2)
- [ ] 1.5（同2.4） 镜像应可以成功安装（P3）和卸载（P4）以下软件，Firefox、LibreOffice、Chrome browser、vlc、GIMP
- [ ] 1.6（同2.5）以下软件，Firefox、LibreOffice、Chrome browser、vlc、GIMP，应可正常启动，基本功能正常(P2)
- [ ] 1.7 镜像支持存储空间扩容，提供扩容说明文档和命令(P3)
- [ ] 1.8 应提供刷机镜像文件（可直接下载）（P1)

如2. 应自动支持wifi无法满足，<b>应提供自带支持的wifi网卡列表，对常见wifi网卡（Intel）提供驱动安装资源和安装文档</b>

如2. 应自动支持wifi无法满足，<b>应镜像预装Xfce、Firefox、LibreOffice、vlc、GIMP、vim、terminal、Thunderbird等软件</b>

如6. 支持存储空间扩容无法满足，<b>应镜像预装Xfce、Firefox、LibreOffice、vlc、GIMP、vim、terminal、Thunderbird等软件</b>

### QEMU

- [ ] 2.1 应可以正常启动(P1)

> 重启黑屏，建议修改替换启动脚本

- [x] 2.2 声卡支持(P2)
  
- [x] 2.3 镜像应自带xfce，功能正常（终端、截屏、显示设置等）(P2)

- [x] 2.4 镜像应可以成功安装（P3）和卸载（P4）以下软件，Firefox、LibreOffice、Chrome browser、vlc、GIMP

- [ ] 2.5 以下软件，Firefox、LibreOffice、Chrome browser、vlc、GIMP，应可正常启动，基本功能正常(P2)

> eclipse can not run as root, 建议从预装软件中删除  

> failed to remove libreoffice，建议修复卸载问题

```
[root@openEuler-riscv64 ~]# dnf remove libreoffice
Error: 
 Problem: The operation would result in removing the following protected packages: dnf
(try to add '--skip-broken' to skip uninstallable packages or '--nobest' to use not only best candidate packages)
```

> vlc使用上游社区新代码后，性能显著改善，且修复了之前的打开视频黑屏问题，建议预装

- [x] 2.6 提供安装文件和启动脚本（可直接下载）(P1)

### 自动化测试

> 发现有问题测试套/软件11个，建议修复，优先级（P4）

| 序号 | 测试套/软件        | 测试用例总数 | 通过 | 未通过 | 备注                                                         |
| ---- | ------------------ | ------------ | ---- | ------ | ------------------------------------------------------------ |
| 1    | kubernetes         | 3            | 1    | 2      | 样例oe_test_service_kube-controller-manager在运行结束后成功但在还原环境时超时 样例oe_test_service_kube-scheduler在对应脚本26行，即上级目录中的common/common.sh中47行处tar解压失败，从而无对应目录，且rpm_manager.py的参数混乱 |
| 2    | os-basic           | 56           | 53   | 3      | 样例oe_test_power_measurement_internal对应脚本32行kill进程失败，同时nohup.out中无预期结果 样例oe_test_power_powertop_powerup中脚本32行kill识别读取出来的进程id不存在从而kill失败，同时onhup.out中同样无预期结果 样例oe_test_who中脚本23行grep后的语句无返回值，29行grep pts非对应结果 |
| 3    | p7zip              | 5            | 0    | 5      | 五个样例p7zip安装失败导致提示错误7za：command not found。    |
| 4    | pcp                | 28           | 26   | 2      | 样例oe_test_pmdumplog_02中34行pmdumplog -S @00 -T @23 $archive_data返回结果错误 样例oe_test_pmlogsummary_02中pmlogsummary -S @00 -T @23 $archive_data $metric_name运行异常 |
| 5    | rabbitmq-server    | 2            | 1    | 1      | 样例oe_test_service_rabbitmq-server中rabbitmq-server.service服务stop,reload均失败 对应../common/common_lib.sh中42行与90行 |
| 6    | atune              | 1            | 0    | 1      | 对应testcases/cli-test/atune/oe_test_service_atune-engine.sh，未找到atune配置文件，且无atune-engine.service，atune-engine安装有问题 |
| 7    | clamav             | 11           | 9    | 2      | cli-test/clamav/oe_test_clamav_clamav-milter.sh运行超时，可能发生在后处理（post_test()）或配置功能测试处 cli-test/clamav/oe_test_clamav_sigtool_2.sh：未找到/var/lib/clamav/bytecode.cvd，可能为clamav安装有问题或收到前出错测试例影响 |
| 8    | djvulibre          | 5            | 3    | 2      | cli-test/djvulibre/oe_test_djvulibre_01.sh: 50/55/58行出错 cli-test/djvulibre/oe_test_djvulibre_02.sh:38行和52至90行出错 |
| 9    | easymock           | 11           | 9    | 2      | cli-test/easymock/oe_test_easymock_junit4: mvn自带测试运行出错 cli-test/easymock/oe_test_easymock_junit5: 测试运行超时 |
| 10   | freeradius         | 7            | 3    | 4      | cli-test/freeradius/oe_test_freeradius_freeradius-utils_rad_counter: 无/etc/raddb/mods-enabled/counter和rad_counter命令疑似freeradius-utils安装或软件源问题 cli-test/freeradius/oe_test_freeradius_freeradius-utils_radclient:无radiusd.service和radclient，疑似安装或软件源问题 cli-test/freeradius/oe_test_freeradius_freeradius-utils_radcryptAndRadeapclient:同缺失文件或命令，疑似安装或软件源问题 cli-test/freeradius/oe_test_freeradius_freeradius-utils_radlastAndRadsniff:同缺失文件或命令，疑似安装或软件源问题 |
| 11   | java-1.8.0-openjdk | 8            | 7    | 1      | cli-test/java-1.8.0-openjdk/oe_test_openjdk_rmic_rmid.sh: 36行处 “rmid -stop -port 1111”出错 |
| 12   | abrt               | 1            | 1    | 0      |                                                              |
| 13   | accountsservice    | 1            | 1    | 0      |                                                              |
| 14   | acl                | 8            | 8    | 0      |                                                              |
| 15   | acpid              | 5            | 5    | 0      |                                                              |
| 16   | alsa-utils         | 1            | 1    | 0      |                                                              |
| 17   | amanda             | 4            | 4    | 0      |                                                              |
| 18   | anaconda           | 8            | 8    | 0      |                                                              |
| 19   | arpwatch           | 1            | 1    | 0      |                                                              |
| 20   | at                 | 1            | 1    | 0      |                                                              |
| 21   | attr               | 1            | 1    | 0      |                                                              |
| 22   | audit              | 1            | 1    | 0      |                                                              |
| 23   | authd              | 1            | 1    | 0      |                                                              |
| 24   | authz              | 1            | 1    | 0      |                                                              |
| 25   | avahi              | 3            | 3    | 0      |                                                              |
| 26   | bcrypt             | 1            | 1    | 0      |                                                              |
| 27   | bind               | 1            | 1    | 0      |                                                              |
| 28   | bolt               | 1            | 1    | 0      |                                                              |
| 29   | brltty             | 1            | 1    | 0      |                                                              |
| 30   | byacc              | 4            | 4    | 0      |                                                              |
| 31   | ceph               | 9            | 9    | 0      |                                                              |
| 32   | clang              | 3            | 3    | 0      |                                                              |
| 33   | clevis             | 1            | 1    | 0      |                                                              |
| 34   | cloud-init         | 6            | 6    | 0      |                                                              |
| 35   | cmake              | 6            | 6    | 0      |                                                              |
| 36   | cockpit            | 1            | 1    | 0      |                                                              |
| 37   | colm               | 1            | 1    | 0      |                                                              |
| 38   | cpio               | 1            | 1    | 0      |                                                              |
| 39   | cppcheck           | 1            | 1    | 0      |                                                              |
| 40   | cracklib           | 1            | 1    | 0      |                                                              |
| 41   | cronie             | 2            | 2    | 0      |                                                              |
| 42   | cups-filters       | 1            | 1    | 0      |                                                              |
| 43   | cups               | 2            | 2    | 0      |                                                              |
| 44   | cvs                | 2            | 2    | 0      |                                                              |
| 45   | cyrus-sasl         | 1            | 1    | 0      |                                                              |
| 46   | dbus               | 2            | 2    | 0      |                                                              |
| 47   | digest-list-tools  | 1            | 1    | 0      |                                                              |
| 48   | dkms               | 1            | 1    | 0      |                                                              |
| 49   | dnf                | 8            | 8    | 0      |                                                              |
| 50   | dnsmasq            | 1            | 1    | 0      |                                                              |
| 51   | dnssec-trigger     | 1            | 1    | 0      |                                                              |
| 52   | dos2unix           | 1            | 1    | 0      |                                                              |
| 53   | dovecot            | 1            | 1    | 0      |                                                              |
| 54   | dracut             | 7            | 7    | 0      |                                                              |
| 55   | e2fsprogs          | 2            | 2    | 0      |                                                              |
| 56   | erlang             | 2            | 2    | 0      |                                                              |
| 57   | fcgi               | 1            | 1    | 0      |                                                              |
| 58   | firebird           | 1            | 1    | 0      |                                                              |
| 59   | firewalld          | 3            | 3    | 0      |                                                              |
| 60   | flatpak            | 1            | 1    | 0      |                                                              |
| 61   | fprintd            | 1            | 1    | 0      |                                                              |
| 62   | galera             | 1            | 1    | 0      |                                                              |
| 63   | ganglia            | 1            | 1    | 0      |                                                              |
| 64   | geoclue2           | 1            | 1    | 0      |                                                              |
| 65   | geos               | 1            | 1    | 0      |                                                              |
| 66   | git                | 1            | 1    | 0      |                                                              |
| 67   | glibc              | 2            | 2    | 0      |                                                              |
| 68   | gpm                | 1            | 1    | 0      |                                                              |
| 69   | grub2              | 1            | 1    | 0      |                                                              |
| 70   | gssproxy           | 1            | 1    | 0      |                                                              |
| 71   | haproxy            | 1            | 1    | 0      |                                                              |
| 72   | haveged            | 1            | 1    | 0      |                                                              |
| 73   | help2man           | 1            | 1    | 0      |                                                              |
| 74   | hsqldb             | 1            | 1    | 0      |                                                              |
| 75   | htop               | 1            | 1    | 0      |                                                              |
| 76   | httpd              | 1            | 1    | 0      |                                                              |
| 77   | ImageMagick        | 8            | 8    | 0      |                                                              |
| 78   | initial-setup      | 1            | 1    | 0      |                                                              |
| 79   | initscripts        | 2            | 2    | 0      |                                                              |
| 80   | iperf3             | 1            | 1    | 0      |                                                              |
| 81   | iputils            | 1            | 1    | 0      |                                                              |
| 82   | ipwatchd           | 1            | 1    | 0      |                                                              |
| 83   | javapackages-tools | 5            | 5    | 0      |                                                              |
| 84   | jemalloc           | 2            | 2    | 0      |                                                              |
| 85   | jq                 | 1            | 1    | 0      |                                                              |
| 86   | junit5             | 12           | 12   | 0      |                                                              |
| 87   | kernel             | 2            | 2    | 0      |                                                              |
| 88   | keyutils           | 1            | 1    | 0      |                                                              |
| 89   | krb5               | 2            | 2    | 0      |                                                              |
| 90   | libcanberra        | 3            | 3    | 0      |                                                              |
| 91   | libcap             | 9            | 9    | 0      |                                                              |
| 92   | libcgroup          | 1            | 1    | 0      |                                                              |
| 93   | libmemcached       | 12           | 12   | 0      |                                                              |
| 94   | libosinfo          | 2            | 2    | 0      |                                                              |
| 95   | libreswan          | 2            | 2    | 0      |                                                              |
| 96   | libstoragemgmt     | 1            | 1    | 0      |                                                              |
| 97   | libwbxml           | 2            | 2    | 0      |                                                              |
| 98   | libzip             | 3            | 3    | 0      |                                                              |
| 99   | lldpad             | 1            | 1    | 0      |                                                              |
| 100  | lm_sensors         | 1            | 1    | 0      |                                                              |
| 101  | lvm2               | 7            | 7    | 0      |                                                              |
| 102  | lxc                | 1            | 1    | 0      |                                                              |
| 103  | man-db             | 2            | 2    | 0      |                                                              |
| 104  | mdadm              | 1            | 1    | 0      |                                                              |
| 105  | memcached          | 3            | 3    | 0      |                                                              |
| 106  | mksh               | 1            | 1    | 0      |                                                              |
| 107  | mlocate            | 1            | 1    | 0      |                                                              |
| 108  | ModemManager       | 1            | 1    | 0      |                                                              |
| 109  | mt-st              | 1            | 1    | 0      |                                                              |
| 110  | multipath-tools    | 1            | 1    | 0      |                                                              |
| 111  | munge              | 1            | 1    | 0      |                                                              |
| 112  | mutt               | 1            | 1    | 0      |                                                              |
| 113  | netcf              | 1            | 1    | 0      |                                                              |
| 114  | net-tools          | 1            | 1    | 0      |                                                              |
| 115  | NetworkManager     | 4            | 4    | 0      |                                                              |
| 116  | nfs-utils          | 8            | 8    | 0      |                                                              |
| 117  | nghttp2            | 1            | 1    | 0      |                                                              |
| 118  | nginx              | 1            | 1    | 0      |                                                              |
| 119  | nodejs             | 3            | 3    | 0      |                                                              |
| 120  | nss-pam-ldapd      | 1            | 1    | 0      |                                                              |
| 121  | nss_wrapper        | 1            | 1    | 0      |                                                              |
| 122  | ntp                | 4            | 4    | 0      |                                                              |
| 123  | oddjob             | 1            | 1    | 0      |                                                              |
| 124  | opencc             | 1            | 1    | 0      |                                                              |
| 125  | opencryptoki       | 1            | 1    | 0      |                                                              |
| 126  | openhpi            | 1            | 1    | 0      |                                                              |
| 127  | open-iscsi         | 2            | 2    | 0      |                                                              |
| 128  | open-isns          | 1            | 1    | 0      |                                                              |
| 129  | openldap           | 1            | 1    | 0      |                                                              |
| 130  | openscap           | 4            | 4    | 0      |                                                              |
| 131  | openslp            | 1            | 1    | 0      |                                                              |
| 132  | opensm             | 1            | 1    | 0      |                                                              |
| 133  | opensp             | 2            | 2    | 0      |                                                              |
| 134  | openssh            | 4            | 4    | 0      |                                                              |
| 135  | openssl            | 21           | 21   | 0      |                                                              |
| 136  | openwsman          | 1            | 1    | 0      |                                                              |
| 137  | optipng            | 2            | 2    | 0      |                                                              |
| 138  | osc                | 6            | 6    | 0      |                                                              |
| 139  | ostree             | 1            | 1    | 0      |                                                              |
| 140  | pacemaker          | 1            | 1    | 0      |                                                              |
| 141  | PackageKit         | 2            | 2    | 0      |                                                              |
| 142  | pam                | 1            | 1    | 0      |                                                              |
| 143  | pcsc-lite          | 2            | 2    | 0      |                                                              |
| 144  | perl-Net-Server    | 1            | 1    | 0      |                                                              |
| 145  | pesign             | 1            | 1    | 0      |                                                              |
| 146  | php                | 8            | 8    | 0      |                                                              |
| 147  | policycoreutils    | 3            | 3    | 0      |                                                              |
| 148  | polkit             | 1            | 1    | 0      |                                                              |
| 149  | portreserve        | 1            | 1    | 0      |                                                              |
| 150  | powertop           | 1            | 1    | 0      |                                                              |
| 151  | proftpd            | 2            | 2    | 0      |                                                              |
| 152  | python-blivet      | 1            | 1    | 0      |                                                              |
| 153  | python-keyring     | 1            | 1    | 0      |                                                              |
| 154  | python-wheel       | 1            | 1    | 0      |                                                              |
| 155  | qt5-qttools        | 9            | 9    | 0      |                                                              |
| 156  | quota              | 1            | 1    | 0      |                                                              |
| 157  | rdate              | 1            | 1    | 0      |                                                              |
| 158  | rdma-core          | 1            | 1    | 0      |                                                              |
| 159  | realmd             | 1            | 1    | 0      |                                                              |
| 160  | redis5             | 3            | 3    | 0      |                                                              |
| 161  | redis6             | 3            | 3    | 0      |                                                              |
| 162  | redis              | 3            | 3    | 0      |                                                              |
| 163  | resource-agents    | 1            | 1    | 0      |                                                              |
| 164  | rpcbind            | 2            | 2    | 0      |                                                              |
| 165  | rpmdevtools        | 2            | 2    | 0      |                                                              |
| 166  | rpmlint            | 2            | 2    | 0      |                                                              |
| 167  | rrdtool            | 2            | 2    | 0      |                                                              |
| 168  | rsync              | 2            | 2    | 0      |                                                              |
| 169  | rsyslog            | 1            | 1    | 0      |                                                              |
| 170  | rtkit              | 1            | 1    | 0      |                                                              |
| 171  | rubygem-bundler    | 13           | 13   | 0      |                                                              |
| 172  | ruby               | 8            | 8    | 0      |                                                              |
| 173  | sane-backends      | 1            | 1    | 0      |                                                              |
| 174  | sanlock            | 1            | 1    | 0      |                                                              |
| 175  | sblim-sfcb         | 1            | 1    | 0      |                                                              |
| 176  | scsi-target-utils  | 1            | 1    | 0      |                                                              |
| 177  | sendmail           | 2            | 2    | 0      |                                                              |
| 178  | smartmontools      | 1            | 1    | 0      |                                                              |
| 179  | spice-vdagent      | 2            | 2    | 0      |                                                              |
| 180  | sqlite-jdbc        | 1            | 1    | 0      |                                                              |
| 181  | sqlite             | 17           | 17   | 0      |                                                              |
| 182  | sssd               | 2            | 2    | 0      |                                                              |
| 183  | stunnel            | 1            | 1    | 0      |                                                              |
| 184  | swig               | 10           | 10   | 0      |                                                              |
| 185  | switcheroo-control | 1            | 1    | 0      |                                                              |
| 186  | sysprof            | 2            | 2    | 0      |                                                              |
| 187  | sysstat            | 3            | 3    | 0      |                                                              |
| 188  | systemtap          | 2            | 2    | 0      |                                                              |
| 189  | tang               | 3            | 3    | 0      |                                                              |
| 190  | tcllib             | 3            | 3    | 0      |                                                              |
| 191  | telnet             | 1            | 1    | 0      |                                                              |
| 192  | tftp               | 2            | 2    | 0      |                                                              |
| 193  | tidy               | 16           | 16   | 0      |                                                              |
| 194  | tigervnc           | 1            | 1    | 0      |                                                              |
| 195  | timedatex          | 1            | 1    | 0      |                                                              |
| 196  | tomcat             | 2            | 2    | 0      |                                                              |
| 197  | udisks2            | 1            | 1    | 0      |                                                              |
| 198  | umoci              | 1            | 1    | 0      |                                                              |
| 199  | unbound            | 2            | 2    | 0      |                                                              |
| 200  | upower             | 1            | 1    | 0      |                                                              |
| 201  | usbmuxd            | 1            | 1    | 0      |                                                              |
| 202  | util-linux         | 3            | 3    | 0      |                                                              |
| 203  | uuid               | 2            | 2    | 0      |                                                              |
| 204  | varnish            | 2            | 2    | 0      |                                                              |
| 205  | vsftpd             | 2            | 2    | 0      |                                                              |
| 206  | watchdog           | 3            | 3    | 0      |                                                              |
| 207  | wireshark          | 2            | 2    | 0      |                                                              |
| 208  | x265               | 1            | 1    | 0      |                                                              |
| 209  | xdelta             | 3            | 3    | 0      |                                                              |
| 210  | xfsprogs           | 1            | 1    | 0      |                                                              |
| 211  | xinetd             | 1            | 1    | 0      |                                                              |
| 212  | xmltoman           | 1            | 1    | 0      |                                                              |
| 213  | ypbind             | 1            | 1    | 0      |                                                              |
| 214  | ypserv             | 3            | 3    | 0      |                                                              |
| 215  | zerofree           | 1            | 1    | 0      |                                                              |
| 216  | zvbi               | 1            | 1    | 0      |                                                              |

### Nice to have
1. 此次交付用户的QEMU 镜像预装Xfce、Firefox、LibreOffice、vlc、GIMP、vim、terminal、Thunderbird等常用软件
2. 提供其它列表上的软件，可正常安装、卸载、启动和基本功能正常（不需要手工配置）
3. 按照Unmatched的要求，支持Vision five和D1
