# 线程属性变量

## 线程作用域

PTHREAD_PROCESS_SHARE		多进程可见
PTHREAD_PROCESS_PRIVATE		仅支持单进程

## 线程堆栈大小

pthread_attr_setstacksize(&thrd_attr_p, 16*1024);	// 16MB
