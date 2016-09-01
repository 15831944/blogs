# OpenSSH 软件包


libssh-4
openssh-client
openssh-server
openssh-sftp-server
ssh-import-id

# OpenSSH 命令

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