# 寄存器

寄存器是有限存储容量的高速存储部件, 是CPU内部存储单元, 通常由触发器组成, 可用来暂存指令, 数据和位址等

1. 内部寄存器: 不能被外部电路或软件访问，只是为内部电路的实现存储功能或满足电路的时序要求。
2. 接口寄存器: 可以同时被内部电路和外部电路或软件访问，CPU中的寄存器就是其中一种，作为软硬件的接口，为广泛的通用编程用户所熟知。

1. 累加器(Accumulator, ACC): 累加器A专门用来存放操作数或运算结果, 在CPU执行某种运算前, 两个操作数中的一个通常应放在累加器A中, 运算完成后累加器A中便可得到运算结果
2. 指令寄存器(Instruction Register, IR): 用于储存现在正在被运行的指令
3. 程序计数器(Program Counter, PC): 指令指针, 用于存放下一条指令所在单元的地址

# ALU Arithmetic & logical Unit 算数逻辑单元

# 参考

1. [算术逻辑单元](http://baike.baidu.com/link?url=MbgHy_z7uFnQ-zjwErxuO4p7fEW6KOLI6oCGiP5GN-v9zhBloo4FIg72GpZFyx2wyY3q0HrnW8TVxAhBNPvodPnnMNCanLKzOp65VT3ETRJ6NJR5sfpnwx8StVoeEwsOgktOstx3X6hW2WYX-biITEdzzFrXZmNdsAxydiTD8x1ynw-sf3bvXdp9kLU-9SFl)
