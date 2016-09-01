# 基础知识

## DHCP 服务器

DHCP 服务器的作用是当你设置为自动获得 IP 地址时， 局域网中的 DHCP 服务器负责 IP 地址分配。

## 网卡名称

lo
表示回环网卡 ，表示本机，可用于验证网络协议是否正确。

eth0
表示第1块网卡，以此类推。

# IP 地址配置

## ifconfig 命令临时配置 IP

主要用来查看有效的 IP 地址信息。

输出信息含义：
| 条目 | 含义 |
| - | - |
| Link encap: Ethernet | 以太网连接类型 |
| HWaddr | mac 地址 |
| inet addr |ip 地址 |
| Bcast | 广播地址 |
| Mask | 子网掩码 |
| inet6 addr | ipv6 地址 |
| UP BROADCAST RUNNING MULTICAST | 网卡参数 |
| MTU | 网卡参数 |
| Metric | 网卡参数 |
| RX packets | 收到数据包数 |
| TX packets | 发送数据包 |

注：windows 下用 ipconfig 命令

## setup 工具永久配置 IP

只有 redhat 中有此命令。

## 修改网络配置文件

### 网卡信息文件

/etc/sysconfig/network-scripts/ifcfg-eth0

### 配置文件文本解释

| 条目 | 含义 |
| - | - |
|DEVICE=eth0 | 网卡设备名 |
| BOOTPROTO=none | 是否自动获取 IP (none, static, dhcp) |
| HWADDR=00:0c:29:17:c4:09 | mac地址 |
| NM_CONTROLLED=yes | 是否可以由 Network Manger 图形管理工具托管 |
| ONBOOT=yes | 是否随网络服务启动，eth0 生效 |
| TYPE=Ethernet | 以太网类型 |
| UUID=" " | 唯一识别码 |
|IPADDR=192.168.0.252| IP 地址 |
| NETMASK=255.255.255.0 | 子网掩码 |
| GATEWAY=192.168.0.1 | 网关 |
| DNS1=202.106.0.20 | DNS |
| IPV6INIT=no | ipv6没有启用 |
| USERCGL=no | 不允许非 root 用户控制此网卡 |

注意：UUID 必须唯一，例如使用虚拟机复制出的系统，UUID可能相同，会导致两个系统都不能上网。

### 主机名文件

	/etc/sysconfig/network

该文件修改后必须重启后生效。

hostname命令可以用来临时修改主机名。

### DNS配置文件

	/etc/resolv.conf

名称服务器，也就是 DNS服务器

	nameserver 202.106.0.20 

顶级域名输入时若省略，默认搜索的域名

	search localhost

