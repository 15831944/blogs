# 函数参数构造 Function Argument Construction

```
#include <stdio.h>
int passthrough();
int average();

int main(int argc,char *argv[])
{
   int result;
   result = passthrough();
   printf(“result = %d\n”, result);
   return (0);
}

int passthourgh(int a, int b, int c)
{
	void *record;
	void *playback;
	void (* fn)() = (void (*) ()) average;		//指向函数的指针

	record   = __builtin_apply_args();	//构造调用此函数的父函数的参数，这些参数都是保存在函数栈中的
	playback = __builtin_apply(fn, record, 128);	//调用相关函数，参数: 函数指针, 构造参数的函数的返回的指针, 建立一个新的栈而从旧栈中复制数据的尺寸
	__builtin_return(playback);		//获得相关函数的返回, 参数: 调用相关函数的函数的返回指针
}

int average(int a, int b, int c)
{
   return (a + b + c) / 3;
}
```
