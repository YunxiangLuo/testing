# Thunderbird 测试指引

## 下载内容

- 下载 QEMU 目录下的 `openeuler-qemu-xfce.raw.tar.zst`、`fw_payload_oe_qemuvirt.elf` 和 `start_vm_xfce.sh`
- 下载地址 `https://mirror.iscas.ac.cn/openeuler-sig-riscv/openEuler-RISC-V/testing/20220621/v0.1/`

## 启动

- 运行脚本

     `bash start_vm_xfce.sh`
- 等待图形界面加载完成

## 安装 thunderbird

- 使用包管理器直接安装 

     `dnf install thunderbird`

## 已知问题

### 预设配置

- 声音可能不工作，启动报错如下

    - 相关日志：
        ```bash
        pulseaudio: set_sink_input_volume() failed
        pulseaudio: Reason: Invalid argument
        pulseaudio: set_sink_input_mute() failed
        pulseaudio: Reason: Invalid argument
        ```

    - 如何绕过：暂无解决方案

### 潜在问题
> 预设配置下不会发生

- 使用带 openGL 的配置重新启动系统并登录后可能出现黑屏

    - 复现条件：使用 `virtio-gpu-gl` / `virtio-vga-gl` 两种虚拟显卡，显示配置增加 `gl=on`，正常登录后重新启动

    - 相关日志：排查中

    - 如何绕过：暂无解决方案


## 权责信息

- thunderbird 目前由 firefox port maintainer [@Jingwiw](https://gitee.com/Jingwiw) 负责维护
- CI maintainer: [@jchzhou](https://gitee.com/jchzhou)
