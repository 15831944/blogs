基本的函数的使用，不多做介绍，照着敲一遍代码就明白了。。

# NSObject 基类

## 1. NSString 字符串类

### 1. NSSttring

#### 1. C 风格字符串和 OC 风格字符串之间的转换

```
#import <Foundation/Foundation.h>
int main(int argc, const char * argv[]) {
    @autoreleasepool {
        char *str1 = "a string";
        NSString *str2 = [NSString stringWithUTF8String:str1];
        NSLog(@"str2 = %@", str2);        
        NSString *str3 = @"string";
        NSLog(@"str4 = %s", [str3 UTF8String]);
    }
    return 0;
}
```
#### 2. 创建字符串

##### 1. 系统帮我们实例化对象和释放内存

```
NSString *str = @"string";




```
##### 2. 需要手动释放内存

```
NSString *str = [[NSString alloc] init];
NSString *str = @"string";



```

#### 3. 格式化字符串

```
#import <Foundation/Foundation.h>
int main(int argc, const char * argv[]) {
    @autoreleasepool {
        int a = 5;
        int b = 10;
        NSString *str = [NSString stringWithFormat:@"a = %d b = %d", a, b];
        NSLog(@"str = %@", str);
    }
    return 0;
}
```

#### 4. 拼接字符串

```
#import <Foundation/Foundation.h>
int main(int argc, const char * argv[]) {
    @autoreleasepool {
        NSString *str1 = @"string1";
        NSString *str2 = @"string2";
        NSString *str3 = [str1 stringByAppendingString:str2];
        NSLog(@"str3 = %@", str3);
    }
    return 0;
}
```
#### 5. 大小写转换

```
#import <Foundation/Foundation.h>
int main(int argc, const char * argv[]) {
    @autoreleasepool {
        NSString *str1 = @"STRing";
        NSString *str2 = [str1 lowercaseString];
        NSLog(@"str2 = %@", str2);
        NSString *str3 = [str1 uppercaseString];
        NSLog(@"str3 = %@", str3);
    }
    return 0;
}
```
#### 6. 字符串前缀、后缀

```
#import <Foundation/Foundation.h>
int main(int argc, const char * argv[]) {
    @autoreleasepool {
        NSString *str = @"www.google.com";
        BOOL hasPreFix = [str hasPrefix:@"www"];
        if (hasPreFix)
            NSLog(@"has prefix");
        else
            NSLog(@"not have prefix");
        BOOL hasSufFix = [str hasSuffix:@"com"];
        if (hasSufFix)
            NSLog(@"has suffix");
        else
            NSLog(@"not have suffix");
    }
    return 0;
}
```
#### 7. 字符串相等性判断

```
#import <Foundation/Foundation.h>
int main(int argc, const char * argv[]) {
    @autoreleasepool {
        NSString *str1 = @"www.apple.com";
        NSString *str2 = @"www.aple.com";
        if ([str1 isEqualToString:str2])
            NSLog(@"equal");
        else
            NSLog(@"not equal");
    }
    return 0;
}
```

#### 8. 字符串比较

NSComparisonResult 方法

#### 9. 字符串分割 

```
#import <Foundation/Foundation.h>
int main(int argc, const char * argv[]) {
    @autoreleasepool {
        NSString *str1 = @"a, b, c, d";
        NSArray *strArray = [str1 componentsSeparatedByString:@", "];
        for( NSString *str in strArray )
        {
            NSLog(@"str = %@", str);
        }
    }
    return 0;
}
```

#### 10. 字符串截取

```
#import <Foundation/Foundation.h>
int main(int argc, const char * argv[]) {
    @autoreleasepool {
        NSString *str = @"0123456789";
        NSRange range = NSMakeRange(1, 5);
        NSString *str1 = [str substringWithRange:range];
        NSLog(@"str1 = %@", str1);
        NSString *str2 = [str substringFromIndex:3];
        NSLog(@"str2 = %@", str2);
        NSString *str3 = [str substringToIndex:7];
        NSLog(@"str3 = %@", str3);
    }
    return 0;
}
```

#### 11. 字符串拆分
```
#import <Foundation/Foundation.h>
int main(int argc, const char * argv[]) {
    @autoreleasepool {
        NSString *str = @"0123456789";
        for (int i = 0; i < [str length]; i++)
        {
            NSLog(@"%c", [str characterAtIndex:i]);
        }
    }
    return 0;
}
```
#### 12. 字符串查找

