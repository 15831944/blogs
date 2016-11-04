# 数据本地化

1. 图片处理
2. 个人信息处理
3. 共用信息分享

# 沙盒机制

1. iPhone 中没有 SD 卡的概念，即没有共用的闪存供应用读写
2. 不能在应用程序之间直接访问数据, 只能对应用自身创建的沙盒内的文件进行读写, 这样的一个独立的封闭的安全的空间叫做沙盒
3. 创建沙盒会自动创建沙盒路径, 删除沙盒会地洞删除沙盒路径

# 沙盒内容

每个应用的沙盒中包含3个文件夹

| name      | usage                                                                | example |
| --------- | -------------------------------------------------------------------- | ------- |
| Documents | 保存程序创建或应用浏览产生的数据文件                                       | iTunes 备份和恢复数据时会使用此目录 |
| Library   | 保存程序的默认设置或状态信息                                              | 略 |
| tmp       | 保存即时创建的临时的不需要持久化的文件, 应用关闭时自动删除, 应用不运行时由系统删除 | 略 |

1. 所谓持久化的数据一般是指保存在数据库中的数据，iOS 8 以前的沙盒路径文件还有一个fmdbDemo, 是一个 bundle 包，现在这个文件已经被分离

# 沙盒路径

1. 程序中, 路径用字符串表示
2. 对于沙盒路径和 tmp 路径，提供有 api 接口函数
3. 对于 Documents 路径 和 Library 路径，可以使用路径名称进行检索，或者使用已有的沙盒路径进行拼接

```
NSHomeDirectory();			// 获取沙盒路径, 返回路径字符串
NSTemporaryDirectory();		// 获取 tmp 路径, 返回路径字符串
NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);	// 获取 Documents 路径, 返回搜索到的指向各路径字符串的指针数组
NSSearchPathForDirectoriesInDomains(NSLibraryDirectory, NSUserDomainMask, YES);		// 获取 Library 路径, 返回搜索到的路径字符串数组
pathComponents;						// 获取路径各组成部分，包括文件名，该字符串对象方法返回存在路径组成的数组
lastPathComponent;					// 获取路径中最后一个组成部分，可以是文件名或目录名
stringByDeletingLastPathComponent;	// 删除路径中最后一个组成部分，可以是文件名或目录名
stringByAppendingPathComponent:;	// 添加路径中最后一个组成部分，可以是文件名或目录名
```

# NSFileManager

对文件本身的创建和删除

NSFileManger 的方法

1. 创建文件夹
2. 创建文件
3. 写入文件
4. 文件存在判断

# NSFileHandle

对文件内容进行读写操作

1. NSFileHandle 只能打开现成的文件，所以如果是新文件则需要 NSFileManager 先创建新文件；
2. 打开一个文件之后，就需要关闭一个文件；
3. 根据不同的要求可能要设定不同的偏移量（即光标所在位置），可以通过移动到开头或结尾，也可以先获取当前位置然后增加和减少多少字节来移动；
4. 文件路径是NSString对象，可以用 stringByAppendingPathComponent+文件全称 方法构造一个完整的文件路径；
5. 往文件里面写的内容是NSData，如果是其他的格式, 则可以用 dataUsingEncoding : NSUTF8StringEncoding 来转化成data类型；
6. 目录的写法于Linux类似，~家目录，/根目录，.当前目录，..父目录，用/表示层级等

NSFileHandle 的方法

1. 文件内容追加
2. 删除文件

# 参考

[iOS基础教程-文件操作](http://www.imooc.com/learn/655)
