1. NSFileHandle 只能打开现成的文件，所以如果是新文件则需要NSFileManager先创建新文件；

2. 打开一个文件就后，就需要关闭一个文件；

3. 根据不同的要求可能要设定不同的偏移量（即光标所在位置），可以通过移动到开头或结尾，也可以先获取当前位置然后增加和减少多少字节来移动；

4. 文件路径是NSString对象，可以用 stringByAppendingPathComponent+文件全称 方法构造一个完整的文件路径；

5.往文件里面写的内容是NSData，如果是其他的格式则可以用 dataUsingEncoding : NSUTF8StringEncoding 来转化成data类型；

6. 同样，目录的写法于Linux类似，~家目录，/根目录，.当前目录，..父目录，用/表示层级等。

## 2. NSFileHandle 类

对文件内容进行读写操作

### 1. 文件内容追加

```
NSString *homePath = NSHomeDirectory();
    NSString *filePath = [homePath stringByAppendingString:@"/wanghuiyong/note.txt"];
    NSFileHandle *myHandle = [NSFileHandle fileHandleForUpdatingAtPath:filePath];
    [myHandle seekToEndOfFile];
    NSString *str = @"append";
    NSData *dat = [str dataUsingEncoding:NSUTF8StringEncoding];
    [myHandle writeData:dat];
    [myHandle closeFile];
```
### 2. 删除文件


```
NSString *homePath = NSHomeDirectory();
    NSString *filePath = [homePath stringByAppendingString:@"/wanghuiyong/note.txt"];
    NSFileManager * myManger = [NSFileManager defaultManager];
    if ([myManger fileExistsAtPath:filePath])
        [myManger removeItemAtPath:filePath error:nil];
```
# 9. 参考

[iOS基础教程-文件操作](http://www.imooc.com/learn/655)
