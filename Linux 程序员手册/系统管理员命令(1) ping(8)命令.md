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
