# CPU的硬件组成：

算术逻辑单元：
程序运算与逻辑判断（程序执行的部分）
控制单元：
协调各组件与各单元间的工作（控制输入流入内存，经过运算再流出内存再到输出设备）

# CPU的指令集：

精简指令集（Reduced Instruction Set Computing, RISC）
复杂指令集（Complex Instruction Set Computing, CISC）

# 容量单位：

大小用2进制，频率用10进制，传输速度用bit，硬盘用10进制

# Intel的CPU架构的主板上的总线芯片组分为2个桥接器：

北桥（系统总线）：
负责连接速度较快的CPU、内存与显卡等组件
南桥（I/O总线）：
负责连接速度较慢的周边接口，包括硬盘、USB、网卡等

# CPU的主频（外频＊倍频）：

外频（可以超频）：
CPU与外部组件进行数据传输／运算时的速度
倍频：
CPU内部用来加速工作性能的一个倍数

# 总线的频宽和CPU的字组大小（32位或64位）

一般多少位的总线就配多少位的CPU，但后者也可小于前者
总线频宽(每秒传送的最大数据量)＝前端总线(Front Side Bus, FSB)速度＊总线宽度
字组大小(word size, CPU每次能够处理的数据量)
对于外频为1600MHz的总线，内存与北桥的频宽为：
1600MHz＊64bit＝1600MHz＊8Bytes＝12.8GB/s

# Intel的x86架构的CPU的等级（分等级是因为引脚定义不同，软件向下兼容）

字母 i 代表兼容性，而x86_64中的字母 x 代表不确定，是i3 i5 i7 的统称，因为这三者的引脚定义不同
i386
i586 Intel Pentium MMX
i686 Intel Celeron
x86_64 Intel Core i3 i5 i7

# 内存（主要组件为动态随机访问内存，Dynamic Random Access Memory, DRAM）

不同类型的内存的供电电压不同，因此不兼容
SDRAM (synchronous dynamic random access memory)
DDR SDRAM (double data rate SDRAM)

对于外频为200MHz的DDR，其频率为400MHz，频宽为400*8=3.2GB/s
利用双通道设计是两块64位的内存组合成一块128位的内存

# CPU二级缓存 L2 Cache (Static Random Access Memory, SRAM)

内存的速度应与CPU的外频一致，二级缓存的速度应与CPU的主频一致

# 显卡

GPU
显存：每个像素占用3字节
规格：PCI AGP PCI-Express 接口
外部接口：VGA PIC HDMI

# 硬盘

硬盘可以直接用磁头读写，因此需要驱动器 控制器
闪存不能直接读写，因此需要控制器
组成：
扇区sector 512字节
磁道track
盘片
柱面cylinder
磁头header
容量计算：
磁头＊柱面／磁头＊扇区／柱面＊512字节／扇区
磁头＊柱面＊扇区＊512
传输接口：
IDE Integrated Drive Electronics 主从架构
SATA Serial ATA Serial Advanced Technology Attachment
SCSI

# 网卡 声卡 特殊功能卡（USB控制卡、磁盘阵列卡）
PCI接口

芯片组（主板上的北桥）

集成型芯片组
独立型芯片组

设备I/O地址
IRQ中断

CMOS：
记录主板上面的重要参数，包括系统时间、CPU电压与频率、各项设备的I/O地址与IRQ中断
BIOS：
写入到主板上某一块闪存或EEPROM的程序，它可以在开机的时候执行，以加载CMOS当中的参数，并尝试调用存储设备中的开机程序，进一步进入操作系统当中。

PS/2接口
USB接口
声音输出、输入与麦克风
RJ-45接口
com1
LPT1
20pin
24pin
