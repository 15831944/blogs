# 1. 含义

`#pragma` 的字面含义是杂注，编译指示

`#pragma` 指令对每个编译器给出了一个方法，在保持与 C 和 C++ 语言完全兼容的情况下，给出主机或操作系统专有的特征

依据定义，编译指示是机器或操作系统专有的，且对于每个编译器都是不同的

# 2. 作用

1. 设定编译器的状态

2. 指示编译器完成一些特定的动作

# 3. 参数

## 1. message

message 参数能够在编译信息输出窗口中输出相应的信息，这对于源代码信息的控制是非常重要的。

其使用方法为：

`#pragma message("消息文本")`

当编译器遇到这条指令时就在编译输出窗口中将消息文本打印出来。

当我们在程序中定义了许多宏来控制源代码版本的时候，我们自己有可能都会忘记有没有正确的设置这些宏，此时我们可以用这条指令在编译的时候就进行检查。

假设我们希望判断有没有在源代码的什么地方定义了 `_X86` 这个宏，可以用下面的方法：

```
#ifdef _X86
#pragma message("_X86 macro activated!")
#endif
```

当我们定义了 `_X86` 这个宏以后，应用程序在编译时就会在编译输出窗口里显示

```
In file included from main.c:10:0:
preprocess_pragma.h:6:9: note: #pragma message: _X86 macro activated!
 #pragma message("_X86 macro activated!")
```

## 2. code_seg

code_seg 参数能够指定函数在目标文件(*.obj)中存放的节，当我们开发驱动程序的时候就会使用到它

观察目标文件可以使用 VC 自带的 dumpbin 工具或 readelf 工具

函数在目标文件中默认(code_seg 没有带参数)的存放节为`.text`

其调用形式为：

`#pragma code_seg(["section-name"[,"section-class"]])`

`#pragma code_seg([[{push | pop},][identifier,]]["segment-name"[, "segment-class"])`

1. push (可选参数) 

	将一个记录(标识符或者节名)压入内部编译器的栈中

2. pop(可选参数) 

	将一个记录(标识符或者节名)从栈顶端弹出

3. identifier (可选参数) 

	当使用push指令时, 为压入堆栈的记录指派的一个标识符，当该标识符被删除时，和其相关的堆栈中的记录将被弹出堆栈

4. "segment-name" (可选参数) 

	表示函数存放的节名

例如:
```
//默认情况下, 函数被存放在.text节中
#pragma  code_seg() 
void func1() {                   // stored in .text
}
//将函数存放在.my_data1节中
#pragma code_seg(".my_data1")
void func2() {                   // stored in my_data1
}
//将函数放入.my_data2节中，标识符为 r1
#pragma code_seg(push, r1, ".my_data2")
void func3() {                   // stored in my_data2
}
//将此部分代码放入分页内存中运行
#pragma  code_seg(“PAGE”)
void func4() {
}
//加载到 INIT 内存区域中，成功加载后，可以退出内存
#pragma  code_seg("INIT")
void func5() {
}
int main() {
}
```

## 3. once

在头文件的最开始加入这条指令就能够保证头文件被编译一次

` #pragma once`

## 4. hdrstop

#pragma hdrstop 表示预编译头文件到此为止，后面的头文件不进行预编译。

BCB可以预编译头文件以加快链接的速度，但如果所有头文件都进行预编译又可能占太多磁盘空间，所以使用这个选项排除一些头文件。

有时单元之间有依赖关系，比如单元A依赖单元B，所以单元B要先于单元A编译。

你可以用 `#pragma startup` 指定编译优先级，如果使用了 `#pragma package(smart_init)` ，BCB就会根据优先级的大小先后编译。

## 5. warning

该指令允许有选择性的修改编译器的警告消息的行为

指令格式如下:

```
#pragma warning( warning-specifier : warning-number-list [; warning-specifier : warning-number-list...]

#pragma warning( push[ ,n ] )

#pragma warning( pop )
```

主要用到的警告表示有如下几个:

* once:只显示一次(警告/错误等)消息

* default:重置编译器的警告行为到默认状态

* n: 1,2,3,4共四个警告级别

* disable:禁止指定的警告信息

* error:将指定的警告信息作为错误报告

举例：

```
#pragma warning( disable : 4507 34; once : 4385; error : 164 )


#pragma warning(disable:4507 34)   // 不显示4507和34号警告信息
#pragma warning(once:4385)         // 4385号警告信息仅报告一次
#pragma warning(error:164)         // 把164号警告信息作为一个错误
```

#pragma warning( push )			// 保存所有警告信息的现有的警告状态

#pragma warning( push, n)		// 保存所有警告信息的现有的警告状态，并且把全局警告等级设定为n

#pragma warning( pop )		// 向栈中弹出最后一个警告信息，在入栈和出栈之间所作的一切改动取消

例如：

```
#pragma warning( push )
#pragma warning( disable : 4705 )
#pragma warning( disable : 4706 )
#pragma warning( disable : 4707 )
#pragma warning( pop )
```

在这段代码的最后，重新保存所有的警告信息(包括4705，4706和4707)

## 6. comment

该指令的格式为

`#pragma comment( "comment-type" [, commentstring] )`

该指令将一个注释记录放入一个对象文件或可执行文件中

comment-type(注释类型):可以指定为五种预定义的标识符的其中一种

五种预定义的标识符为:

1. compiler

	将编译器的版本号和名称放入目标文件中,本条注释记录将被编译器忽略, 如果你为该记录类型提供了 commentstring 参数, 编译器将会产生一个警告, 例如:
	
	`#pragma comment( compiler )`

2. exestr

	将 commentstring 参数放入目标文件中,在链接的时候这个字符串将被放入到可执行文件中,当操作系统加载可执行文件的时候,该参数字符串不会被加载到内存中.但是,该字符串可以被 dumpbin 之类的程序查找出并打印出来,你可以用这个标识符将版本号码之类的信息嵌入到可执行文件中!

3. lib

	这是一个非常常用的关键字,用来将一个库文件链接到目标文件中常用的 lib 关键字，可以帮我们连入一个库文件。例如:
	
	`#pragma comment(lib, "user32.lib")`
	
	该指令用来将 user32.lib 库文件加入到本工程中
	
	相对位置的加载实例：
	
	`#pragma comment(lib, ".\\XCGUI\\XCGUId.lib")`

4. linker

	将一个链接选项放入目标文件中,你可以使用这个指令来代替由命令行传入的或者在开发环境中设置的链接选项, 你可以指定 /include 选项来强制包含某个对象,例如:

	`#pragma comment(linker, "/include:__mySymbol")`
	你可以在程序中设置下列链接选项
	/DEFAULTLIB
	/EXPORT
	/INCLUDE
	/MERGE
	/SECTION
	这些选项在这里就不一一说明了,详细信息请看msdn!

5. user

	将一般的注释信息放入目标文件中, commentstring 参数包含注释的文本信息,这个注释记录将被链接器忽略.例如:
	
	`#pragma comment( user, "Compiled on " __DATE__ " at " __TIME__ )`

## 7. pack

# 4. 举例

```
#pragma always_inline	// 始终作为内联函数进行替换

#pragma pack(2)			//将该格式按WORD对齐

#pragma no_aliass
```

# 5. 参考

[ 关于#pragma code_seg](http://blog.csdn.net/whatday/article/details/7100855)

[#pragma详细解释](http://blog.csdn.net/nodeman/article/details/45477067)
