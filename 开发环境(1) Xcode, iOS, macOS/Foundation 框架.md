# 值对象 Value Objects

| Class                  | Subclass       | Subclass        |
| ---------------------- | -------------- | --------------- |
| NSAffineTransform      |                |                 |
| NSCalendar             |                |                 |
| NSCache                |                |                 |
| NSData                 | NSMutableData  | NSPurgeableData |
| NSDate                 | NSCalendarDate |                 |
| NSDateComponents       |                |                 |
| NSDecimalNumberHandler |                |                 |
| NSLocale               |                |                 |
| NSNull                 |                |                 |
| NSTimeZone             |                |                 |
| NSValue                | NSNumber       | NSDecimalNumber |
| NSValueTransformer     |                |                 |

# NSData 类

1. NSData 类用于包装数据，以便在网络数据通信时进行读写
2. NSData 类的数据为二进制形式，这种形式屏蔽了数据之间的差异，便于进行读取
3. 文本，音频，图像都可以使用 NSData 进行处理

# XML

| Class                                    | Subclass                                            |
| ---------------------------------------- | --------------------------------------------------- |
| NSXMLNode(OS X)                          | NSXMLDocument, NSXMLDTD, NSXMLDTDNode, NSXMLElement |
| NSXMLParser                              |                                                     |

# 字符串 Strings

| Class              | Subclass                           |
| ------------------ | ---------------------------------- |
| NSAttributedString | NSMutableAttributeString           |
| NSCharacterSet     | NSMutableCharacterSet              |
| NSString           | NSMutableString                    |
| NSFormatter        | NSDateFormatter, NSNumberFormatter |
| NSScanner          |                                    |
| NSSortDescriptor   |                                    |

# NSSttring

```
[str length];								// 字符串长度
[NSString stringWithUTF8String:str]			// C风格字符串转换为OC风格字符串
[str UTF8String]							// OC风格字符串转换为C风格字符串
NSString *str = @"string";					// 在栈中实例化字符串
NSString *str = [[NSString alloc] init];	// 在堆中实例化字符串
NSString *str2 = [str1 lowercaseString];	// 转换为小写
NSString *str2 = [str1 uppercaseString];	// 转换为大写
BOOL hasPreFix = [str hasPrefix:@"www"];	// 字符串前缀
BOOL hasSufFix = [str hasSuffix:@"com"];	// 字符串后缀
[str1 isEqualToString:str2]					// 字符串相等
NSComparisonResult							// 字符串比较
NSString *str3 = [str1 stringByAppendingString:str2];				// 拼接字符串
NSArray *strArray = [str1 componentsSeparatedByString:@", "];		// 字符串分割
NSString *str = [NSString stringWithFormat:@"a = %d b = %d", a, b];	// 格式化字符串
NSString *str1 = [str substringWithRange:range];	// 按范围截取字符串
NSString *str2 = [str substringFromIndex:3];		// 从指定索引号截取字符串
NSString *str3 = [str substringToIndex:7];			// 截取字符串至指定索引号
[str characterAtIndex:i];							// 从字符串中提取字符
NSRange range = [str rangeOfString:@"substr"];		// 字符串查找, 返回子串所在范围(位置和长度)
NSString *str1 = [str stringByReplacingCharactersInRange:NSMakeRange(0, 5) withString:@"你好"];	// 按范围替换字符串中的字符
NSString *str2 = [str stringByReplacingOccurrencesOfString:@"hello" withString:@"你好"];			// 替换字符串的指定的已存在部分
NSURL *httpURL = [NSURL URLWithString:str];
NSURL *fileURL = [NSURL fileURLWithPath:str];
NSString *httpStr = [NSString stringWithContentsOfURL:httpURL encoding:NSUTF8StringEncoding error:nil];		// 读取网络文件
NSString *fileStr = [NSString stringWithContentsOfFile:@"/Users/username/Documents/demo.txt" encoding:NSUTF8StringEncoding error:nil];	// 读取本地文件
BOOL rtn = [str writeToURL:@"/Users/username/Documents/demo.txt" atomically:YES encoding:NSUTF8StringEncoding error:nil];	// 将指定字符串写入文件
```

# NSMutableString

```
NSMutableString *str = [[NSMutableString alloc] initWithCapacity:10];	// 实例化可变字符串
[str setString:@"hello"];			// 初始化可变字符串
[str appendString:@" world"];		// 使用字符串追加可变字符串
[str appendFormat:@" %d", a];		// 以指定格式追加字符串
[str replaceCharactersInRange:range withString:@"substr"];	// 按范围替换字符串中的字符
[str insertString:@"substr" atIndex:6];			// 在指定位置插入字符串
[str deleteCharactersInRange:range];			// 按范围删除字符串中的字符
```

# 集合 Collections

