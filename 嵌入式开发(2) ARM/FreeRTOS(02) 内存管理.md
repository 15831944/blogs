# 内存管理 Heap Memory Management

1. 内存分配算法可移植

```
reeRTOS\Source\Portable\MemMang\heap_x.c
pvPortMalloc()
vPortFree()
```

整个内存看作数组

任务控制块(TCB)
任务栈空间

最佳匹配算法
