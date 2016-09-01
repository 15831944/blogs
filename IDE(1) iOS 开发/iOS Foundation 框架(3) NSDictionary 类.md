## 3. 字典

### 1. NSDictionary

存储内存空间不连续

使用键(key)值(value)对(KVC, key value coding, 键值编码)

注意

1. 添加或删除数组或字典的元素时，count 会随之变化
2. 对象释放后，每个值都会 release

```
#import <Foundation/Foundation.h>
int main(int argc, const char * argv[]) {
    @autoreleasepool {
        NSDictionary *dict1 = [NSDictionary dictionaryWithObject:@"1" forKey:@"a"];
        NSLog(@"dict1 = %@", dict1);
        NSDictionary *dict2 = [NSDictionary dictionaryWithObjects:[NSArray arrayWithObjects:@"1", @"2", @"3", nil] forKeys:[NSArray arrayWithObjects:@"a", @"b", @"c", nil]];
        NSLog(@"dict2 = %@", dict2);
        NSDictionary *dict3 = @{@"a":@"1", @"b":@"2", @"c":@"3"};
        NSLog(@"dict3 = %@", dict3);
        int count = (int)[dict2 count];
        NSLog(@"count = %d", count);
        NSString *value1 = [dict2 valueForKey:@"b"];
        NSLog(@"value1 = %@", value1);
        NSString *value2 = [dict2 objectForKey:@"b"];
        NSLog(@"value2 = %@", value2);
        NSArray *allValues = [dict2 allValues];
        NSLog(@"allValues = %@", allValues);
        NSArray *allKeys = [dict2 allKeys];
        NSLog(@"allKeys = %@", allKeys);
        NSArray *array = [dict2 objectsForKeys:[NSArray arrayWithObjects:@"a", @"b", @"d", nil] notFoundMarker:@"not found"];
        NSLog(@"array = %@", array);
        for (NSString *key in dict2)
        {
            NSLog(@"%@ = %@", key, [dict2 objectForKey:key]);
        }
        NSEnumerator *en = [dict2 keyEnumerator];
        id key = nil;
        while (key = [en nextObject]) {
            NSLog(@"key = %@", key);
        }
    }
    return 0;
}
```

### 2. NSMutbaleDictionary

```
#import <Foundation/Foundation.h>
int main(int argc, const char * argv[]) {
    @autoreleasepool {
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
    }
    return 0;
}
```