| Class                    | Subclass               | Subclass     |
| ------------------------ | ---------------------- | ------------ |
| NSArray                  | NSMutableArray         |              |
| NSDictionary             | NSMutableDictionary    |              |
| NSEnumerator             | NSDictionaryEnumerator |              |
| NSHashTable(OS X)        |                        |              |
| NSIndexPath              |                        |              |
| NSIndexSet               | NSMutableIndexSet      |              |
| NSMapTable(OS X)         |                        |              |
| NSPointerArray(OS X)     |                        |              |
| NSPointerFunctions(OS X) |                        |              |
| NSSet                    | NSMutableSet           | NSCountedSet |

# NSArray

1. 数组的元素只能是对象指针, 由于都是指针类型, 同一个数组可以存储不同类型的对象, 数组的内存空间依然连续

```
NSArray *array = [[NSArray alloc] initWithObjects:@"1", @"2", @"3", @"4", @"5", nil];	// 在堆中实例化数组
int count = (int) array.count;					// 数组长度
BOOL ishas = [array containsObject:@"2"];		// 数组元素判断
str = [array lastObject];						// 数组最后一个元素
str = [array firstObject];						// 数组第一个元素
str = [array objectAtIndex:3];					// 按索引号访问数组元素
int index = (int) [array indexOfObject:@"3"];	// 查找数组元素的索引位置
for (int i = 0; i < array.count; i++)			// 使用 for 循环遍历数组
{
	NSString *str = [array objectAtIndex:i];
	NSLog(@"array[%d] = %@", i, str);
}
for (NSString *str in array)				// 使用 for in 快速枚举(需要数组元素类型一致)遍历数组
{
	NSLog(@"array = %@", str);
}
NSEnumerator *enumerator;					// 使用枚举器(迭代器)遍历数组
enumerator = [array objectEnumerator];
id thing;
while (thing = [enumerator nextObject])
{
	NSLog(@"%@",thing);
}
```

# NSMultableArray

```
addObject				// 添加数组元素对象
addObjectsFromArray		// 从数组添加
removeAllObjects		// 移除所有对象
removeLastObject		// 移除最后一个对象
removeOjbect			// 移除指定对象
removeOjbectAtIndex		// 按索引位置移除对象
exchangeObjectAtIndex:(NSUInteger) withObjectAtIndex:(NSUInteger)	// 交换数组元素位置
```

# NSDictionary

1. 字典对象的存储内存空间不连续, 使用键值对(KVC, key value coding, 键值编码)进行访问
2. 添加或删除数组或字典的元素时，count 会随之变化
3. 对象释放后，每个值都会 release

```
NSDictionary *dict1 = [NSDictionary dictionaryWithObject:@"1" forKey:@"a"];		// 使用指定键值对实例化字典对象
NSDictionary *dict2 = [NSDictionary dictionaryWithObjects:[NSArray arrayWithObjects:@"1", @"2", @"3", nil] forKeys:[NSArray arrayWithObjects:@"a", @"b", @"c", nil]];		// 使用数组指定的键值对实例化字典对象
NSDictionary *dict3 = @{@"a":@"1", @"b":@"2", @"c":@"3"};		// 使用初始化列表实例化字典对象
int count = (int)[dict2 count];								// 字典元素数
NSString *value1 = [dict2 valueForKey:@"b"];		// 按键查找值
NSString *value2 = [dict2 objectForKey:@"b"];		// 按键查找对象
NSArray *allValues = [dict2 allValues];				// 将所有值输出到数组中
NSArray *allKeys = [dict2 allKeys];					// 将所有键输出到数组中
NSArray *array = [dict2 objectsForKeys:[NSArray arrayWithObjects:@"a", @"b", @"d", nil] notFoundMarker:@"not found"];	// 按数组指定的键查找, 并将结果值输出到数组中
for (NSString *key in dict2)			// 使用快速枚举遍历字典
{
    NSLog(@"%@ = %@", key, [dict2 objectForKey:key]);
}
NSEnumerator *en = [dict2 keyEnumerator];	// 使用枚举器遍历字典
id key = nil;
while (key = [en nextObject])
{
    NSLog(@"key = %@", key);
}
```

# NSMutbaleDictionary

```
NSMutableDictionary *dict = [[NSMutableDictionary alloc] init];
[dict setObject:@"1" forKey:@"a"];
[dict setObject:@"2" forKey:@"b"];
[dict setObject:@"3" forKey:@"c"];
[dict setObject:@"4" forKey:@"d"];
NSLog(@"dict = %@", dict);
[dict removeObjectForKey:@"a"];
NSLog(@"dict = %@", dict);
[dict removeObjectsForKeys:[NSArray arrayWithObjects:@"b", @"d", nil]];
NSLog(@"dict = %@", dict);
[dict removeAllObjects];
NSLog(@"dict = %@", dict);
```


# Predicates

