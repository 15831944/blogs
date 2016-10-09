# 1. 网络进程通信概述

使用TCP/IP协议的应用程序通常采用应用编程接口：

| 接口 | 标准 | 应用 |
| - | - | - |
| 套接字(socket) | POSIX | UNIX BSD |
| 传输层接口(Transport Layer Interface, TLI) |  | UNIX System V |

几乎所有的应用程序都是采用 socket

套接字是通信端点的抽象, 接收进程从套接字读取数据, 发送进程向套接字写数据

正如使用文件描述符访问文件, 应用程序使用套接字描述符访问(引用)套接字

套接字是网络编程的入口，它提供了大量的系统调用，构成了网络程序的主体

在 Linux 系统中，socket 属于文件系统的一部分, 网络通信可以被看作是对文件的读取，使得我们对网络的控制和对文件的控制一样方便

# 2. 套接字的创建

```
#include <sys/socket.h>
int socket (int domain, int type, int protocol)
```

## 1. **通信域**

| 通信域 | 描述 |
| - | - |
| AF_INET             | IPv4 因特网域 |
| AF_INET6            | IPv6 因特网域 |
| AF_UNIX(AF_LOCAL)   | UNIX 域 |
| AF_UPSPEC           | 未指定 unspecified |

### 1. IPv4 域套接字

要通过 Internet 进行通信，至少需要一对套接字

其中一个运行在客户端，称之为ClientSocket

另一个运行于服务器端面，称为ServerSocket

根据连接启动的方式以及本地要连接的目标，套接字之间的连接过程可以分为三个步骤：

#### 1. 服务器监听

服务端套接字并不定位具体的客户端套接字，而是处于等待连接的状态，实时监控网络状态。

#### 2. 客户端请求

由客户端的套接字提出连接请求，要连接的目标是服务器端套接字。为此，客户端的套接字必须首先描述它要连接的服务器的套接字，指出服务器套接字的地址和端口号，然后再向服务器端套接字提出连接请求。

#### 3. 连接确认

当服务器端套接字监听到或者说接收到客户端套接字的连接请求时，它就响应客户端套接字的请求，建立一个新的线程，把服务器端套接字的信息发送给客户端，一旦客户端确认了此连接，连接即可建立。而服务器端继续处于监听状态，继续接收其他客户端的连接请求。

### 2. Unix 域套接字

Unix 域套接字是面向连接的，每个套接字的连接都建立了一个新的通讯信道

服务器可能同时处理许多连接，但对于每个连接都有不同的文件描述符

这个属性使 Unix 域套接字能够比命名管道更好的适应 IPC 任务

## 2. **套接字类型**

1. 数据报为固定长度, 即发送和接收的数据量一致

2. 字节流为不固定长度, 无法分辨报文界限, 可能需要若干次函数调用才能接收完成

3. 无连接的套接字需要指定接收者地址, 是不可靠的

4. 需要先建立逻辑连接的套接字是端到端的通信链路, 对话中不包含地址信息, 是可靠的

5. 套接字通信是双向的, 发送进程和接收进程是对等的

### 1. SOCK_DGRAM 数据报

固定长度的, 不需要逻辑连接, 不可靠的报文传递

数据报为自包含报文, 即包含接收者地址

AF_INET 域默认协议为 UDP

### 2. SOCK_RAW 原始数据报

固定长度的, 不需要逻辑连接, 不可靠的报文传递

IP 协议的数据报文接口(在 POSIX.1 中为可选)

绕过传输层(TCP和UDP协议), 直接访问下面的网络层(IP层), 因此应用程序需要构建自己的协议头部

需要超级用户特权

### 3. SOCK_SEQPACKET 顺序数据包

固定长度的, 有序的, 可靠的, 面向连接的报文传递

流控制传输协议(Stream Control Transmission Protocol, SCTP)

### 4. SOCK_STREAM 字节流

有序的, 可靠的, 双向的, 需先建立逻辑连接的字节流, 端到端的通信链路

基于字节流意味着无法分辨报文界限, 发送和接收的数据量可能不一致(前3者可以), 需要若干次函数调用才能接收完成

AF_INET 域默认协议为 TCP

## 3. **协议**

