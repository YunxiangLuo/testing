# 操作系统镜像和软件源要求

## 提交测试截至时间：20220922（本周四）上午10点

## 缺陷修改截至时间：20220926（下周一）上午10点

## 提交规则：[ORSP004](https://gitee.com/openeuler/RISC-V/blob/master/proposal/ORSP004.md)

## 责任人：周嘉成

## Bug分级

P1 / blocking 指阻塞性bug修复之前什么都不能干。例如用户数据丢失可能列为P1

P2 / important 指用户几乎总会遇到并影响使用，例如常用用例中程序崩溃、关键功能无法使用等

P3 / normal 指用户经常遇到并且影响使用体验的bug

P4 / improvement 不紧急的bug

P5 / wishlist


## 镜像和软件源要求：

### Unmatched开发板

> 计划9月26日星期一收到提交测试的镜像和软件源

- [ ] 1. 应可以正常启动(p1)
- [ ] 2. 应自动支持wifi(p2)
- [ ] 3. 应自带xfce，功能正常（终端、截屏、显示设置等）(p2)
- [ ] 4. 应可以成功安装和卸载Firefox、LibreOffice、vlc（已可以）、GIMP（已可以）(p2)
- [ ] 5. Firefox、LibreOffice、vlc、GIMP可正常启动，基本功能正常(p2)
- [ ] 6. 支持存储空间扩容，提供扩容说明文档和命令(p2)
- [ ] 7. 提供刷机镜像文件（可直接下载）（p1)

如2. 应自动支持wifi无法满足，<b>应提供自带支持的wifi网卡列表，对常见wifi网卡（Intel）提供驱动安装资源和安装文档</b>

如2. 应自动支持wifi无法满足，<b>应镜像预装Xfce、Firefox、LibreOffice、vlc、GIMP、vim、terminal、Thunderbird等软件</b>

如6. 支持存储空间扩容无法满足，<b>应镜像预装Xfce、Firefox、LibreOffice、vlc、GIMP、vim、terminal、Thunderbird等软件</b>

### QEMU

- [ ] 1. 应可以正常启动

> P1
> 重启黑屏，建议修改替换启动脚本

- [x] 2. 声卡支持
  
- [x] 3. 应自带xfce，功能正常（终端、截屏、显示设置等）

- [x] 4. 应可以成功安装和卸载Firefox、LibreOffice、GIMP

- [ ] 5. Firefox、LibreOffice可正常启动，基本功能正常

> P4
> eclipse can not run as root, 建议从预装软件中删除  

> p4
> failed to remove libreoffice，建议修复卸载问题

> vlc使用上游社区新代码后，性能显著改善，且修复了之前的打开视频黑屏问题，建议预装

```
[root@openEuler-riscv64 ~]# dnf remove libreoffice
Error: 
 Problem: The operation would result in removing the following protected packages: dnf
(try to add '--skip-broken' to skip uninstallable packages or '--nobest' to use not only best candidate packages)
```

- [x] 6. 提供安装文件和启动脚本（可直接下载）

### 自动化测试

> p4
> 发现有问题测试套/软件11个，建议修复，优先级中

