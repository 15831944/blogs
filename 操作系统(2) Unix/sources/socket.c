/*********************
	socket 编程接口
*********************/

// 创建和删除套接字描述符
int socket (int domain, int type, int protocol);
int shutdown (int sockfd, int how);

// 地址查询
int getaddrinfo (const char *restrict host,
                 const char *restrict service,
                 const struct addrinfo *restrict hint,
                 struct addrinfo **restrict res);
void freeaddrinfo (struct addrnifo *ai);

// 服务器套接字与地址关联
int bind (int sockfd, const struct sockaddr *addr, socklen_t len);

int getsockname (int sockfd, struct sockaddr *restrict addr, socklen_t *restrict alenp);
int getpeername (int sockfd, struct sockaddr *restrict addr, socklen_t *restrict alenp);

// 建立连接
int connect (int sockfd, const struct sockaddr *addr, aocklen_t len);

int listen (int sockfd, int backlog);
int accept (int sockfd, struct sockaddr *restrict addr, socklen_t *restrict len);

// 数据传输
ssize_t send (int sockfd, const void *buf, size_t nbytes, int flags);
ssize_t sendto (int sockfd, const void *buf, size_t nbytes, int flags,
                const struct sockaddr *destaddr, socklen_t destlen);
ssize_t sendmsg (int sockfd, const struct msghdr *msg, int flags);

ssize_t recv (int sockfd, void *buf, size_t nbytes, int flags)
ssize_t recvfrom (int sockfd, void *restrict buf, size_t len, int flags,
                  strcut sockaddr *restrict addr, socklen_t *restrict addrlen);
ssize_t recvmsg (int sockfd, struct msghdr *msg, int flags);

// 套接字选项
int setsockopt (int sockfd, int level, int option, const void *val, socklen_t len);
int getsockopt (int sockfd, int level, int option, void *restrict val, socklen_t *restrict lenp);
