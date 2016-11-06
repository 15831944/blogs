# 对称加密算法

对称加密, 也称为单秘钥加密, 同一个秘钥可以同时用作信息的加密和解密, 例如压缩包

# 非对称加密算法

1. 非对称加密算法(asymmetric cryptographic algorithm), 也称为公开秘钥加密算法, 非对称加密算法需要两个秘钥, 公钥(publickey), 相当于锁, 私钥(pritatekey), 相当于钥匙
2. 非对称加密工具称为良好隐私密码法(PGP, Pretty Good Privacy)

# SSH 的定义

1. SSH 安全外壳协议(Secure Shell)由 IETF (Internet Engineering Task Force) 的网络工作小组 (NetworkWorkingGroup) 所制定, 是建立在应用层和传输层基础上的安全协议
2. SSH 是目前较可靠的专为远程登录会话和其他网络服务提供安全性的协议, 可以有效防止远程管理过程中的信息泄露问题, 对登录过程和执行命令均进行加密传送
3. SSH 的主要目的是用来取代传统的 telnet(明文传送) 和 R 系列命令(rlogin, rsh, rexec)远程登录和远程执行命令的工具, 实现对远程登录和远程执行命令加密, 防止由于网络监听而出现的密码泄漏
4. SSH 协议目前有 SSH1 和 SSH2, SSH2 协议兼容 SSH1

# SSH 验证方式

## 第一种级别(基于口令的安全验证)

只要你知道自己帐号和口令, 就可以登录到远程主机, 所有传输的数据都会被加密, 但是不能保证你正在连接的服务器就是你想连接的服务器, 可能会有别的服务器在冒充真正的服务器, 即受到“中间人”这种方式的攻击

## 第二种级别(基于密匙的安全验证)

1. 必须为自己创建一对密匙, 并把自己的公匙放在需要访问的服务器上, 如果你要连接到 SSH 服务器上, 客户端软件就会向服务器发出请求, 用你的密匙进行安全验证
2. 服务器收到请求之后, 先在该服务器上你的主目录下寻找你的公匙, 然后把它和你发送过来的公匙进行比较, 如果两个密匙一致, 服务器就用公用密匙加密质询(challenge), 并把它发送给客户端软件
3. 客户端软件收到质询之后, 就可以用你的私人密匙解密再把它发送给服务器
4. 必须知道自己密匙的口令, 但不需要在网络上传送口令, 可防止中间人这种攻击方式, 但是整个登录的过程可能需要10秒

# SSH 协议层次

SSH 主要由三部分组成：

## 传输层协议 [SSH-TRANS]

1. SSH-TRANS 通常运行在 TCP/IP 连接上, 也可能用于其它可靠数据流上
2. SSH-TRANS 提供了强力的加密技术, 密码主机认证及完整性保护, 该协议中的认证基于主机, 并且该协议不执行用户认证, 更高层的用户认证协议可以设计为在此协议之上

## 用户认证协议 [SSH-USERAUTH]

1. SSH-USERAUTH 用于向服务器提供客户端用户鉴别功能
2. SSH-USERAUTH 运行在传输层协议 SSH-TRANS 的上层, 当 SSH-USERAUTH 开始后, 它从低层协议那里接收会话标识符, 会话标识符唯一标识此会话并且适用于标记以证明私钥的所有权, 也需要知道低层协议是否提供保密性保护

## 连接协议 [SSH-CONNECT]

1. SSH-CONNECT 将多个加密隧道分成逻辑通道
2. SSH-CONNECT 运行在用户认证协议的上层, 提供了交互式登录话路, 远程命令执行, 转发 TCP/IP 连接和转发 X11 连接

# SSH 软件组成

