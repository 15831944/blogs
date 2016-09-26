# 1. 使用串口登录远程主机

1. 确保串口线连接正确，在windows 下使用 devmgmt.msc 命令打开设备管理器，查看正确连接的串口号
2. 协议选择 SERIAL
3. 输入正确的串口号和合适的波特率

![Serial](http://img.blog.csdn.net/20160705132129757)

![Port](http://img.blog.csdn.net/20160705132237898)

# 2. 使用 SSH 协议登录远程主机

1. 选择 SSH 协议
2. 输入主机 IP 地址
3. 端口号设置为22
4. 使用 ssh 命令登录

![SSH](http://img.blog.csdn.net/20160705132653494)

# 3. 配色方案

![Color Scheme](http://img.blog.csdn.net/20160705130949293)

## ANSI Colors

1. 第1行为常规文本，第2行为粗体文本
2. 第2行比第1行对应位置颜色更亮

| black | red | green | yellow | blue | magenta | cyan | white |
| :- | :- | :- | :- | :- | :- | :- | :- |
| 粘住位目录前景色 | 压缩文件 | 其他人可写目录背景色 |  | 普通目录前景色 | 块特殊文件 | 链接文件 | 文本文件 |
|  | 压缩文件 | 可执行文件 |  | 可读可执行目录前景色 | 块特殊文件 | 链接文件 | 文本文件 |

粘住位目录例如 tmp 目录，所有人可都可写，但是只能删除自己的文件，权限为 drwxrwxrwt

[My Color]
text=f2f2f2
text(bold)=ffffff
background=000000
black=36342e
black(bold)=535755
red=a56434
red(bold)=cf9e72
green=008000			#其他人可写目录
green(bold)=1cc470
yellow=999606
yellow(bold)=e2e234
blue=4646ff
blue(bold)=6f6ff4
magenta=7b5175
magenta(bold)=a97ead
cyan=00a2c4
cyan(bold)=50ebfc
white=cfd8d3
white(bold)=eceeee
[Names]
name0=My Color
count=1


# 4. 自动登录脚本

以下 VB 脚本用于输入用于名，回车，等待提示字符串，输入密码，回车

```
Sub Main
xsh.Screen.Send "username"
xsh.Screen.Send VbCr
xsh.Screen.WaitForString "password: "
xsh.Screen.Send "userpassword"
xsh.Screen.Send VbCr
End Sub
```

# 5. 快速命令集

1. 点击 View 菜单
2. 选择 Quick Commands
3. 添加按钮
4. 使用 ctrl-F1~F9 执行快速命令