| 协议 | 描述 |
| - | - |
| IPPROTO_IP   | IPv4 网际协议 |
| IPPROTO_IPv6 | IPv6 网际协议(在 POSIX.1 中为可选) |
| IPPROTO_ICMP | 因特网控制报文协议(Internet Control Message Protocol) |
| IPPROTO_RAW  | 原始 IP 数据包协议(在 POSIX.1 中为可选) |
| IPPROTO_TCP  | 传输控制协议(Transmission Control Protocol) |
| IPPROTO_UDP  | 用户数据报协议(User Datagram Protocol) |

# 3. 套接字的释放

```
#include <sys/socket.h>
int shutdown (int sockfd, int how)
```
| how | 含义 |
| --------- | - |
| SHUT_RD   | 关闭读端, 则无法从套接字读取数据, 只能发送数据 |
| SHUT_WR   | 关闭写端, 则无法使用套接字发送数据, 只能接收数据 |
| SHUT_REWR | 既无法读取数据, 又无法发送数据 |

一个套接字可能被多个文件描述符引用

若使用 close 函数, 则所有活动的引用(文件描述符)关闭时, 才能释放网络端点(套接字)

若使用 shutdown 函数, 则可以使套接字处于不活动状态, 不论该套接字存在多少文件描述符的引用

进程 A 向进程 B 发送数据, 若只关闭进程 B 套接字的写端, 则进程 B 仍然可以通过该套接字的读端接收数据, 则进程 B 就能够确定数据传输何时结束

# 4. 套接字选项

## 1. 套接字选项类型

| 类型 | 标准 | 说明 |
| - | - | - |
| 套接字层通用选项 | SUS | 工作在所有套接字类型上 |
| 在套接字层管理的选项 | SUS | 依赖于下层协议的支持 |  
| 特定于某协议的选项 |  | 每个协议独有 |

## 2. 设置套接字选项

```
#include <sys/socket.h>
int setsockopt(int sockfd, int level, int option, const void *val, socklen_t len);
```

| level | 说明 |
| ----------- | - |
| SOL_SOCKET  | 通用的套接字层次选项 |
| IPPROTO_TCP | TCP 选项 |
| IPPROTO_IP  | IP 选项 |

# 3. 查看套接字选项

```
#include <sys/socket.h>
int getsockopt(int sockfd, int level, int option, void *restrict val, socklen_t *restrict lenp);
```

# 总结

服务器的地址需要绑定到服务器的套接字

客户端的描述符通过地址访问服务器,去连接服务器的描述符

客户端的描述符如果可写,说明客户端成功连接到了服务器

服务器的描述符如果可读,说明服务器正在等待客户端的请求

面向连接的服务,对话中不包含地址信息,需要先建立连接

无连接的服务,数据包包含接受者地址

```
创建和删除套接字描述符
int socket (int domain, int type, int protocol);
int shutdown (int sockfd, int how);

地址查询
int getaddrinfo (const char *restrict host,
                 const char *restrict service,
                 const struct addrinfo *restrict hint,
                 struct addrinfo **restrict res);
void freeaddrinfo (struct addrnifo *ai);

套接字与地址关联
int bind (int sockfd, const struct sockaddr *addr, socklen_t len);

int getsockname (int sockfd, struct sockaddr *restrict addr, socklen_t *restrict alenp);
int getpeername (int sockfd, struct sockaddr *restrict addr, socklen_t *restrict alenp);

建立连接
int connect (int sockfd, const struct sockaddr *addr, aocklen_t len);

int listen (int sockfd, int backlog);
int accept (int sockfd, struct sockaddr *restrict addr, socklen_t *restrict len);

数据传输
ssize_t send (int sockfd, const void *buf, size_t nbytes, int flags);
ssize_t sendto (int sockfd, const void *buf, size_t nbytes, int flags,
                const struct sockaddr *destaddr, socklen_t destlen);
ssize_t sendmsg (int sockfd, const struct msghdr *msg, int flags);

ssize_t recv (int sockfd, void *buf, size_t nbytes, int flags)
ssize_t recvfrom (int sockfd, void *restrict buf, size_t len, int flags,
                  strcut sockaddr *restrict addr, socklen_t *restrict addrlen);
ssize_t recvmsg (int sockfd, struct msghdr *msg, int flags);

套接字选项
int setsockopt (int sockfd, int level, int option, const void *val, socklen_t len);
int getsockopt (int sockfd, int level, int option, void *restrict val, socklen_t *restrict lenp);
```
