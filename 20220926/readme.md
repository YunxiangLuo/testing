# 操作系统镜像和软件源要求

## 提交测试截至时间：20220922（本周四）上午10点

## 缺陷修改截至时间：20220926（下周一）上午10点

## 提交规则：[ORSP004](https://gitee.com/openeuler/RISC-V/blob/master/proposal/ORSP004.md)

## 责任人：周嘉成

## 镜像和软件源要求：

### Unmatched开发板

- [x] 1. 应可以正常启动
- [x] 2. 应自动支持wifi
- [x] 3. 应自带xfce，功能正常（终端、截屏、显示设置等）
- [x] 4. 应可以成功安装和卸载Firefox、LibreOffice、vlc（已可以）、GIMP（已可以）
- [x] 5. Firefox、LibreOffice、vlc、GIMP可正常启动，基本功能正常
- [x] 6. 支持存储空间扩容，提供扩容说明文档和命令
- [x] 7. 提供刷机镜像文件（可直接下载）

如2. 应自动支持wifi无法满足，应提供自带支持的wifi网卡列表，对常见wifi网卡（Intel）提供驱动安装资源和安装文档

如2. 应自动支持wifi无法满足，应镜像预装Xfce、Firefox、LibreOffice、vlc、GIMP、vim、terminal、Thunderbird等软件

如6. 支持存储空间扩容无法满足，应镜像预装Xfce、Firefox、LibreOffice、vlc、GIMP、vim、terminal、Thunderbird等软件

### QEMU

- [x] 1. 应可以正常启动
- [x] 2. 声卡支持
- [x] 3. 应自带xfce，功能正常（终端、截屏、显示设置等）
- [x] 4. 应可以成功安装和卸载Firefox、LibreOffice、GIMP
- [x] 5. Firefox、LibreOffice可正常启动，基本功能正常
- [x] 6. 提供安装文件和启动脚本（可直接下载）

### Nice to have
1. 此次交付用户的QEMU 镜像预装Xfce、Firefox、LibreOffice、vlc、GIMP、vim、terminal、Thunderbird等常用软件
2. 提供其它列表上的软件，可正常安装、卸载、启动和基本功能正常（不需要手工配置）
3. 按照Unmatched的要求，支持Vision five和D1