```
#import <Foundation/Foundation.h>
int main(int argc, const char * argv[]) {
    @autoreleasepool {
        NSString *str = @"ab cd ef cd gh ijk";
        NSRange range = [str rangeOfString:@"cd"];
        NSLog(@"range.location:%ld range.length:%ld", range.location, range.length);        
    }
    return 0;
}
```
#### 13. 字符串替换

```
#import <Foundation/Foundation.h>
int main(int argc, const char * argv[]) {
    @autoreleasepool {
        NSString *str = @"hello there, hello here";
        NSString *str1 = [str stringByReplacingCharactersInRange:NSMakeRange(0, 5) withString:@"你好"];
        NSLog(@"str1 = %@", str1);
        NSString *str2 = [str stringByReplacingOccurrencesOfString:@"hello" withString:@"你好"];
        NSLog(@"str2 = %@", str2);
    }
    return 0;
}
```
#### 14. 读取文件

使用 NSURL 路径类读取网络和本地文件

```
#import <Foundation/Foundation.h>
int main(int argc, const char * argv[]) {
    @autoreleasepool {
        NSString *str = @"http://blog.csdn.net/username";
        NSURL *httpURL = [NSURL URLWithString:str];
        NSURL *fileURL = [NSURL fileURLWithPath:str];
        NSString *httpStr = [NSString stringWithContentsOfURL:httpURL encoding:NSUTF8StringEncoding error:nil];
        NSLog(@"httpStr = %@", httpStr);
        NSString *fileStr = [NSString stringWithContentsOfFile:@"/Users/username/Documents/test.txt" encoding:NSUTF8StringEncoding error:nil];
        NSLog(@"fileStr = %@", fileStr);
    }
    return 0;
}
```

#### 15. 写入文件

```
#import <Foundation/Foundation.h>
int main(int argc, const char * argv[]) {
    @autoreleasepool {
        NSString *str = @"write file";
        BOOL rtn = [str writeToURL:@"/Users/username/Documents/demo.txt" atomically:YES encoding:NSUTF8StringEncoding error:nil];
        if (rtn)
            NSLog(@"write success");
        else
            NSLog(@"write fail");
    }
    return 0;
}
```

### 2. NSMutableString 可变字符串

可变字符串是字符串类的子类，因此，字符串类的方法可以用于可变字符串，反之则不行。

#### 1. 追加字符串

```
#import <Foundation/Foundation.h>
int main(int argc, const char * argv[]) {
    @autoreleasepool {
        NSMutableString *str = [[NSMutableString alloc] initWithCapacity:10];
        [str setString:@"hello"];
        [str appendString:@" world"];
        int a = 10;
        [str appendFormat:@" %d", a];
        NSLog(@"str = %@", str);
    }
    return 0;
}
```

#### 2. 替换字符串

```
#import <Foundation/Foundation.h>
int main(int argc, const char * argv[]) {
    @autoreleasepool {
        NSMutableString *str = [[NSMutableString alloc] initWithCapacity:10];
        [str setString:@"hello world"];
        NSRange range = [str rangeOfString:@"world"];
        [str replaceCharactersInRange:range withString:@"iOS"];
        NSLog(@"str = %@", str);
    }
    return 0;
}
```
#### 3. 插入字符串

```
#import <Foundation/Foundation.h>
int main(int argc, const char * argv[]) {
    @autoreleasepool {
        NSMutableString *str = [[NSMutableString alloc] initWithCapacity:10];
        [str setString:@"hello world"];
        [str insertString:@"a " atIndex:6];
        NSLog(@"str = %@", str);
    }
    return 0;
}
```

#### 4. 删除字符串

```
#import <Foundation/Foundation.h>
int main(int argc, const char * argv[]) {
    @autoreleasepool {
        NSMutableString *str = [[NSMutableString alloc] initWithCapacity:10];
        [str setString:@"hello world"];
        NSRange range = [str rangeOfString:@"ello"];
        [str deleteCharactersInRange:range];
        NSLog(@"str = %@", str);
    }
    return 0;
}
```




# 2. 参考

[iOS 基础入门之 Foundation 框架初体验](http://www.imooc.com/learn/420)












