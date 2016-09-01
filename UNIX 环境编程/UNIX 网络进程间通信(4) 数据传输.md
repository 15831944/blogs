# 发送和接收数据的函数接口

```
#include <sys/socket.h>
ssize_t send(int sockfd, const void *buf, size_t nbytes, int flags);
ssize_t sendto(int sockfd, const void *buf, size_t nbytes, int flags, const struct sockaddr *destaddr, socklen_t destlen);
ssize_t sendmsg(int sockfd, const struct msghdr *msg, int flags);
ssize_t recv(int sockfd, void *buf, size_t nbytes, int flags);
ssize_t recvfrom(int sockfd, void *restrict buf, size_t len, int flags, struct sockaddr *restrict addr, socklen_t *restrict adrlen);
ssize_t recvmsg(int sockfd, struct msghdr *msg, int flags);
```

| flags         | 描述 |
| ------------- | - |
| MSG_CONFIRM   | 提供链路层反馈以保持地址映射有效 |
| MSG_DONTROUTE | 勿将数据包路由出本地网络 |
| MSG_DONTWAIT  | 允许非阻塞操作(等价于使用 O_NONBLOCK) |
| MSG_EOF       | 发送数据后关闭套接字的发送端 |
| MSG_EOR       | 如果协议支持, 标记记录结束 |
| MSG_MORE      | 延迟发送数据包允许写更多数据 |
| MSG_NOSIGNAL  | 在写无连接的套接字时不产生 SIGPIPE 信号 |
| MSG_OOB       | 如果协议支持, 发送带外数据 |

send 函数, 用于面向连接的套接字, 目标地址被隐含(已调用过 connect 函数建立连接), 用于无连接的套接字时, 需先调用 connect 函数设置目标地址

sendto 函数, 用于无连接的套接字, 需要指定目标地址

| flags | 描述 |
| ---------------- | - |
| MSG_CMSG_CLOEXEC | 为 UNIX 域套接字上接收的文件描述符设置执行时关闭标志 |
| MSG_DONTWAIT     | 启用非阻塞操作(相当于使用 O_NONBLOCK) |
| MSG_ERRQUEUE     | 接收错误信息作为辅助数据 |
| MSG_OOB          | 如果协议支持, 获取带外数据 |
| MSG_PEEK         | 返回数据包内容, 而不真正取走数据包 |
| MSG_TRUNC        | 即使数据包被截断, 也返回数据包的实际长度 |
| MSG_WAITALL      | 等待直到所有的数据可用(仅 SOCK_STREAM) |

recvfrom 函数, 用于无连接的套接字, 获取发送者的地址
