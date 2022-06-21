# Firefox安装说明

## 1. 编译支持视频输出的QEMU

### 1.1 Ubuntu 20.04及其以下版本
参考[Xfce安装说明](../Xfce/Xfce_installation_guide.md)

#### 1.2Ubuntu 22.04直接使用apt安装qemu

## 2. 系统镜像的使用

### 2.1 镜像下载

#### 2.1.1 下载内容

- 下载 QEMU 目录下的 `openeuler-qemu-xfce.raw.tar.zst`、`fw_payload_oe_qemuvirt.elf` 和 `start_vm_xfce.sh`
- 下载地址 [https://mirror.iscas.ac.cn/openeuler-sig-riscv/openEuler-RISC-V/testing/20220621/v0.1/QEMU/](https://mirror.iscas.ac.cn/openeuler-sig-riscv/openEuler-RISC-V/testing/20220621/v0.1/QEMU/)
或
https://repo.tarsier-infra.com/openEuler-RISC-V/testing/20220621/v0.1/QEMU/

#### 2.1.2 启动

- 运行 `bash start_vm_xfce.sh`
- 通过 VNC 打开图形界面（以 TigerVNC 为例，本地地址localhost） `vncviewer :5900`

### 2.2 环境安装详细步骤

- 解压 tar.zst 格式的镜像文件

```bash
tar -I `zstdmt` -xvf ./openeuler-qemu-xfce.raw.tar.zst
```

- 执行 `ps -p $$`，确认 CMD 栏下方对应着 `bash`, `zsh` 或其他 bash 兼容 shell

- 执行 `bash start_vm_xfce.sh`，并查看 `ssh port` 的返回结果

- 执行 `ssh -p {insert your ssh port here} root@localhost`，如 `ssh -p 10255 root@localhost`

- 本地安装vnc客户端，访问IP地址localhost，端口5900

- 输入密码完成登录，默认的用户名和密码为 `root` 和 `openEuler1234`

## 3. 安装Firefox

### 3.1 安装Firefox

- 执行下列指令

```bash
dnf install firefox
```

- 安装过程中，有些包可能会已经以依赖的形式被安装了，没关系直接跳过。

### 3.2 启动Firefox

- Xfce桌面下打开终端，输入`firefox` 启动 Firefox。

```shell
firefox
```

- 点击Firefox图标启动Firefox

root 默认密码为 openEuler12#$

![figure_1](./images/figure_1.png)
