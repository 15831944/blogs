# NSValue

# NSNumber

1. NSNumber 类会依据基本数据的类型创建对象

```
NSNumber *number = @1;
number = [NSNumber numberWithInt:10];
NSLog(@"%i", [number intValue]);
number = [NSNumber numberWithInteger:100];
NSLog(@"%li", [number integerValue]);
number = [[NSNumber alloc] initWithInt:200];
NSLog(@"%i", [number intValue]);
number = [[NSNumber alloc] initWithInteger:400];
NSLog(@"%li", [number integerValue]);
if ([number isEqualToNumber:number] == YES)
if ([number compare:number] == NSOrderedAscending)
```

# NSDecimalNumber
