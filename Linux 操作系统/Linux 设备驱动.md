# ioctl 函数概述

1. ioctl 函数是设备驱动程序中对设备的I/O通道进行管理的函数, 即对设备的一些特性进行控制, 例如串口的传输波特率, 马达的转速等
2. ioctl 函数是文件结构中的一个属性分量, 即如果你的驱动程序提供了对 ioctl 的支持, 用户就可以在用户程序中使用 ioctl 函数来控制设备的I/O通道
3. 用户程序所作的只是通过命令码(cmd)告诉驱动程序它想做什么, 至于怎么解释这些命令和怎么实现这些命令, 这都是驱动程序要做的事情

# 函数原型

`int ioctl(int fd, unsign long cmd, ...)`

1. fd 是用户程序打开设备时使用open函数返回的文件描述符
2. cmd 是用户程序对设备的控制命令, 是应用程序用于区别设备驱动程序请求处理内容的值, 除了可区别数字外, 还包含有助于处理的几种相应信息, 大小为32位, 分4个域

# 命令码

| bit         | width   | parameter | 说明                              |
| ----------- | ------- | --------- | -------------------------------- |
| bit31~bit30 | 2 Bits  | direction | 方向区, 读, 写, 双向               |
| bit29~bit16 | 14 Bits | size      | 数据大小区, arg 变量传送的内存大小    |
| bit15~bit08 | 8 Bits  | type      | 幻数区, 设备类型, 用大小写英文字符表示 |
| bit7~bit0   | 8 Bits  | nr        | 区别序列号, 基数, 区分命令的命令顺序号 |

# 宏定义

```
#include	<asm-generic/ioctl.h>
#define		_IOC_SIZEBITS				14
#define		_IOC_TYPEBITS				8
#define		_IOC_NRBITS					8
#define		_IOC_DIRSHIFT				(_IOC_SIZESHIFT + _IOC_SIZEBITS)	/* 30 */
#define		_IOC_SIZESHIFT				(_IOC_TYPESHIFT + _IOC_TYPEBITS)	/* 16 */
#define		_IOC_TYPESHIFT				(_IOC_NRSHIFT   + _IOC_NRBITS)		/* 8 */
#define		_IOC_NRSHIFT				0
#define		_IOC(dir, type, nr, size)	(((dir) << _IOC_DIRSHIFT) | ((size) << _IOC_SIZESHIFT) | ((type) << _IOC_TYPESHIFT) | ((nr) << _IOC_NRSHIFT))
#define		_IOC_TYPECHECK(t)			(sizeof(t))
/* 由各域生成命令码 */
#define		_IO  (type, nr)				_IOC(_IOC_NONE,              (type), (nr), 0)
#define		_IOR (type, nr, size)		_IOC(_IOC_READ,              (type), (nr), (_IOC_TYPECHECK(size)))
#define		_IOW (type, nr, size)		_IOC(_IOC_WRITE,             (type), (nr), (_IOC_TYPECHECK(size)))
#define		_IOWR(type, nr, size)		_IOC(_IOC_READ | _IOC_WRITE, (type), (nr), (_IOC_TYPECHECK(size)))
/* 由命令码提取各域 */
#define		_IOC_DIR (cmd)
#define		_IOC_SIZE(cmd)
#define		_IOC_TYPE(cmd)
#define		_IOC_NR  (cmd)
```
