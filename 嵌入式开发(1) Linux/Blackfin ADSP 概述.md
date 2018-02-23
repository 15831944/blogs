# 数据类型

1. char, short, int, long, float, double, fract16, fract32
2. 只支持最高32位的定点运算, 浮点运算即64位运算需通过软件转换来实现
3. volatile 会禁用编译器的"数据流分析", 不做缓冲值的优化, 用于硬件寄存器, 多任务共享的标志变量, 中断服务程序中的变量(用于通知其他程序某外部事件发生)
4. C/C++ 扩展关键字和库函数以双下划线开头

fract 分数类型

1. fract16 本质是16位 short 类型, fract32 本质是32位 int 类型, 存储同整型, 只是解释的方式不同, 使用时需要包含 fract.h 头文件
2. fract16 的取值范围是 [ (-2^15) / 2^15, (2^15 - 1) / 2^15), 分辨率是 1 / 2^15, 即 short 类型等比缩小 2^15 倍
3. 数据归一化:

# 关键字

1. inline 用于内联函数
2. asm 用于内嵌汇编语言
3. section 用于指定数据的存储器位置
4. restrict 说明该指针是访问其指向内容的唯一途径, 不能使用别名, 两个不同的受限指针不能指向同一个对象, 即一个对象只能有一个引用?
5. buildin 用于内置函数

# 编译器内置函数

1. 编译器内置函数(Compiler Builtin Function)主要针对一些常用操作, 其实现大多与处理器硬件电路相关, 采用汇编语言编写,

```
	sysreg_read(reg_CYCLES);	// 访问外设寄存器, 获取系统时钟周期
```

# 运行时环境

1. 系统复位跳转到开始地址后要指定的代码称为 CRT(C/C++ Run-time headers), 可自行实现, 默认路径为 Blackfin/lib/src/libc/crt/basiccrt.s

# 运行时库

1. DSP 运行时库支持很多通用 DSP 算法: 滤波, FFT, 矢量和矩阵函数, 数学函数, 窗函数

# 数字滤波

```
// fir_init 函数原型
fir_init(	fir_state_fr16	state,		// 得到的初始状态
			fract16			coefs[],	// 滤波器初始状态, 数组长度=阶数+1
			fract16			*delay,		// 线性缓冲区首地址, 数组长度=阶数+1
			int				NUM_TAPS	// 滤波器阶数+1
			int				index);		// 内插或抽取索引号 interpolation / decimation index, 用于 fir_interp 或 fir_decima 函数

// fir_init 函数实现为宏
#define fir_init(state, coeffs, delay, ncoeffs, index)	\
			(state).h = (coeffs);	\	// 系数
			(state).d = (delay);	\	// 延时
			(state).p = (delay);	\	// 读写指针
			(state).k = (ncoeffs);	\	// 系数个数
			(state).l = (index)			// 内插或抽取索引号

// fir_fr16 函数原型
fir_fr16(	fract16			*in,		// 输入信号缓冲区首地址, 数组长度为 VEC_SIZE
			fract16			*out,		// 输出信号缓冲区首地址, 数组长度为 VEC_SIZE
			int				VEC_SIZE,	// 每次参与录波数据长度, 即缓冲区长度
			fir_state_fr16	*state);	// 初始状态, 由 fir_init 函数获取

Blackfin/lib/src/libdsp/fir_fr16.asm

```

# 参考

compiler and library manual for blackfin processors
device drivers and system services manual for blackfin processors