| 测试套/软件        | 测试用例总数 | 通过 | 未通过 | 备注                                                         | 总测试套数 | 总测试用例数 |
| ------------------ | ------------ | ---- | ------ | ------------------------------------------------------------ | ---------- | ------------ |
| kubernetes         | 3            | 1    | 2      | 样例oe_test_service_kube-controller-manager在运行结束后成功但在还原环境时超时 样例oe_test_service_kube-scheduler在对应脚本26行，即上级目录中的common/common.sh中47行处tar解压失败，从而无对应目录，且rpm_manager.py的参数混乱 | 216        | 636          |
| os-basic           | 56           | 53   | 3      | 样例oe_test_power_measurement_internal对应脚本32行kill进程失败，同时nohup.out中无预期结果 样例oe_test_power_powertop_powerup中脚本32行kill识别读取出来的进程id不存在从而kill失败，同时onhup.out中同样无预期结果 样例oe_test_who中脚本23行grep后的语句无返回值，29行grep pts非对应结果 |            |              |
| p7zip              | 5            | 0    | 5      | 五个样例p7zip安装失败导致提示错误7za：command not found。    |            |              |
| pcp                | 28           | 26   | 2      | 样例oe_test_pmdumplog_02中34行pmdumplog -S @00 -T @23 $archive_data返回结果错误 样例oe_test_pmlogsummary_02中pmlogsummary -S @00 -T @23 $archive_data $metric_name运行异常 |            |              |
| rabbitmq-server    | 2            | 1    | 1      | 样例oe_test_service_rabbitmq-server中rabbitmq-server.service服务stop,reload均失败 对应../common/common_lib.sh中42行与90行 |            |              |
| atune              | 1            | 0    | 1      | 对应testcases/cli-test/atune/oe_test_service_atune-engine.sh，未找到atune配置文件，且无atune-engine.service，atune-engine安装有问题 |            |              |
| clamav             | 11           | 9    | 2      | cli-test/clamav/oe_test_clamav_clamav-milter.sh运行超时，可能发生在后处理（post_test()）或配置功能测试处 cli-test/clamav/oe_test_clamav_sigtool_2.sh：未找到/var/lib/clamav/bytecode.cvd，可能为clamav安装有问题或收到前出错测试例影响 |            |              |
| djvulibre          | 5            | 3    | 2      | cli-test/djvulibre/oe_test_djvulibre_01.sh: 50/55/58行出错 cli-test/djvulibre/oe_test_djvulibre_02.sh:38行和52至90行出错 |            |              |
| easymock           | 11           | 9    | 2      | cli-test/easymock/oe_test_easymock_junit4: mvn自带测试运行出错 cli-test/easymock/oe_test_easymock_junit5: 测试运行超时 |            |              |
| freeradius         | 7            | 3    | 4      | cli-test/freeradius/oe_test_freeradius_freeradius-utils_rad_counter: 无/etc/raddb/mods-enabled/counter和rad_counter命令疑似freeradius-utils安装或软件源问题 cli-test/freeradius/oe_test_freeradius_freeradius-utils_radclient:无radiusd.service和radclient，疑似安装或软件源问题 cli-test/freeradius/oe_test_freeradius_freeradius-utils_radcryptAndRadeapclient:同缺失文件或命令，疑似安装或软件源问题 cli-test/freeradius/oe_test_freeradius_freeradius-utils_radlastAndRadsniff:同缺失文件或命令，疑似安装或软件源问题 |            |              |
| java-1.8.0-openjdk | 8            | 7    | 1      | cli-test/java-1.8.0-openjdk/oe_test_openjdk_rmic_rmid.sh: 36行处 “rmid -stop -port 1111”出错 |            |              |
| abrt               | 1            | 1    | 0      |                                                              |            |              |
| accountsservice    | 1            | 1    | 0      |                                                              |            |              |
| acl                | 8            | 8    | 0      |                                                              |            |              |
| acpid              | 5            | 5    | 0      |                                                              |            |              |
| alsa-utils         | 1            | 1    | 0      |                                                              |            |              |
| amanda             | 4            | 4    | 0      |                                                              |            |              |
| anaconda           | 8            | 8    | 0      |                                                              |            |              |
| arpwatch           | 1            | 1    | 0      |                                                              |            |              |
| at                 | 1            | 1    | 0      |                                                              |            |              |
| attr               | 1            | 1    | 0      |                                                              |            |              |
| audit              | 1            | 1    | 0      |                                                              |            |              |
| authd              | 1            | 1    | 0      |                                                              |            |              |
| authz              | 1            | 1    | 0      |                                                              |            |              |
| avahi              | 3            | 3    | 0      |                                                              |            |              |
| bcrypt             | 1            | 1    | 0      |                                                              |            |              |
| bind               | 1            | 1    | 0      |                                                              |            |              |
| bolt               | 1            | 1    | 0      |                                                              |            |              |
| brltty             | 1            | 1    | 0      |                                                              |            |              |
| byacc              | 4            | 4    | 0      |                                                              |            |              |
| ceph               | 9            | 9    | 0      |                                                              |            |              |
| clang              | 3            | 3    | 0      |                                                              |            |              |
| clevis             | 1            | 1    | 0      |                                                              |            |              |
| cloud-init         | 6            | 6    | 0      |                                                              |            |              |
| cmake              | 6            | 6    | 0      |                                                              |            |              |
| cockpit            | 1            | 1    | 0      |                                                              |            |              |
| colm               | 1            | 1    | 0      |                                                              |            |              |
| cpio               | 1            | 1    | 0      |                                                              |            |              |
| cppcheck           | 1            | 1    | 0      |                                                              |            |              |
| cracklib           | 1            | 1    | 0      |                                                              |            |              |
| cronie             | 2            | 2    | 0      |                                                              |            |              |
| cups-filters       | 1            | 1    | 0      |                                                              |            |              |
| cups               | 2            | 2    | 0      |                                                              |            |              |
| cvs                | 2            | 2    | 0      |                                                              |            |              |
| cyrus-sasl         | 1            | 1    | 0      |                                                              |            |              |
| dbus               | 2            | 2    | 0      |                                                              |            |              |
| digest-list-tools  | 1            | 1    | 0      |                                                              |            |              |
| dkms               | 1            | 1    | 0      |                                                              |            |              |
| dnf                | 8            | 8    | 0      |                                                              |            |              |
| dnsmasq            | 1            | 1    | 0      |                                                              |            |              |
| dnssec-trigger     | 1            | 1    | 0      |                                                              |            |              |
| dos2unix           | 1            | 1    | 0      |                                                              |            |              |
| dovecot            | 1            | 1    | 0      |                                                              |            |              |
| dracut             | 7            | 7    | 0      |                                                              |            |              |
| e2fsprogs          | 2            | 2    | 0      |                                                              |            |              |
| erlang             | 2            | 2    | 0      |                                                              |            |              |
| fcgi               | 1            | 1    | 0      |                                                              |            |              |
| firebird           | 1            | 1    | 0      |                                                              |            |              |
| firewalld          | 3            | 3    | 0      |                                                              |            |              |
| flatpak            | 1            | 1    | 0      |                                                              |            |              |
| fprintd            | 1            | 1    | 0      |                                                              |            |              |
| galera             | 1            | 1    | 0      |                                                              |            |              |
| ganglia            | 1            | 1    | 0      |                                                              |            |              |
| geoclue2           | 1            | 1    | 0      |                                                              |            |              |
| geos               | 1            | 1    | 0      |                                                              |            |              |
| git                | 1            | 1    | 0      |                                                              |            |              |
| glibc              | 2            | 2    | 0      |                                                              |            |              |
| gpm                | 1            | 1    | 0      |                                                              |            |              |
| grub2              | 1            | 1    | 0      |                                                              |            |              |
| gssproxy           | 1            | 1    | 0      |                                                              |            |              |
| haproxy            | 1            | 1    | 0      |                                                              |            |              |
| haveged            | 1            | 1    | 0      |                                                              |            |              |
| help2man           | 1            | 1    | 0      |                                                              |            |              |
| hsqldb             | 1            | 1    | 0      |                                                              |            |              |
| htop               | 1            | 1    | 0      |                                                              |            |              |
| httpd              | 1            | 1    | 0      |                                                              |            |              |
| ImageMagick        | 8            | 8    | 0      |                                                              |            |              |
| initial-setup      | 1            | 1    | 0      |                                                              |            |              |
| initscripts        | 2            | 2    | 0      |                                                              |            |              |
| iperf3             | 1            | 1    | 0      |                                                              |            |              |
| iputils            | 1            | 1    | 0      |                                                              |            |              |
| ipwatchd           | 1            | 1    | 0      |                                                              |            |              |
| javapackages-tools | 5            | 5    | 0      |                                                              |            |              |
| jemalloc           | 2            | 2    | 0      |                                                              |            |              |
| jq                 | 1            | 1    | 0      |                                                              |            |              |
| junit5             | 12           | 12   | 0      |                                                              |            |              |
| kernel             | 2            | 2    | 0      |                                                              |            |              |
| keyutils           | 1            | 1    | 0      |                                                              |            |              |
| krb5               | 2            | 2    | 0      |                                                              |            |              |
| libcanberra        | 3            | 3    | 0      |                                                              |            |              |
| libcap             | 9            | 9    | 0      |                                                              |            |              |
| libcgroup          | 1            | 1    | 0      |                                                              |            |              |
| libmemcached       | 12           | 12   | 0      |                                                              |            |              |
| libosinfo          | 2            | 2    | 0      |                                                              |            |              |
| libreswan          | 2            | 2    | 0      |                                                              |            |              |
| libstoragemgmt     | 1            | 1    | 0      |                                                              |            |              |
| libwbxml           | 2            | 2    | 0      |                                                              |            |              |
| libzip             | 3            | 3    | 0      |                                                              |            |              |
| lldpad             | 1            | 1    | 0      |                                                              |            |              |
| lm_sensors         | 1            | 1    | 0      |                                                              |            |              |
| lvm2               | 7            | 7    | 0      |                                                              |            |              |
| lxc                | 1            | 1    | 0      |                                                              |            |              |
| man-db             | 2            | 2    | 0      |                                                              |            |              |
| mdadm              | 1            | 1    | 0      |                                                              |            |              |
| memcached          | 3            | 3    | 0      |                                                              |            |              |
| mksh               | 1            | 1    | 0      |                                                              |            |              |
| mlocate            | 1            | 1    | 0      |                                                              |            |              |
| ModemManager       | 1            | 1    | 0      |                                                              |            |              |
| mt-st              | 1            | 1    | 0      |                                                              |            |              |
| multipath-tools    | 1            | 1    | 0      |                                                              |            |              |
| munge              | 1            | 1    | 0      |                                                              |            |              |
| mutt               | 1            | 1    | 0      |                                                              |            |              |
| netcf              | 1            | 1    | 0      |                                                              |            |              |
| net-tools          | 1            | 1    | 0      |                                                              |            |              |
| NetworkManager     | 4            | 4    | 0      |                                                              |            |              |
| nfs-utils          | 8            | 8    | 0      |                                                              |            |              |
| nghttp2            | 1            | 1    | 0      |                                                              |            |              |
| nginx              | 1            | 1    | 0      |                                                              |            |              |
| nodejs             | 3            | 3    | 0      |                                                              |            |              |
| nss-pam-ldapd      | 1            | 1    | 0      |                                                              |            |              |
| nss_wrapper        | 1            | 1    | 0      |                                                              |            |              |
| ntp                | 4            | 4    | 0      |                                                              |            |              |
| oddjob             | 1            | 1    | 0      |                                                              |            |              |
| opencc             | 1            | 1    | 0      |                                                              |            |              |
| opencryptoki       | 1            | 1    | 0      |                                                              |            |              |
| openhpi            | 1            | 1    | 0      |                                                              |            |              |
| open-iscsi         | 2            | 2    | 0      |                                                              |            |              |
| open-isns          | 1            | 1    | 0      |                                                              |            |              |
| openldap           | 1            | 1    | 0      |                                                              |            |              |
| openscap           | 4            | 4    | 0      |                                                              |            |              |
| openslp            | 1            | 1    | 0      |                                                              |            |              |
| opensm             | 1            | 1    | 0      |                                                              |            |              |
| opensp             | 2            | 2    | 0      |                                                              |            |              |
| openssh            | 4            | 4    | 0      |                                                              |            |              |
| openssl            | 21           | 21   | 0      |                                                              |            |              |
| openwsman          | 1            | 1    | 0      |                                                              |            |              |
| optipng            | 2            | 2    | 0      |                                                              |            |              |
| osc                | 6            | 6    | 0      |                                                              |            |              |
| ostree             | 1            | 1    | 0      |                                                              |            |              |
| pacemaker          | 1            | 1    | 0      |                                                              |            |              |
| PackageKit         | 2            | 2    | 0      |                                                              |            |              |
| pam                | 1            | 1    | 0      |                                                              |            |              |
| pcsc-lite          | 2            | 2    | 0      |                                                              |            |              |
| perl-Net-Server    | 1            | 1    | 0      |                                                              |            |              |
| pesign             | 1            | 1    | 0      |                                                              |            |              |
| php                | 8            | 8    | 0      |                                                              |            |              |
| policycoreutils    | 3            | 3    | 0      |                                                              |            |              |
| polkit             | 1            | 1    | 0      |                                                              |            |              |
| portreserve        | 1            | 1    | 0      |                                                              |            |              |
| powertop           | 1            | 1    | 0      |                                                              |            |              |
| proftpd            | 2            | 2    | 0      |                                                              |            |              |
| python-blivet      | 1            | 1    | 0      |                                                              |            |              |
| python-keyring     | 1            | 1    | 0      |                                                              |            |              |
| python-wheel       | 1            | 1    | 0      |                                                              |            |              |
| qt5-qttools        | 9            | 9    | 0      |                                                              |            |              |
| quota              | 1            | 1    | 0      |                                                              |            |              |
| rdate              | 1            | 1    | 0      |                                                              |            |              |
| rdma-core          | 1            | 1    | 0      |                                                              |            |              |
| realmd             | 1            | 1    | 0      |                                                              |            |              |
| redis5             | 3            | 3    | 0      |                                                              |            |              |
| redis6             | 3            | 3    | 0      |                                                              |            |              |
| redis              | 3            | 3    | 0      |                                                              |            |              |
| resource-agents    | 1            | 1    | 0      |                                                              |            |              |
| rpcbind            | 2            | 2    | 0      |                                                              |            |              |
| rpmdevtools        | 2            | 2    | 0      |                                                              |            |              |
| rpmlint            | 2            | 2    | 0      |                                                              |            |              |
| rrdtool            | 2            | 2    | 0      |                                                              |            |              |
| rsync              | 2            | 2    | 0      |                                                              |            |              |
| rsyslog            | 1            | 1    | 0      |                                                              |            |              |
| rtkit              | 1            | 1    | 0      |                                                              |            |              |
| rubygem-bundler    | 13           | 13   | 0      |                                                              |            |              |
| ruby               | 8            | 8    | 0      |                                                              |            |              |
| sane-backends      | 1            | 1    | 0      |                                                              |            |              |
| sanlock            | 1            | 1    | 0      |                                                              |            |              |
| sblim-sfcb         | 1            | 1    | 0      |                                                              |            |              |
| scsi-target-utils  | 1            | 1    | 0      |                                                              |            |              |
| sendmail           | 2            | 2    | 0      |                                                              |            |              |
| smartmontools      | 1            | 1    | 0      |                                                              |            |              |
| spice-vdagent      | 2            | 2    | 0      |                                                              |            |              |
| sqlite-jdbc        | 1            | 1    | 0      |                                                              |            |              |
| sqlite             | 17           | 17   | 0      |                                                              |            |              |
| sssd               | 2            | 2    | 0      |                                                              |            |              |
| stunnel            | 1            | 1    | 0      |                                                              |            |              |
| swig               | 10           | 10   | 0      |                                                              |            |              |
| switcheroo-control | 1            | 1    | 0      |                                                              |            |              |
| sysprof            | 2            | 2    | 0      |                                                              |            |              |
| sysstat            | 3            | 3    | 0      |                                                              |            |              |
| systemtap          | 2            | 2    | 0      |                                                              |            |              |
| tang               | 3            | 3    | 0      |                                                              |            |              |
| tcllib             | 3            | 3    | 0      |                                                              |            |              |
| telnet             | 1            | 1    | 0      |                                                              |            |              |
| tftp               | 2            | 2    | 0      |                                                              |            |              |
| tidy               | 16           | 16   | 0      |                                                              |            |              |
| tigervnc           | 1            | 1    | 0      |                                                              |            |              |
| timedatex          | 1            | 1    | 0      |                                                              |            |              |
| tomcat             | 2            | 2    | 0      |                                                              |            |              |
| udisks2            | 1            | 1    | 0      |                                                              |            |              |
| umoci              | 1            | 1    | 0      |                                                              |            |              |
| unbound            | 2            | 2    | 0      |                                                              |            |              |
| upower             | 1            | 1    | 0      |                                                              |            |              |
| usbmuxd            | 1            | 1    | 0      |                                                              |            |              |
| util-linux         | 3            | 3    | 0      |                                                              |            |              |
| uuid               | 2            | 2    | 0      |                                                              |            |              |
| varnish            | 2            | 2    | 0      |                                                              |            |              |
| vsftpd             | 2            | 2    | 0      |                                                              |            |              |
| watchdog           | 3            | 3    | 0      |                                                              |            |              |
| wireshark          | 2            | 2    | 0      |                                                              |            |              |
| x265               | 1            | 1    | 0      |                                                              |            |              |
| xdelta             | 3            | 3    | 0      |                                                              |            |              |
| xfsprogs           | 1            | 1    | 0      |                                                              |            |              |
| xinetd             | 1            | 1    | 0      |                                                              |            |              |
| xmltoman           | 1            | 1    | 0      |                                                              |            |              |
| ypbind             | 1            | 1    | 0      |                                                              |            |              |
| ypserv             | 3            | 3    | 0      |                                                              |            |              |
| zerofree           | 1            | 1    | 0      |                                                              |            |              |
| zvbi               | 1            | 1    | 0      |                                                              |            |              |

### Nice to have
1. 此次交付用户的QEMU 镜像预装Xfce、Firefox、LibreOffice、vlc、GIMP、vim、terminal、Thunderbird等常用软件
2. 提供其它列表上的软件，可正常安装、卸载、启动和基本功能正常（不需要手工配置）
3. 按照Unmatched的要求，支持Vision five和D1
