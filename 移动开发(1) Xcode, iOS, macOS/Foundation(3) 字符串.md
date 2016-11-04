# NSString

1. 在栈中实例化字符串对象自动释放内存, 在堆中实例化对象需要手动释放内存
2. C 风格的字符串称为 UTF8String
3. Range 的实现为结构体, 成员为位置和长度
4. 网络路径和本地路径虽然都是 NSURL 类, 但获取的方法不同, 不能混用
5. 字符串比较较为复杂, 涉及读音等
6. 对字符串的各种操作往往返回一个新建的字符串, 而不是修改原字符串

```
NSString *str = @"string";							// 在栈中实例化字符串
NSString *str = [[NSString alloc] init];			// 在堆中实例化字符串
[str length];										// 字符串长度
[NSString stringWithUTF8String:str]					// C风格字符串转换为OC风格字符串
[str UTF8String]									// OC风格字符串转换为C风格字符串
NSString *str = [str1 lowercaseString];				// 转换为小写
NSString *str = [str1 uppercaseString];				// 转换为大写
NSString *str = [str1 substringWithRange:range];	// 按范围截取字符串
NSString *str = [str1 substringFromIndex:3];		// 从指定索引号截取字符串
NSString *str = [str1 substringToIndex:7];			// 截取字符串至指定索引号
BOOL hasPreFix = [str hasPrefix:@"www"];			// 字符串前缀
BOOL hasSufFix = [str hasSuffix:@"com"];			// 字符串后缀
[str1 isEqualToString:str2]							// 字符串相等
NSComparisonResult									// 字符串比较
[str characterAtIndex:i];							// 从字符串中提取字符
NSString *str3 = [str1 stringByAppendingString:str2];					// 拼接字符串
NSArray *strArray = [str1 componentsSeparatedByString:@", "];			// 字符串分割
NSString *str = [NSString stringWithFormat:@"a = %d b = %d", a, b];		// 格式化字符串
NSRange range = [str rangeOfString:@"substr"];							// 字符串查找, 返回子串所在范围(位置和长度)
NSString *str1 = [str stringByReplacingCharactersInRange:NSMakeRange(0, 5) withString:@"Hi"];				// 按范围替换字符串中的字符
NSString *str2 = [str stringByReplacingOccurrencesOfString:@"hello" withString:@"Hey"];						// 按已经存在的子串替换字符串中的字符
NSURL *httpURL = [NSURL URLWithString:str];																	// 获取网络路径
NSURL *fileURL = [NSURL fileURLWithPath:str];																// 获取本地路径
NSString *httpStr = [NSString stringWithContentsOfURL:httpURL encoding:NSUTF8StringEncoding error:nil];		// 读取网络文件
NSString *fileStr = [NSString stringWithContentsOfFile:fileURL encoding:NSUTF8StringEncoding error:nil];	// 读取本地文件
BOOL rtn = [str writeToURL:fileURL atomically:YES encoding:NSUTF8StringEncoding error:nil];					// 将指定字符串写入文件
```

# NSMutableString

1. 在实例化可变字符串时指定长度可以提升性能
2. 用 NSString 对象初始化 NSMutableString 对象会报类型不匹配
3. 对字符串的操作将修改原字符串, 返回的是引用
4. NSMutableString 继承自 NSString, 即可变字符串可以使用普通字符串的方法
5. 字符串替换只能按范围进行替换

```
NSMutableString *str = [[NSMutableString alloc] initWithCapacity:10];	// 实例化可变字符串
[str setString:@"hello"];												// 初始化可变字符串
[str appendString:@" world"];											// 使用字符串追加可变字符串
[str appendFormat:@" %d", a];											// 以指定格式追加字符串
[str replaceCharactersInRange:range withString:@"substr"];				// 按范围替换字符串中的字符
[str insertString:@"substr" atIndex:6];									// 在指定位置插入字符串
[str deleteCharactersInRange:range];									// 按范围删除字符串中的字符
```
