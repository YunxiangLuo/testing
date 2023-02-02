# munge 使用说明

## 1. 创建授权密钥

1. 执行以下命令，创建授权密钥；

```
$ sudo mungekey --verbose
```

2. 显示如下信息，表示创建成功。

```
mungekey: Info: Created "/opt/etc/munge/munge.key" with 1024-bit key
```

## 2. 启动 munge 后台服务

执行以下命令，启动 munge 后台服务。

```
$ sudo mkdir -p /run/munge && sudo munged
```

## 3. 对凭据进行编码

1. 执行以下命令，对凭据进行编码；

```
$ munge -n
```

2. 显示如下信息，表示编码成功。此命令可测试 munge 可执行文件和 libmunge 库是否存在，munged 是否正在运行，以及客户端（munge 或 libmunge）是否可以与服务器（munged）通信。

```
MUNGE:AwQFAACsSBOF7ALp7dlTVlgyJSyP+5FCoBnYH4L7/pWcT2RDadFe9VN3FjdYVwWpgFky6gjb6rLlUFmrRAYgbCkVegE6VOrHp0IiDISahhN7mJQv9dNhHmaiyUMRNIMzl/FivbI=:
```

## 4. 对凭据进行解码

1. 执行以下命令，对凭据进行解码；

```
munge -n | unmunge
```

2. 显示如下信息，表示解码成功。此命令可测试编码与解码是否成功，并显示已经编码的凭据的原始数据。

```
STATUS:          Success (0)
ENCODE_HOST:     openEuler-PC (127.0.1.1)
ENCODE_TIME:     2023-02-02 22:14:25 +0800 (1675347265)
DECODE_TIME:     2023-02-02 22:14:25 +0800 (1675347265)
TTL:             300
CIPHER:          aes128 (4)
MAC:             sha256 (5)
ZIP:             none (0)
UID:             openEuler (1000)
GID:             openEuler (1000)
LENGTH:          0
```

## 5. 停止 munge 后台服务

执行以下命令，停止 munge 后台服务。

```
$ sudo killall munged
```
