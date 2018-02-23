关于apue.3e中apue.h的使用

近来要学一遍APUE第三版，并于此开博做为记录。

先下载源文件：

```
url: http:www.apuebook.com/code3e.html
curl -O http:www.apuebook.com/src.3e.tar.gz
tar -zxvf src.3e.
cd apue.3e
```

从上面ls的结果看，其实完全看不明白这些目录与APUE书中代码的关系，或者有些目录可以猜测出是那一章。不过有个小技巧：

`ls -l figlinks/`

你会发现，这个目录下全是软链。通过软链正好可以对应到书上的代码。比如，书上图1-3为ls命令的简易实现，这正是：

# fig1.3 -> ../intro/ls1.c

先从apue.h的使用上做一说明。个人觉得有两种方式来使用，整理如下。 至于编译环境，本人使用Ubuntu 14.04 LTS。

一次编译生成libapue.a文件，长久使用

代码如下：

  apt-get install libbsd- # 用于解决make时报：can,t  -lbsd错误。

# 编译成功后，执行如下copy操作：
# libapue.a是apue.h文件的静态链接库

  ./include/apue.h /usr/include/
  ./lib/libapue.a /usr/local/lib/

# 至于为什么要放置静态文件在上述目录，是因为gcc在加载静态文件时设置的从上述目录查询，可以通过如下文件知晓。
# /etc/.conf.d/libc.conf

下面来测试上述配置的效果。实际上，上述make时，已经将所有c文件编译成目标文件了。可以看下各个目录下都有相应.c文件的.o文件了。

  ls1.c
  /tmp/ccyhkMzS.o: In function `main
  ls1.c:(.text+): undefined reference to `err_quit
  ls1.c:(.text+): undefined reference to `err_sys
  collect2: error:  returned  exit status

# 上述编译因为没有带apue表态库，所以gcc找不到APUE作者定义的错误处理函数，err_quit, err_sys。
  ls1.c -lapue # 带上apue表态库
./a.out ./
  testerror.c
shell2.c
hello
# ...

如上，只有每次编译时带上-lapue的参数，即可以使用部署在/usr/local/lib/下的libapue.a库。

如果你是在Mac os X 10.11系统下编译，当copy文件到/usr/inlucde目录时，会出现Operation not permitted报错。

因为10.11启动了SIP特性，即使使用sudo cp也会失败。要关闭SIP，需要在Recovery OS环境下执行如下命令：

sudo csrutil disable

每次独立编译apue.h和error.c文件

第二种方式是每次单独编译apue，方法如下。需要先清理掉上述方法生成的编译环境：

  -vf /usr/include/apue.h /usr/local/lib/libapue.a
  clean # 清掉之前的编译临时文件

  include/apue.h ./  lib/error.c ./  apue.h

# 在最后一行的endif预编译命令前加上一行include指令如下（包括井号）：
#inclulde error.c

  intro/ls1.c .
  -o  ./ ./
# 编译成功，执行成功。ls1.c需要的inlucde文件都已经copy到当前目录了

这种方式的好处是，每次编译时，使用了apue.h中的什么文件，直接从lib/下拷到当前目录即可，比较清楚的知道用了那些apue.h中的函数。

不足之处是每次都需要拷贝。

# 参考

http://www.cnblogs.com/qinqiao/p/how-to-compile-apue-v3-apue_h.html
