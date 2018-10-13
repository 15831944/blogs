# 执行模式 Execution Mode

1. RUN
2. VLPR, very-low-power modes

# 定时器/脉冲宽度调制模块 Timer/PWM Module (TPM)

1. 设备包含3个低功耗 TPM 模块实例

1. TPM0, 6个通道, 目前用于延时读取 Flash 的是否写入成功的状态
2. TPM1, 2个通道, 用于
3. TPM2, 2个通道,

```
SIM_SOPT2[TPMSRC]		// 内部时钟源选择
SIM_SOPT4[TPMxCLKSEL]	// 外部时钟源选择
TPM_SC[CMOD]=1x			// 外部时钟模式(全部)
TPMx_CONF[TRGSEL]		// 外部触发输入源选择(每个)
TPMx_CONF[GTBEEN]		// 全局时间基使能, TPM1 用作全局时间
CMOD[1:0]				// 外部输入信号
CMOD[1:0]				// TPM counter clock domain
PS[2:0]					// 分频
SC[CPWMS] = 0			// Up counting
SC[CPWMS] = 1			// Up-down counting
CONF[GTBEEN] = 1		// global time base is enabled
```

## 时钟源 clock source

1. 3个 TPM 共用一个时钟源

内部时钟模式 Internal clock mode, TPM Counter Clock, Internal clocks

1. OSCERCLK
2. MCGIRCLK, 8 MHz
3. MCGPCLK, 48 MHz

外部时钟模式 external clock mode, External Source, I/O interface clocks

1. TPM_CLKIN0
2. TPM_CLKIN1

# 触发器 Trigger

1. 每个 TPM 各有1个外部触发输入源, 用于启动 start 或重载 reload 计数器

# 全局时间基 Global timebase

1. 每个 TPM 各有1个全局时间基

# 中断 TPM Interrupts

1. 多个中断源进行"或"操作生成一个对中断控制器的请求, 通过读 TPM 状态寄存器来确定是哪个中断源

1. Timer Overflow Interrupt
2. Channel (n) Interrupt

# 通道模式 channel mode

1. 每个通道是1个 I/O 引脚

1. input capture, 事件发生时将当前计数值存入寄存器
2. output compare, 计数值匹配寄存器值时进行通道输出
3. edge-aligned PWM mode, EPWM Mode, period = MOD + 1, pulse width = CnV
4. center-aligned PWM mode, CPWM Mode, period = 2 × MOD, pulse width = 2 × CnV, up-down counting mode

1. 第1个是输入模式, 后3个都是输出模式
2. 前3个都是 up counting 模式, 第4个是 up-down counting 模式

1. interrupt request
2. DMA request

# 操作模式

1. debug mode
2. doze mode
3. stop mode

# 计数器 counter

1. free-running counter
2. modulo counter

counting method

1. up counting
2. up-down counting

Trigger

1. start
2. reload
3. pause

# 信号 Signal

1. TPM_EXTCLK, 输入引脚, 输入信号必须小于 TPM counter clock frequency 的一半
2. TPM_CHn, TPM 通道 I/O 引脚

# TPM 寄存器 Registers

1. TPM0_SC: 模块的状态和控制位, DMA, TOF, TOIE, CPWMS, CMOD, PS
2. TPM0_CNT: 计数值
3. TPM0_MOD: 模值, 溢出值

4. TPM0_C0SC: 通道的状态和控制位, CHF, CHIE, MSB, MSA(通道模式选择), ELSB, ELSA(控制通道引脚), DMA
5. TPM0_C0V: 计数值(输入模式)或匹配值(输出模式)

6. TPM0_STATUS: 为编程方便提供的状态标志的副本, 6个 CHF 位, 1个 TOF 位,
7. TPM0_POL: 各通道的输入输出优先级
8. TPM0_CONF: TRGSEL, TRGSRC, TRGPOL, CPOT, CROT, CSOO, CSOT, GTBEEN, GTBSYNC, DBGMODE, DOZEEN

# 时钟域 Clock domains

1. bus clock
2. TPM counter clock, 作用于多个 TPM 实例

# 疑问

domain
half frequency

# 编程实例

1. 在 fsl_clock_manager 组件中配置 TPM 内部时钟源为 8 MHz 的 MCGIRCLK 时钟
