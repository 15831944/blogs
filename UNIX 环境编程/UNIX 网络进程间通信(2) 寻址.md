# 1. 如何找到目标通信进程

1. 计算机IP地址, 用于标识网络上我们想与之通信的计算机

2. 服务端口号, 用于表标识目标计算机上特定的进程

# 2. 字节序

最高有效字节(Most Significant Byte, MSB)

最低有效字节(Least Significant Byte, LSB)

对于一个千数量级的整数, 我们认为千位是"最多重要的", 即 MSB, 个位是"最少重要的", 即 LSB

因此, 对于一个整数, MSB 总是在左边, LSB 总是在右边

## 1. 大端字节序 big-endian

最小字节地址出现在 MSB 上, 地址向右递增, 地址的增长顺序和数据的书写顺序一致

## 2. 小端字节序 little-endian

最小字节地址出现在 LSB 上, 地址向左递增

## 3. 举例

若将一个字符指针(cp)强制转换到一个整数地址 0x04030201 上

对于大端字节序, cp 指向 MSB, 内容为04

对于小端字节序, cp 指向 LSB, 内容为01

字节序是处理器架特性, 为了使异构的计算机系统能够交换协议信息而不会被字节序所混淆, 网络协议需要指定字节序

TCP/IP 协议使用大端字节序, 地址用网络字节序表示

## 4. 主机字节序和网络字节序的转换

应用程序需要以一种易读的形式打印地址时, 可调用下列函数

```
#include <arpa/inet.h>
uint32_t htonl(uint32_t hostint32);
uint16_t htons(uint16_t hostint16);
uint32_t ntohl(uint32_t netint32);
uint16_t ntohs(uint16_t netint16);
```

h 表示主机字节序

n 表示网络字节序

l 表示长整型(4字节)

s 表示短整型(2字节)

uint32_t 是系统数据类型, 表示32位无符号整型

# 3. 地址格式

对于不同的套接字通信域, 地址格式是不同的

1. IPv4 因特网域套接字地址结构 struct sockaddr_in

2. IPv6 因特网域套接字地址结构 struct sockaddr_in6

为了使不同的地址格式能够传入到套接字函数, 地址会被强制转换成一个通用的地址结构 sockaddr, 输入到套接字例程中

## 1. 点分十进制地址格式

网络字节序二进制地址格式与点分十进制文本字符串格式的转换

```
#include <arpa/inet.h>
const char	*inet_ntop(int domain, const void *restrict addr, char *restrict str, socklen_t size);
int			 inet_pton(int domain, const char *restrict str,  void *restrict addr);
```

p 表示 presentation format

n 表示 network format

### size 取值

INET_ADDRSTRLEN

INET6_ADDRSTRLEN

# 4. 地址查询

## 1. 网络配置信息

### 1. 静态文件

/etc/hosts

/etc/services

### 2. 名字服务

域名系统(Domain Name System, DNS)

网络信息服务(Network Information Service, NIS)

## 2. 获取主机信息

```
#include <netdb.h>
struct hostent	*gethostent(void);
void			 sethostent(int stayopen);
void			 endhostent(void);
```

1. gethostent 函数打开主机数据库文件, 返回文件中的下一个条目

2. sethostent 函数打开主机数据库文件, 若已被打开则将其回绕, stayopen 参数为真则调用 gethostent 后, 文件依然是打开的

3. endhostent 函数关闭主机数据库文件

## 3. 获取网络名字和网络编号

```
#include <netdb.h>
struct netent	*getnetbyaddr(uint32_t net, int type);
struct netent	*getnetbyname(const char *name);
struct netent	*getnetent(void);
void			 setnetent(int stayopen);
void			 endnetent(void);
```

## 4. 获取协议名称和协议编号

```
#include <netdb.h>
struct protoent		*getprotobyname(const char *name);
struct protoent		*getprotobynumber(int proto);
struct protoent		*getprotoent(void);
void				 setprotoent(int stayopen);
void				 endprotoent(void);
```

## 5. 获取服务名称和端口号

```
#include <netdb.h>
struct servent		*getservbyname(const char *name, const char *proto);
struct servent		*getservbyprot(int port, const char *proto);
struct servent		*getservent(void);
void				 setservent(int stayopen);
void				 endservent(void);
```

## 6. 使用主机名和服务名获取地址

```
#include <sys/socket.h>
#include <netdb.h>
int getaddrinfo(const char *restrict hosts, 
				const char *restrict service, 
				const struct addrinfo *restrict hint, 
				struct addrinfo **restrict res);
void freeaddrinfo(struct addrinfo *ai);
```

## 7. 使用地址获取主机名和服务名

```
#include <sys/socket.h>
#include <netdb.h>
int getnameinfo(const struct sockaddr *restrict addr,    socklen_t alen,
				char                  *restrict host,    socklen_t hostlen,
				char                  *restrict service, socklen_t servlen, 
				int flags);
```

# 5. 将套接字绑定到地址

客户端的套接字关联地址, 可以让系统选择一个默认地址

服务器可接收客户端请求, 需要给服务器套接字关联一个众所周知的地址

客户端需要一种方法来发现连接服务器所需要的地址, 方法是服务器保留一个地址并且注册在 /etc/services 或者某个名字服务中

```
#include <sys/socket.h>
int bind(       int sockfd, const struct sockaddr          *addr, socklen_t           len);
int getsockname(int sockfd,       struct sockaddr *restrict addr, socklen_t *restrict alenp);
int getpeername(int sockfd,       struct sockaddr *restrict addr, socklen_t *restrict alenp);
```
