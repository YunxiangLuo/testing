# Thunderbird安装说明

## 1. 编译支持视频输出的QEMU

Ubuntu 22.04可直接安装`sudo apt install qemu`

Ubuntu 20.04及其以下版本

参考[Xfce安装说明](../../Xfce/Xfce_installation_guide.md)

## 2. 系统镜像的使用

### 2.1 镜像下载

- 在此次测试中我们选取 2022xxxx 生成的 vx.x 版 QEMU 镜像进行测试。

- 请到镜像源下载 `fw_payload_oe_qemuvirt.elf`，`openeuler-qemu.raw.tar.zst` 与 `start_vm.sh` 三个文件，并将其放置在同一个文件夹内，保证目录中没有中文。

- [点此直达下载文件夹]()

### 2.2 环境安装

- 解压 tar.zst 格式的镜像文件

```bash
tar -I `zstdmt` -xvf ./openeuler-qemu.raw.tar.zst
```

- 执行 `ps -p $$`，确认 CMD 栏下方对应着 `bash`, `zsh` 或其他 bash 兼容 shell

- 执行 `bash start_vm.sh`，并查看 `ssh port` 的返回结果

- 执行 `ssh -p {insert your ssh port here} root@localhost`，如 `ssh -p 10255 root@localhost`

- 输入密码完成登录，默认的用户名和密码为 `root` 和 `openEuler1234`

## 3. 安装Thunderbird

### 3.1 安装Thunderbird

- 执行下列指令

```bash
yum install alsa-lib-devel dbus-glib desktop-file-utils pciutils mesa* thunderbird -y
```

- 安装过程中，有些包可能会已经以依赖的形式被安装了，没关系直接跳过。

### 3.2 启动Thunderbird

- Xfce桌面下打开终端，输入`thunderbird` 启动 Thunderbird。

```shell
thunderbird
```

- 点击Thunderbird图标启动Thunderbird

root 默认密码为 openEuler12#$