1. 服务端是一个守护进程(daemon), 一般是 sshd 进程, 在后台运行并响应来自客户端的连接请求, 包括公共密钥认证, 密钥交换, 对称密钥加密和非安全连接
2. 客户端包含 ssh 程序, 以及像 scp(远程拷贝), slogin(远程登录), sftp(安全文件传输)等其他的应用程序
3. 一旦建立一个安全传输层连接, 客户机就发送一个服务请求, 当用户认证完成之后, 会发送第二个服务请求, 这样就允许新定义的协议可以与上述协议共存
4. 连接协议提供了用途广泛的各种通道, 有标准的方法用于建立安全交互式会话外壳和转发(隧道技术)专有 TCP/IP 端口和 X11 连接
4. SSH 被设计成为工作于自己的基础之上而不利用超级服务器(inetd), 虽然可以通过 inetd 上的 tcpd 来运行 SSH 进程, 但没有必要
5. 启动 SSH 服务器后, sshd 运行起来并在默认的22端口进行监听(你可以用 `ps -waux | grep sshd` 来查看 sshd 是否已经被正确的运行了), 如果不是通过 inetd 启动的 SSH, 那么 SSH 就将一直等待连接请求, 当请求到来的时候, SSH 守护进程会产生一个子进程, 该子进程进行这次的连接处理

# SSH 应用软件

1. OpenSSH, 是 OpenBSD 组织开发的一款免费的 SSH 软件, 是 Linux 和 BSD 操作系统的标准组件
2. SSH Communications, 是 SSH Communications Security Corporation 公司的商业软件

# OpenSSH 软件包

1. libssh-4
2. openssh-client
3. openssh-server
4. openssh-sftp-server
5. ssh-import-id

# OpenSSH 命令

| command     | describe |
| ----------- | -------- |
| sshdSSH     | 服务端程序 |
| sftp-server | SFTP 服务端程序 |
| scp         | 非交互式 sftp-server 的客户端, 用来向服务器上传或下载文件 |
| sftp        | 交互式 sftp-server 客户端, 用法和 ftp 命令一样 |
| slogin      | SSH 的别名 |
| ssh         | SSH 协议的客户端程序, 用来登入远程系统或远程执行命令 |
| ssh-add     | SSH 代理相关程序, 用来向 SSH 代理添加 dsa key |
| ssh-agent   | ssh 代理程序 |
| ssh-keyscan | ssh　public key 生成器 |

1. ssh(1) - The basic rlogin/rsh-like client program
SSH协议的客户端程序，用来登入远程系统或远程执行命令(slogin)
2. sshd(8) - The daemon that permits you to log in
SSH服务端程序

3. ssh_config(5) - The client configuration file
4. sshd_config(5) - The daemon configuration file
客户端和服务器的配置文件的定义

5. ssh-agent(1) - An authentication agent that can store private keys
ssh代理程序
6. ssh-add(1) - Tool which adds keys to in the above agent
SSH代理相关程序，用来向SSH代理添加dsa key

7. sftp(1) - FTP-like program that works over SSH1 and SSH2 protocol
交互式sftp-server客户端，用法和ftp命令一样。
8. scp(1) - File copy program that acts like rcp
非交互式sftp-server的客户端，用来向服务器上传/下载文件
9. sftp-server(8) - SFTP server subsystem (started automatically by sshd)
SFTP服务端程序（类似FTP但提供数据加密的一种协议）

10. ssh-keygen(1) - Key generation tool
11. ssh-keyscan(1) - Utility for gathering public host keys from a number of hosts
12. ssh-keysign(8) - Helper program for host-based authentication
ssh public key 生成器

# OpenSSH 登录方式

1. Password
用户名密码登录

2. Publickey
公钥/私钥登录

3. Keybord Interactive

4. GSSAPI

# 相关文件

.ssh目录的权限必须是700

服务器中
~/.ssh/known_hosts
存放ssh指纹，已识别的服务器
~/.ssh/authorized_keys
存放各客户端的公钥，即可以把各个*.pub文件中的内容添加到此文件

客户端中
~/.ssh/id_dsa
存放客户端的私钥
私钥必须是600权限

日志文件
/var/log/secure

# 参考

[openssh 官方用户手册](http://www.openssh.com/manual.html)

[SH, The Secure Shell: The Definitive Guide](http://docstore.mik.ua/orelly/networking_2ndEd/ssh/index.htm)

[ssh远程登录使用指南](http://bbs.chinaunix.net/thread-2113237-1-1.html)

[SSH入门学习基础教程](http://www.linuxidc.com/Linux/2014-06/103008.htm)

[SSH原理与运用](http://www.ruanyifeng.com/blog/2011/12/ssh_remote_login.html)
