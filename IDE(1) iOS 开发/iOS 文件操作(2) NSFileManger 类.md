## 1. NSFileManger 类

对文件本身的创建和删除

### 1. 创建文件夹

withIntermediateDirectories 表示是否覆盖

如果选择 NO, 若文件夹已经存在，则会调用失败

如果选择 YES, 若文件夹已经存在，则不会删除原来的内容

```
NSString *homePath = NSHomeDirectory();
    NSString *filePath = [homePath stringByAppendingString:@"/wanghuiyong"];
    NSFileManager *myManger = [NSFileManager defaultManager];
    BOOL rtn = [myManger createDirectoryAtPath:filePath withIntermediateDirectories:YES attributes:nil error:nil];
```

### 2. 创建文件

如果文件名之前的路径不存在，则会调用失败

```
NSString *homePath = NSHomeDirectory();
    NSString *filePath = [homePath stringByAppendingString:@"/wanghuiyong/note.txt"];
    NSFileManager *myManger = [NSFileManager defaultManager];
    BOOL rtn = [myManger createFileAtPath:filePath contents:nil attributes:nil];
```

### 3. 写入文件

```
NSString *homePath = NSHomeDirectory();
    NSString *filePath = [homePath stringByAppendingString:@"/wanghuiyong/note.txt"];
    NSString *content = @"content";
    BOOL rtn = [content writeToFile:filePath atomically:YES encoding:NSUTF8StringEncoding error:nil];
```

### 4. 文件存在判断

```
NSFileManager *myManger = [NSFileManager defaultManager];
    if ([myManger fileExistsAtPath:filePath])
        return YES;
    else
        return NO;
```

# 9. 参考

[iOS基础教程-文件操作](http://www.imooc.com/learn/655)
