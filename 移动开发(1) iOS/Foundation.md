# 值对象 Value

1. NSValue
2. NSNumber 类会依据基本数据的类型创建并初始化对象
3. NSDecimalNumber

# 字符串 String

NSString

1. NSString 对字符串的各种操作往往返回一个新建的字符串, 而不是修改原字符串
2. C 风格的字符串称为 UTF8String, 由 char 字符组成, NSString 对象由 unichar 字符(Unicode 标准的多字节字符)组成
3. 范围 Range 的实现为结构体, 成员为位置和长度
4. 网络路径和本地路径虽然都是 NSURL 类, 但获取的方法不同, 不能混用
5. 字符串比较较为复杂, 涉及读音等
6. 使用字符串字字面值定义和初始化对象在栈中, 不需要手动管理内存, 使用 alloc 方法初始化在堆中, 需要人工释放内存

NSMutableString

1. NSMutableString 在实例化可变字符串时指定长度(Capacity)可以提升性能
2. 用 NSString 对象初始化 NSMutableString 对象会报类型不匹配
3. 对字符串的操作将修改原字符串, 返回的是引用
4. NSMutableString 继承自 NSString, 即可变字符串可以使用普通字符串的方法
5. 字符串替换只能按范围进行替换

NSConstantString

NSAttributedString

1. 属性字符串

# 集合 Collection

集合数据类型包括: 数组, 字典

NSArray

1. 数组的元素只能是对象指针, 由于都是指针类型, 同一个数组可以存储不同类型的对象, 数组的内存空间依然连续
2. 不可变数组在实例化时必须指定长度, 声明后不能修改长度
3. 对数组进行快速枚举需要数组元素类型一致, 对于不一致元素会打印其地址, 因为依然是对象
4. 数组打印输出时为小括号

NSMultableArray

1. 可以实例化空的可变数组
2. 下标访问越界会报运行时错误

NSDictionary

1. 字典对象的存储内存空间不连续, 使用键值对(KVC, key value coding, 键值编码)进行访问, 是无序的
2. 添加或删除数组或字典的元素时，count 会随之变化
3. 对象释放后，每个值对象都会释放, MRC 需要注意内存管理, ARC 则不用
4. 字典打印输出时为大括号

NSMutbaleDictionary

枚举器

5. 可以使用枚举器遍历数组, 字典等
