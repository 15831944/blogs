## 2. 数组

数组元素只能是对象

同一个数组可以存储不同类型的对象

内存空间依然连续

不论是什么对象，数组元素都是一个指针


### 1. NSArray

#### 1. 基本操作

1. 数组初始化
2. 数组长度
3. 数组元素判断
4. 数组最后一个元素
5. 数组第一个元素
6. 数组元素查找
7. 数组元素位置

```
#import <Foundation/Foundation.h>
int main(int argc, const char * argv[]) {
    @autoreleasepool {
        NSArray *array = [[NSArray alloc] initWithObjects:@"1", @"2", @"3", @"4", @"5", nil];
        int count = (int) array.count;
        NSLog(@"count = %d", count);
        BOOL ishas = [array containsObject:@"2"];
        if (ishas)
        {
            NSLog(@"contain");
        }
        else
        {
            NSLog(@"not contain");
        }
        NSString *str = [array lastObject];
        NSLog(@"str = %@", str);
        str = [array firstObject];
        NSLog(@"str = %@", str);
        str = [array objectAtIndex:3];
        NSLog(@"str = %@", str);
        int index = (int) [array indexOfObject:@"3"];
        NSLog(@"index = %d", index);
    }
    return 0;
}
```

#### 2. 数组的遍历

1. for 循环
2. for in 快速枚举(需要数组元素类型一致)
3. 枚举器(迭代器)

```
#import <Foundation/Foundation.h>
int main(int argc, const char * argv[]) {
    @autoreleasepool {
        NSArray *array = [[NSArray alloc] initWithObjects:@"1", @"2", @"3", @"4", @"5", nil];
        for (int i = 0; i < array.count; i++)
        {
            NSString *str1 = [array objectAtIndex:i];
            NSLog(@"array[%d] = %@", i, str1);
        }
        for (NSString *str2 in array)
        {
            NSLog(@"array = %@", str2);
        }
        NSEnumerator *enumerator;
        enumerator = [array objectEnumerator];
        id thing;
        while (thing = [enumerator nextObject]) {
            NSLog(@"%@",thing);
        }
    }
    return 0;
}
```

### 2. Multable Array 可变数组

#### 1. 添加和删除

addObject

addObjectsFromArray

removeAllObjects

removeLastObject

removeOjbect

removeOjbectAtIndex

#### 2. 交换数组元素位置

exchangeObjectAtIndex:(NSUInteger) withObjectAtIndex:(NSUInteger)