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
for (NSString *str in array)					// 使用 for in 快速枚举(需要数组元素类型一致)遍历数组
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
int count = (int)[dict2 count];									// 字典元素数
NSString *value1 = [dict2 valueForKey:@"b"];					// 按键查找值
NSString *value2 = [dict2 objectForKey:@"b"];					// 按键查找对象
NSArray *allValues = [dict2 allValues];							// 将所有值输出到数组中
NSArray *allKeys = [dict2 allKeys];								// 将所有键输出到数组中
NSArray *array = [dict2 objectsForKeys:[NSArray arrayWithObjects:@"a", @"b", @"d", nil] notFoundMarker:@"not found"];	// 按数组指定的键查找, 并将结果值输出到数组中
for (NSString *key in dict2)									// 使用快速枚举遍历字典
{
    NSLog(@"%@ = %@", key, [dict2 objectForKey:key]);
}
NSEnumerator *en = [dict2 keyEnumerator];						// 使用枚举器遍历字典
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
[dict removeObjectForKey:@"a"];
[dict removeObjectsForKeys:[NSArray arrayWithObjects:@"a", @"b", nil]];
[dict removeAllObjects];
```
