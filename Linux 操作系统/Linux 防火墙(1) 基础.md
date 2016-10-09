# 1. 防火墙技术

防火墙是用于阻止计算机之间直接通信，位于两个或多个网络间，实施网络之间访问控制的组件集合。

| 技术 | 协议栈 | 判据 | 检测内容 | 逻辑位置 | 物理位置 | 代表 |
| - | - | - | - | - | - | - |
| 静态包过滤 | 网络层 | 访问控制表 | 源地址, 目的地址  | 网络边界 | 负责内外网络转换的网关, 个人计算机 | 已退出市场 |
| 动态包过滤 | 网络层, 传输层 | 访问控制表 | 端口号, 协议状态 | 网络边界 | 负责内外网络转换的网关, 个人计算机 | 无 |
| 应用级网关 | 应用层 | 应用协议分析 | 截进出某应用程序的所有封包，并且封锁其他的封包，通常是直接将封包丢弃 | 两个网络的驳接处 | 通用PC平台或芯片级专用硬件平台 | NetScreen, FortiNet |
| 代理服务 | 应用层 | 略 | 略 | 略 | 小型的带有数据检测过滤功能的透明代理服务器 | 略 |
| 状态监视 | 略 | 略 | 略 | 略 | 略 | Checkpoint |
| 数据库协议分析与控制技术 | 略 | 略 | 略 | 略 | 略 | 略 |

# 2. 防火墙策略

| 策略 | 内容 |
| - | - |
| 通策略 | 默认门是全关的，必须要定义谁能进 |
| 堵策略 | 默认门是洞开的，有身份认证就能进 |

# 3. 应用软件

iptables 现在被做成了一个服务，可以进行启动，停止的。启动，则将规则直接生效，停止，则将规则撤销。

iptables 还支持自己定义链。但是自己定义的链，必须是跟某种特定的链关联起来的。

在一个关卡设定，指定当有数据的时候专门去找某个特定的链来处理，当那个链处理完之后，再返回。接着在特定的链中继续检查。

| 软件包 | 工作空间 | 功能 |
| - | - | - |
| iptables | 用户空间 |规则列表，定义规则和策略|
| netfilter | 内核空间 | 网络过滤器，读取规则和策略|

# 4. 数据包流向

一个特定是数据包必定会经过规则链中的一个或多个。

| 类型 | 流向 |
| - | - |
| 本机向外界发 | Output -> Postrouting |
| 外界向本机发 | Prerouting -> Input |
|外界经过本机向外界发 | Prerouting -> Forward -> Postrouting |

# 5. 规则链

也叫做钩子函数（hook functions），由 netfilter 规定。

规则链就是规则的集合。针对特定数据包的各种防火墙规则，按照顺序依次放入对应的链中。

| 名称 | 位置 | 含义 | 内容 | 判断时机 | 举例 |
| - | - | - | - |
| PREROUTING | 路由前 | for altering  packets as soon as they come in | 当收到要通过防火墙发送给其他网络地址的数据包时应用的规则 | 在对数据包做路由选择之前 | 略 |
| INPUT | 数据包入口 | for packets destined to local sockets | 外界访问防火墙数据的规则的集合 | 收到访问防火墙本地地址的数据包时 | 限制某IP是否可以管理防火墙 |
| FORWARD | 转发关卡 | for packets being routed through the box | 所有通过防火墙的数据的规则的集合 | 收到要通过防火墙发送给其他网络地址的数据包时 | 限制某IP是否能访问某网站 |
| OUTPUT | 数据包出口 | for locally-generated packets | 防火墙访问外界数据的规则的集合 | 防火墙本机向外发出数据时 | 是否允许防火墙对外进行DNS解析 |
| POSTROUTING | 路由后 | 略 | 略 |在对数据包做路由选择之后 | 略 |

## 1. 名词

状态监视 Stateful Inspection

应用协议分析(Application Protocol Analysis)技术工作在OSI模型的最高层——应用层上，在这一层里能接触到的所有数据都是最终形式，也就是说，防火墙“看到”的数据和我们看到的是一样的，而不是一个个带着地址端口协议等原始内容的数据包，因而它可以实现更高级的数据检测过程。

通用PC平台：使用标准计算机的硬件平台和一些功能经过简化处理的UNIX系列操作系统

专用硬件平台：采用专门设计的硬件平台，搭建专门开发的防火墙软件

静态数据包过滤 Static Packet Filtering

动态数据包过滤 Dynamic Packet Filtering 与基于状态的包过滤防火墙技术，即Stateful-based Packet Filtering 其实是同一类型

应用级网关 Application Level Gateways

代理服务(Proxy Service)也称链路级网关或TCP通道(Circuit Level Gateways or
TCP Tunnels)

访问控制表 Access Control Table

协议栈：TCP/IP 协议栈层级

网络边界：两个网络之间的接口处，称为边界防火墙，工作于操作系统网络处理接口与网络驱动程序接口(Network Driver Interface Specification，NDIS)之间

代理服务器(Transparent Proxy)

网络边界，即两个网络之间的接口处，在操作系统网络处理接口与网络驱动程序接口之间

## 2. 在协议栈的不同层级有什么不同？

在网络层只能对源地址和目标地址进行检测，而在应用层，软件处理的数据同人们看到的数据，包含所有信息。

## 3. 什么影响防火墙的性能？

吞吐量可能成为流量瓶颈。

# 6. 规则表定义

为了让各个功能交替工作，我们制定出了“表”这个定义，来定义、区分各种不同的工作功能和处理方式。

除了三张默认的表外，我们还可以自定义额外的链。

规则的次序非常关键，谁的规则越严格，应该放的越靠前，而检查规则的时候，是按照从上往下的方式进行检查的。

| 规则表 | 内容 | 作用于哪种数据包或规则链 |
| - | - | - |
| filter | 定义过滤功能，即数据包中的通策略或堵策略，用于管理本机数据包的进出。 | INPUT, FORWARD, OUTPUT |
| nat | 定义地址转换功能。用于来源地与目的地的 IP 或 port 转换，用于管理后端主机（防火墙内部主机的）访问internet。与本机无关。主要与 Linux 主机后的内部计算机有关 | PREROUTING, OUTPUT, POSTROUTING |
| mangle | 修改报文原数据，即特殊数据包的路由标记，即修改TTL。能够实现将数据包的元数据拆开，在里面做标记/修改内容的。而防火墙标记，其实就是靠mangle来实现的。用于管理有特殊标记的包 | PREROUTING，INPUT，FORWARD，OUTPUT，POSTROUTING |
| raw | 略 | 略 |
| security | 略 | 略 |

# 7. 参考

http://zhidao.baidu.com/question/23063704.html

http://www.xuexila.com/diannao/360634.html

http://blog.chinaunix.net/uid-23886490-id-3167640.html

http://drops.wooyun.org/tips/1424

http://blog.chinaunix.net/uid-9950859-id-98279.html

http://blog.chinaunix.net/uid-26495963-id-3279216.html

http://blog.csdn.net/houlc/article/details/7089436

http://blog.chinaunix.net/uid-26495963-id-3279216.html
