# RTC

实时时钟是个32位秒计数器，一次溢出时间为

4,294,967,296s = 71,582,788min = 1,193,046h = 49,710 day = 1,657 mon = 138 year > 1 century

一般我们只用其1个世纪以内，计的时年份的后2位。

时钟芯片均存在百年虫问题

时钟源是 32.768kHz 的 ERCLK32K.

RTC_TPR 每次从 32767 变到 32768 时, RTC_TSR 加 1

# Signal

```
SIM_SOPT2[RTCCLKOUTSEL] = 0		// RTC_CLKOUT 引脚输出的是 RTC 1 Hz clock, square-wave output
SIM_SOPT2[RTCCLKOUTSEL] = 1		// RTC_CLKOUT 引脚输出的是 OSCERCLK on-chip clock source
```

# Registers

1. RTC_TSR, 时间秒寄存器, 32位, 每秒加1, 计数范围 0~4,294,967,295,  给一个时间基准, 可计时138年
2. RTC_TPR, 时间除频寄存器, 低16位, 每个 32.768kHz 的时钟周期加1, 计数范围 0~32,767, 即每秒增加32768次
3. RTC_TAR, 时间闹钟寄存器, 32位, TSR 到达 TAR 中设定的时间时, 置位 SR[TAF] 标志
4. RTC_TCR, 时间补偿寄存器, CIC, TCV, CIR, TCR 还剩多少个补偿间隔, 当前间隔的补偿值, 一个补偿间隔多少秒, 补偿值
5. RTC_CR, 控制寄存器, SC2P, SC4P, SC8P, SC16P 晶振的电容大小, CLKO 时钟输出到其他外设, OSCE 振荡器使能, WPS 唤醒引脚选择, UM 升级模式, SUP 高访问权限, WPE 唤醒引脚使能, SWR 软件复位
6. RTC_SR, 状态寄存器, TCE, TAF, TOF, TIF 时间计数器使能, 时间告警标志, 时间溢出标志, 时间无效标志
7. RTC_LR, 锁定寄存器, LRL, SRL, CRL, TCL LR 本身被锁定, SR状态寄存器锁定, CR控制寄存器锁定, TCR时间补偿寄存器锁定, 用途应该就是锁定当前配置
8. RTC_IER, 中断使能寄存器, WPON 唤醒引脚打开, TSIE 时间秒中断使能, TAIE 时间闹钟中断使能, TOIE 时间溢出中断使能, TIIE 时间无效中断使能

# Time counter

1. RTC_TSR, 32-bit seconds counter, 每秒增加
2. RTC_TPR, 16-bit prescaler register, 每个时钟周期增加

# 温度自动补偿 Compensation

1. 走时精度范围 0.12~3906ppm

# 参考

1. [kinetis的RTC报警中断例程](http://blog.chinaaet.com/freetech/p/29483)
