1. DSP 和 SRAM 间采用 DMA 方式通信, 对于动态申请的内存, SRAM 和 主存间拷贝数据应使用 dma_memcpy 函数
