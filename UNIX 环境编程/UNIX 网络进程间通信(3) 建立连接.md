# 面向连接的套接字

1. 字节流 SOCK_STREAM

2. 顺序数据包 SOCK_SEQPACKET

# 客户端向服务器请求连接

在开始交换数据前, 服务器向客户端请求连接

即在请求服务的进程套接字(客户端)和提供服务的进程套接字(服务器)之间建立连接

```
#include <sys/socket.h>
int connect(int sockfd, const struct sockaddr *addr, socklen_t len);
```

sockfd 是客户端的套接字, 应绑定到客户端的地址, 若没有绑定, 则系统会给调用者(客户端)绑定一个默认地址

addr 是我们想与之通信的服务器的地址, 服务器的套接字必须已经绑定到这个地址上

# 服务器接受客户端的连接请求

```
#include <sys/socket.h>
int listen(int sockfd, int backlog);
int accept(int sockfd, struct sockaddr *restrict addr, socklen_t *restrict len);
```

## 服务器的等待连接队列

## listen

调用 listen, 则指定的服务器的套接字就能接收连接请求

## accept

调用 accept, 则获得连接请求并建立连接, 返回客户端的套接字描述符

sockfd 是服务器的套接字并且在函数返回后依然可用

addr 是获取的客户端的地址

sockfd 处于阻塞模式: 如果没有连接请求在等待, 则 accept 会阻塞直到一个请求到来

sockfd 处于非阻塞模式: accept 会返回 -1, 并将 errno 设置为 EAGAIN 或 EWOULDBLOCK
