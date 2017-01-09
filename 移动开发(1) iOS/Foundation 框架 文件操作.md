# 沙盒机制

1. iOS 中没有 SD 卡的概念, 即没有共用的闪存供应用程序进行读写
2. 不能在应用程序之间直接访问数据, 只能访问应用程序自身创建的沙盒内的文件, 这样的一个独立的封闭的安全的空间叫做沙盒
3. 创建沙盒会自动创建沙盒目录结构, 删除沙盒会自动删除沙盒目录结构
4. 数据本地化的应用场景包括: 图片处理, 个人信息处理, 共用信息分享
5. 用于存储文档, 偏好设置

# 沙盒路径

1. 沙盒路径用字符串对象表示, 包括: Documents, Library, tmp 共3个目录, iOS 8 以前还有一个 fmdbDemo, 是一个 bundle 包, 现已经被分离
2. Documents, 保存应用程序创建或浏览操作产生的数据文件, iTunes 备份和恢复数据时使用此目录
3. Library, 保存应用程序的默认设置或状态信息
4. tmp, 保存临时创建的不需要持久化的文件, 应用关闭时或不运行时由系统自动删除, 持久化的数据一般是指保存在数据库中的数据
5. 对于沙盒(home)路径及 tmp 路径，可通过系统提供的 NSString 的全局函数进行获取
6. 使用系统提供的路径名称进行检索 Documents 路径 和 Library 路径，得到所有的 document 或 library 路径(应用程序中默认每种路径只有一个)
7. 对沙盒(home)路径进行拼接获取 Documents 路径 和 Library 路径

```
NSString *homeDirectoryPath = NSHomeDirectory();															// 获取 home 路径
NSString *tmpDirectoryPath = NSTemporaryDirectory();														// 获取 tmp 路径
NSArray *documentPaths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);	// 检索 Documents 路径
NSArray *libraryPaths  = NSSearchPathForDirectoriesInDomains(NSLibraryDirectory,  NSUserDomainMask, YES);	// 检索 Library 路径
NSArray *component  = [directoryPath pathComponents];									// 获取路径中各个组成部分，包含开始和结尾的斜杠
NSString *fileName  = [directoryPath lastPathComponent];								// 获取路径中最后一个组成部分
NSString *directory = [directoryPath stringByDeletingLastPathComponent];				// 删除路径中最后一个组成部分
NSString *filePath  = [directoryPath stringByAppendingPathComponent:@"fileName.txt"];	// 添加路径中最后一个组成部分
```

# NSData

1. NSData 类用于包装数据, 用于在网络数据通信时对文件进行读写, 为二进制形式, 屏蔽了数据之间的差异, 文本, 音频, 图片等都可以使用 NSData 进行处理

NSData 的数据转换

```
NSString *string = [[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding];	// NSData 转换为 NSString
NSData *data = [string dataUsingEncoding:NSUTF8StringEncoding];							// NSString 转换为 NSData
UIImage *image = [UIImage imageWithData:data];											// NSData 转换为 UIImage
NSData *data = UIImagePNGRepresentation(image);											// UIImage (png) 转换为 NSData (C 函数)
NSData *data = UIImageJPEGRepresentation(image);										// UIImage (jpeg) 转换为 NSData (C 函数)
```

# NSFileManager

1. NSFileManager 类实例化的单例模式的对象可创建和删除文件或目录, 即对文件本身进行操作

NSFileManager 的方法

```
NSFileManager *fileManager = [NSFileManager defaultManager];															// 声明 NSFileManager
BOOL *result = [fileManager createDirectroyAtPath:dirPath withIntermediateDirectories:YES attributes:nil error:nil];	// 以指定目录创建多级目录
BOOL *result = [fileManager createFileAtPath:filePath content:nil attributes:nil];										// 以指定文件路径创建文件
BOOL *exists = [fileManager fileExistsAtPath:filePath];																	// 指定路径的文件存在
BOOL *result = [fileManager removeItemAtPath:filePath error:nil];														// 删除指定目录中文件
BOOL *result = [string writeToFile:filePath automically:YES encoding:NSUTF8StringEncoding error:nil];					// 将字符串写入指定路径的文件
BOOL *result = [data   writeToFile:filePath automically:YES];															// 将数据(图片, 音乐, 文本)写入指定路径的文件
```

# NSFileHandle

1. 打开和关闭: NSFileHandle 只能操作现有的文件, 是对文件内容进行读写操作, 相当于文件对象指针(UNIX)或文件句柄(Windows), 操作前先打开文件, 并需要关闭文件
2. 文件偏移量: 可以将文件偏移量设置到文件开始或结尾, 也可以根据当前偏移量前进或后退
3. 文件读写的内容是 NSData 类的对象

NSFileHandle 的方法

```
NSFileHandle *fileHandle = [NSFileHandle fileHandleForUpdatingAtPath:filePath];	// 为更新而打开文件
[fileHandle seekToEndOfFile];		// 将文件偏移量设置到文件末尾
[fileHandle writeData:data];		// 写入数据到 fileHandle 指定的文件, 其他数据类型应先转换为 NSData 类型
[fileHandle closeFile];				// 关闭文件
```
