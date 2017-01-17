# NSArray

1. 数组的元素只能是对象指针, 由于都是指针类型, 同一个数组可以存储不同类型的对象, 数组的内存空间依然连续
2. 不可变数组在实例化时必须指定长度, 声明后不能修改长度
3. 对数组进行快速枚举需要数组元素类型一致, 对于不一致元素会打印其地址, 因为依然是对象
4. 数组打印输出时为小括号

```
NSArray *array = [[NSArray alloc] initWithObjects:@"1", @"2", @"3", @"4", @"5", nil];	// 在堆中实例化数组
int count = (int) array.count;					// 数组长度
BOOL ishas = [array containsObject:@"2"];		// 数组元素判断
str = [array lastObject];						// 数组最后一个元素
str = [array firstObject];						// 数组第一个元素
str = [array objectAtIndex:3];					// 按索引号访问数组元素
int index = (int) [array indexOfObject:@"3"];	// 查找数组元素的索引位置, 元素不存在则返回-1
for (int i = 0; i < array.count; i++)			// 使用 for 循环遍历数组
{
	NSString *str = [array objectAtIndex:i];
	NSLog(@"array[%d] = %@", i, str);
}
for (NSString *str in array)					// 使用 for in 快速枚举遍历数组
{
	NSLog(@"array = %@", str);
}
NSEnumerator *enumerator;						// 使用枚举器(迭代器)遍历数组
enumerator = [array objectEnumerator];
id thing;
while (thing = [enumerator nextObject])
{
	NSLog(@"%@", thing);
}
```

# NSMultableArray

1. 可以实例化空的可变数组
2. 下标访问越界会报运行时错误

```
[array addObject: Array];				// 添加数组元素对象, 若传入的是数组, 则此数组将作为可变数组的一个元素
[array addObjectsFromArray: Array];		// 从普通数组添加到可变数组, 普通数组的每个元素对应可变数组的各个元素
[array removeAllObjects];				// 移除数组中所有元素对象
[array removeLastObject];				// 移除最后一个对象
[array removeOjbect:Ojbect];			// 移除指定对象, 若指定对象不存在, 则调用无效
[array removeOjbectAtIndex:2];			// 按索引移除对象, 下标越界会造成运行时错误
[array exchangeObjectAtIndex:(NSUInteger) withObjectAtIndex:(NSUInteger)];	// 交换数组元素位置
```

# NSDictionary

1. 字典对象的存储内存空间不连续, 使用键值对(KVC, key value coding, 键值编码)进行访问, 是无序的
2. 添加或删除数组或字典的元素时，count 会随之变化
3. 对象释放后，每个值对象都会释放, MRC 需要注意内存管理, ARC 则不用
4. 字典打印输出时为大括号

```
NSDictionary *dict = [NSDictionary dictionaryWithObject:@"1" forKey:@"a"];		// 使用指定键值对实例化字典对象, 由于长度不可变, 因此这样声明无实际意义
NSDictionary *dict = [NSDictionary dictionaryWithObjects:[NSArray arrayWithObjects:@"1", @"2", @"3", nil] forKeys:[NSArray arrayWithObjects:@"a", @"b", @"c", nil]];		// 使用数组指定的键值对实例化字典对象
NSDictionary *dict = @{@"a":@"1", @"b":@"2", @"c":@"3"};		// 使用初始化列表实例化字典对象(key:value)
int count = (int)[dict count];									// 字典元素数
NSString *value = [dict valueForKey:@"b"];						// 按键查找值
NSString *value = [dict objectForKey:@"b"];						// 按键查找对象(值就是对象)
NSArray *allValues = [dict allValues];							// 将所有值输出到数组中
NSArray *allKeys = [dict allKeys];								// 将所有键输出到数组中
NSArray *array = [dict objectsForKeys:[NSArray arrayWithObjects:@"a", @"b", @"d", nil] notFoundMarker:@"not found"];	// 按数组指定的键查找, 并将结果值输出到数组中
for (NSString *key in dict)										// 使用快速枚举使用键遍历字典(无法像数组那样使用下标)
{
    NSLog(@"%@ = %@", key, [dict objectForKey:key]);
}
NSEnumerator *en = [dict keyEnumerator];						// 使用枚举器遍历字典
id key = nil;
while (key = [en nextObject])
{
    NSLog(@"key = %@", key);
}
[dict enumerateKeyAndObjectsUsingBlock:(id key, id obj, BOOL *stop){ }];
```

# NSMutbaleDictionary

```
NSMutableDictionary *dict = [[NSMutableDictionary alloc] init];			// 实例化空的可变字典
[dict setObject:@"1" forKey:@"a"];										// 添加键值对
[dict removeObjectForKey:@"a"];											// 按键删除对象(键值对)
[dict removeObjectsForKeys:[NSArray arrayWithObjects:@"a", @"b", nil]];	// 按键删除多个键值对
[dict removeAllObjects];												// 删除所有键值对
```