| Class              | Subclass                                   |
| ------------------ | ------------------------------------------ |
| NSExpression       |                                            |
| NSPredicate        | NSComparisonPredicate, NSCompoundPredicate |

# 操作系统服务 Operating-System Services

| Class                |
| -------------------- |
| NSError              |
| NSHost               |
| NSNetService         |
| NSNetServiceBrowser  |
| NSOrthography        |
| NSProcessinfo        |
| NSRunLoop            |
| NSSpellServer(OS X)  |
| NSTextCheckingResult |
| NSTimer              |
| NSUserDefaults       |

## 文件系统 File System

| Class                                    | Subclass                      |
| ---------------------------------------- | ----------------------------- |
| NSBundle                                 |                               |
| NSFileHandle                             |                               |
| NSFileManager                            |                               |
| NSMetadataItem(OS X)                     |                               |
| NSMetadataQuery(OS X)                    |                               |
| NSMetadataQueryAttributeValueTuple(OS X) |                               |
| NSMetadataQueryResultGroup(OS X)         |                               |
| NSStream                                 | NSInputStream, NSOutputStream |

## URL

| Class                       | Subclass            |
| --------------------------- | ------------------- |
| NSCachedURLResponse         |                     |
| NSHTTPCookie                |                     |
| NSHTTPCookieStorage         |                     |
| NSURL                       |                     |
| NSURLAuthorizationChallenge |                     |
| NSURLCache                  |                     |
| NSURLConnection             |                     |
| NSURLCredential             |                     |
| NSURLCredentialStorage      |                     |
| NSURLDownload               |                     |
| NSURLProtectionSpace        |                     |
| NSURLProtocol               |                     |
| NSURLRequest                | NSMutableURLRequest |
| NSURLResponse               | NSHTTPURLResponse   |

## 进程间通信 Interprocess Communication

1. 代表不同的系统端口, 套接字, 名字服务器，用于实现底层的IPC
2. NSPipe 代表一个BSD管道，即一种进程间的单向通讯通道

| Class                  | Subclass                                                               |
| ---------------------- | ---------------------------------------------------------------------- |
| NSPipe                 |                                                                        |
| NSPort                 | NSMachPort, NSMessagePort, NSSocketPort(OS X)                          |
| NSPortMessage(OS X)    |                                                                        |
| NSPortNameServer(OS X) | NSMachBootstrapServer, NSMessagePortNameServer, NSSocketPortNameServer |

## 线程和子任务 Locking/Threading

1. NSThread 类创建多线程的程序
2. 各种锁（lock）类则为彼此竞争的线程在访问进程资源时提供各种控制机制
3. 通过 NSTask，您的程序可以分出一个子进程来执行其它工作或进行进度监控

| Class             | Subclass                                |
| ----------------- | --------------------------------------- |
| NSConditionLock   |                                         |
| NSDistributedLock |                                         |
| NSLock            |                                         |
| NSOperation       | NSBlockOperation, NSInvocationOperation |
| NSOperationQueue  |                                         |
| NSRecursiveLock   |                                         |
| NSTask            |                                         |
| NSThread          |                                         |

# 消息 Notifications

| Class                | Subclass                        |
| -------------------- | ------------------------------- |
| NSNotification       | NSDistributedNotificationCenter |
| NSNotificationCenter |                                 |
| NSNotificationQueue  |                                 |

# 归档和序列化 archiving and Serialization

| Class                                    | Subclass                                                                  |
| ---------------------------------------- | ------------------------------------------------------------------------- |
| NSCoder                                  | NSArchiver, NSKeyedArchiver, NSKeyedUnarchiver, NSPortCoder, NSUnarchiver |
| NSPropertyListSerialization              |                                                                           |

# OC语言服务 Objective-C Language Services

| Class                                    | Subclass                 |
| ---------------------------------------- | ------------------------ |
| NSAssertionHander                        |                          |
| NSAutoreleasePool                        |                          |
| NSClassDescription                       | NSScriptClassDescription |
| NSException                              |                          |
| NSGarbageCollector(OS X)                 |                          |
| NSInvocation                             |                          |
| NSMethodSignature                        |                          |
| NSUndoManager                            |                          |

# Scripting

| Class                      |
| -------------------------- |
| NSAppleEventDescriptor     |
| NSAppleEventManager        |
| NSAppleScript              |
| NSPositionalSpecifier      |
| NSScriptCoercionHandler    |
| NSScriptCommand            |
| NSScriptCommandDescription |
| NSScriptExecutionContext   |
| NSScriptObjectSpecifier    |
| NSScriptSuiteRegistry      |
| NSScriptWhoseTest          |

# Distributed Objects

| Class                  |
| ---------------------- |
| NSConnection           |
| NSDistantObjectRequest |
| NSDistantObject        |
| NSProtocolChecker      |

# 参考

[iOS 基础入门之 Foundation 框架初体验](http://www.imooc.com/learn/420)
