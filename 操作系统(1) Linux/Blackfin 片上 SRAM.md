1. DSP 和 SRAM 间采用 DMA 方式通信, 对于动态申请的内存, SRAM 和 主存间拷贝数据应使用 dma_memcpy 函数
47.    程序中SRAM无内存读写保护机制；

# 高端绿色存储

单独的 SRAM 芯片, SRAM 在高地址空间, 因此叫高端

high-end storage

sram 中

# 如何避免写冲突

头信息中记录文件个数，写入是先添加到队列，按顺序存入
