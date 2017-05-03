# 概述

1. 上电后, 先启动 UBoot 这个 bootloader 引导程序, 然后转交给 uclinux 操作系统, 操作系统采用 BusyBox 作为 shell

# U-Boot

操作系统的引导程序, U-Boot，全称 Universal Boot Loader，是遵循GPL条款的开放源码项目。U-Boot的作用是系统引导。

# uclinux

image3.8.bin

50.    Uclinux并非强实时操作系统, 定时功能有时会有几十微秒的误差；

# BusyBox

# FPGA

1. FPGA底层驱动, 输出和反校都在驱动中完成；
1. 驱动：I¬2C, IP, DO, RS-232, 内存分配；
43.    FPGA控制多路开关MUX；
52.    采样为非同步采样, 多路开关轮换有时间间隔；

# Flash

46.    Flash芯片块擦除和写入时应留有余量；

# 守护进程

4.    MZK100是调度监控程序, 控制各个进程的运行；
48.    看门狗使能, 应用程序才使能, 1.7s不喂狗设备就复位, 拔掉短路块才可维护, 这样应用程序就不执行了, 方便出错后替换程序；
49.    MZK600负责喂狗；
1.    DSP进程存在DSP芯片中？AI进程存在CPU中？
不论是CPU的还是DSP的程序代码都存储在FLASH中, 运行时载入到各自的内存中, CPU的内存是SDRAM、
DSP包含80K字节的RAM, 可以储存32K的数据及48K的程序代码DSP的运行程序代码储存于主电路的闪烁存储器, 在系统上电初始化时, 由主CPU通过DSP的DMA口载入

# 实时操作系统


# 中断服务程序
