你可能已经在虚拟机中安装好了交叉编译工具链，但是平时的主要工作环境还是在windows下，那么你很可能需要在windows下安装一个xshell或者secureCRT才进行远程登录到虚拟机，就不用来来回回的切换了。

到此之前，可参考我的其他文章。

[在 Linux 中安装 Blackfin 交叉编译工具链](http://blog.csdn.net/why19911024/article/details/51742865)

[SSH 远程登录 基础知识](http://blog.csdn.net/why19911024/article/details/51775671)

# 1. openssh-server 服务器安装

## 1. 查看是否已安装 openssh
```
#dpkg -l | grep ssh



```

## 2. 安装 openssh
```
#apt-get install openssh-server
#apt-get install openssh-client



```

## 3. 启动 openssh

```
#sudo /etc/init.d/ssh start
#sudo /etc/init.d/ssh stop
#sudo /etc/init.d/ssh restart



```
## 4. 查看22端口是否开放

```
#netstat -tnl




```

## 5. 查看ssh服务是否启动

```
#systemctl status sshd.service




```

# 2. sshd 服务器配置

/etc/ssh/sshd_config

```
PasswordAuthentication yes



```

# 3. 采用public key登录远程服务器


## 1. 生成一个公钥/私钥对

公钥和私钥的就好比锁和钥匙的关系。

openssh的ssh-keygen命令用来产生这样的私钥和公钥。

	# ssh-keygen -b 1024 -t dsa -C gucuiwen@myserver.com
	Generating public/private dsa key pair.
	Enter file in which to save the key (/root/.ssh/id_dsa): 
	Enter passphrase (empty for no passphrase): 
	Enter same passphrase again: 
	Your identification has been saved in /root/.ssh/id_dsa.
	Your public key has been saved in /root/.ssh/id_dsa.pub.
	The key fingerprint is:
	71:e5:cb:15:d3:8c:05:ed:05:84:85:32:ce:b1:31:ce gucuiwen@myserver.com

说明：

-b 1024　采用长度为1024字节的公钥/私钥对，最长4096字节，一般1024或2048就可以了，太长的话加密解密需要的时间也长。

-t dsa　　采用dsa加密方式的公钥/私钥对，除了dsa还有rsa方式，rsa方式最短不能小于768字节长度。

-C gucuiwen@myserver.com 对这个公钥/私钥对的一个注释和说明，一般用所有人的邮件代替。可以省略不写


把生成的公钥发送到对方的主机上去，用ssh-copy-id命令，自动保存在对方主机的/root/.ssh/authorized_keys 文件中去

	# ssh-copy-id -i /root/.ssh/id_rsa.pub root@192.168.142.84 
