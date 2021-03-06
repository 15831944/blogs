# ping

名称：
Packet Internet Grope 因特网包探索器
分类：
System administration commands 系统管理员命令
作用：
send ICMP ECHO_REQUEST to network hosts 向网络主机发送ICMP回声请求消息
ICMP是（Internet Control Message Protocol）Internet控制报文协议。它是TCP/IP协议族的一个子协议，用于在IP主机、路由器之间传递控制消息。
ICMP协议是一种面向无连接的协议，没有具体的端口号。
-t选项：
ttl(time to live) Set the IP Time to Live.
生存时间，指定IP包被路由器丢弃之前允许通过的最大网段数量。避免IP包在网络中的无限循环和收发，节省了网络资源
TTL是IPv4包头的一个8 bit字段。
TTL的作用是限制IP数据包在计算机网络中的存在的时间。TTL的最大值是255，TTL的一个推荐值是64。
虽然TTL从字面上翻译，是可以存活的时间，但实际上TTL是IP数据包在计算机网络中可以转发的最大跳数。
TTL字段由IP数据包的发送者设置，在IP数据包从源到目的的整个转发路径上，每经过一个路由器，路由器都会修改这个TTL字段值，具体的做法是把该TTL的值减1，然后再将IP包转发出去。如果在IP包到达目的IP之前，TTL减少为0，路由器将会丢弃收到的TTL=0的IP包并向IP包的发送者发送 ICMP time exceeded消息。

# tcpdump

# halt

名称：halt
　　使用权限：系统管理者
　　使用方式：halt [-n] [-w] [-d] [-f] [-i] [-p]
　　说明：若系统的 runlevel 为 0 或 6 ，则关闭系统，否则以 shutdown 指令（加上 -h 参数）来取代
　　参数：

　　-n : 在关机前不做将记忆体资料写回硬盘的动作
　　-w : 并不会真的关机，只是把记录写到 /var/log/wtmp 档案里
　　-d : 不把记录写到 /var/log/wtmp 档案里（-n 这个参数包含了 -d） -f : 强迫关机，不呼叫 shutdown 这个指令
　　-i : 在关机之前先把所有网络相关的装置先停止
　　-p : 当关机的时候，顺便做关闭电源（poweroff）的动作

　　范例：
　　halt -p 关闭系统后关闭电源。
　　halt -d 关闭系统，但不留下纪录。

linux常用关机命令及其区别:

在linux下一些常用的关机/重启命令有shutdown、halt、reboot、及init，它们都可以达到重启系统的目的，但每个命令的内部工作过程是不同的，通过本文的介绍，希望你可以更加灵活的运用各种关机命令。

1.shutdown
shutdown命令安全地将系统关机。
有些用户会使用直接断掉电源的方式来关闭linux，这是十分危险的。因为linux与windows不同，其后台运行着许多进程，所以强制关机可能会导致进程的数据丢失﹐使系统处于不稳定的状态﹐甚至在有的系统中会损坏硬件设备。
而在系统关机前使用shutdown命令﹐系统管理员会通知所有登录的用户系统将要关闭。并且login指令会被冻结﹐即新的用户不能再登录。直接关机或者延迟一定的时间才关机都是可能的﹐还可能重
启。这是由所有进程〔process〕都会收到系统所送达的信号〔signal〕决定的。这让像vi之类的程序有时间储存目前正在编辑的文档﹐而像处理邮件〔mail〕和新闻〔news〕的程序则可以正常地离开等等。
shutdown执行它的工作是送信号〔signal〕给init程序﹐要求它改变runlevel。Runlevel 0被用来停机〔halt〕﹐runlevel 6是用来重新激活〔reboot〕系统﹐而runlevel 1则是被用来让系统进入管理工作可以进行的状态﹔这是预设的﹐假定没有-h也没有-r参数给shutdown。要想了解在停机〔halt〕或者重新开机〔reboot〕过程中做了哪些动作﹐你可以在这个文件/etc/inittab里看到这些runlevels相关的资料。

shutdown 参数说明:

[-t] 在改变到其它runlevel之前﹐告诉init多久以后关机。
[-r] 重启计算器。
[-k] 并不真正关机﹐只是送警告信号给每位登录者〔login〕。
[-h] 关机后关闭电源〔halt〕。
[-n] 不用init﹐而是自己来关机。不鼓励使用这个选项﹐而且该选项所产生的后果往往不总是你所预期得到的。
[-c] cancel current process取消目前正在执行的关机程序。所以这个选项当然没有时间参数﹐但是可以输入一个用来解释的讯息﹐而这信息将会送到每位使用者。
[-f] 在重启计算器〔reboot〕时忽略fsck。
[-F] 在重启计算器〔reboot〕时强迫fsck。
[-time] 设定关机〔shutdown〕前的时间。

2.halt—-最简单的关机命令

其实halt就是调用shutdown -h。halt执行时﹐杀死应用进程﹐执行sync系统调用﹐文件系统写操作完成后就会停止内核。
参数说明:
[-n] 防止sync系统调用﹐它用在用fsck修补根分区之后﹐以阻止内核用老版本的超级块〔superblock〕覆盖修补过的超级块。
[-w] 并不是真正的重启或关机﹐只是写wtmp〔/var/log/wtmp〕纪录。
[-d] 不写wtmp纪录〔已包含在选项[-n]中〕。
[-f] 没有调用shutdown而强制关机或重启。
[-i] 关机〔或重启〕前﹐关掉所有的网络接口。
[-p] 该选项为缺省选项。就是关机时调用poweroff。

3.reboot

reboot的工作过程差不多跟halt一样﹐不过它是引发主机重启﹐而halt是关机。它的参数与halt相差不多。

4.init

init是所有进程的祖先﹐它的进程号始终为1﹐所以发送TERM信号给init会终止所有的用户进程﹑守护进程等。shutdown就是使用这种机制。init定义了8个运行级别(runlevel)，init 0为关机﹐init1为重启。关于init可以长篇大论﹐这里就不再叙述。另外还有telinit命令可以改变init的运行级别﹐比如﹐telinit -iS可使系统进入单用户模式﹐并且得不到使用shutdown时的信息和等待时间。
