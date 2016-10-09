以 root 身份自动登录并执行初始化脚本

# 1 自动登录系统

在 /etc/inittab 中，有如下配置

```
1:2345:respawn:/sbin/agetty tty1 9600
2:2345:respawn:/sbin/agetty tty2 9600
3:2345:respawn:/sbin/agetty tty3 9600
4:2345:respawn:/sbin/agetty tty4 9600
5:2345:respawn:/sbin/agetty tty5 9600
6:2345:respawn:/sbin/agetty tty6 9600
```

表示系统可以有六个控制台，可以用ALT+(F1~F6)来切换。

而 /sbin/agetty 就是一个登陆验证程序，执行它，会提示用户输入用户名和密码，然后启动一个指定的 shell（在 passwd 文件中指定的）。

所以，我们只需将其修改为不执行agettty，而是执行自己编写的一个脚本，就可以跳过用户名和密码的输入。

修改如下：

1:2345:respawn:/root/logintest tty1 9600

这里我在/root/下放了一个测试脚本，这样系统启动时就会执行那个脚本，脚本内容：

```
#!/bin/sh
/bin/login -f root
```

脚本其实就是执行了一个root用户的登陆而已。

# 2 自动执行脚本

将要执行的脚本放到上面的 /root/logintest 的后面或 /etc/profile 文件的后面
