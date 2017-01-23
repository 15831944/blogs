# 数据类型

1. 基本数据类型(Fundamental Types)包括: Int, Float, Double, Bool, String, Tuple
2. 集合数据类型(Collection Types)包括: Array, Dictionary, Set
3. 自定义数据类型(Named Types)包括: 枚举, 类, 结构体, 是为 Swift 创建的新类型, 首字母大写, 面向对象的实质就是自定义的数据类型
4. 基本数据类型, 集合数据类型, 枚举的实现均是结构体

## 整型 Int, UInt, Int8, Int64

1. Int 类型的属性: 使用 max 和 min 属性查看整型的存储范围, 属性值的类型同原数据类型
2. Int 类型的宽度同所在平台的原生字长(native word size), 增强一致性(consistency)和复用性(interoperability), 推荐用 Int, 存取速度快, 不推荐 UInt, Int8 等

## 浮点型 Float, Double

1. Float 类型默认为32位数, 精度为6位; Double 类型为64位数, 精度为15位, 推荐用 Double
2. 可以使用科学计数法初始化浮点类型变量, 10进制用e表示, 16进制用p表示
3. OC 中使用 CGFloat 类型表示图形中的浮点数(Core Graphics 是苹果的一个底层矢量图绘制框架, 还有 Core Data，Core Animation 等)
4. Swift3 引入 FloatingPoint 协议统一不同的浮点类型

## 布尔 Bool

1. 布尔常量值(Boolean constant values): true, false
2. Swift 是强类型语言, 不可以使用0代表假, 非0值代表真, 比较运算符的表达式会返回 Bool 类型

## 元组 Tuple

1. 元组: Swift 新增的 C 和 OC 没有的数据类型, 用于相关联不同类型的数据的临时组合, 可创建和传递一组值
2. 元组的分解(decompose): 将元组中的元素分解出来, 赋给各变量, 使用下划线忽略不需要解包的元素
3. 元素的名称: 使用 ":" 在初始值中或显式类型声明中为元组的各个元素命名(区分 ":" 后面接数据类型的习惯用法)
4. 元素的访问: 使用 "." 运算符以元素的序号或名称访问元祖的各个元素
5. 在 OC 版本的 Cocoa API 中有不少需要传递指针来获取值的地方, 一般是返回值只能有一个所造成的妥协, 使用元祖可使函数返回多个值

## 可选型 Optional

1. 可选型的必要性: 程序执行时, 访问指向不存在的对象的指针会导致运行时错误, C 语言使用 NULL 表示空指针, 本质是整型, 指向地址0, OC 语言的方法(method)通常返回一个特殊值(NSNotFound)来表示没有值, 用 nil 空对象指针表示没有有效对象(nonexistent object), 可选型可用于任何类型, 而不仅是类, 用一个统一的符号(nil)代表"没有(absent)"这个概念, 避免用同类型指定值(例如用404表示错误, 0表示没有错误)带来的弊端, nil 可用于各种数据类型的可选型, 不是指针(不同于 OC), 可以表示任何数据类型的没有值( absence of a value)
2. 可选型的声明: 可选型必须和其他类型共存, 必须显式声明可选型, 使用类型名接问号, 例如 Int? 代表整型的可选型, 即该类型的变量可选为整型, 也可选为 nil, 可以不赋初始值, 默认值是 nil (其他数据类型声明时必须赋初始值)
3. 可选型的操作: 整型可以赋值给整型的可选型, 反之则不行, 因为是不同的数据类型, 且整型的取值范围比整型的可选型小
4. 可选型的解包(unwrap): 可选型的值可能为 nil, 不能直接使用, 因此需要解包(unwrap), 在不是 nil 的情况下才可使用, 进行多个可选型的解包时可使用逗号分隔, 使用 where 进行匹配样式
5. 强制解包(forced unwrapping): 使用 if 判断该可选型不是 nil 后, 确保该可选型有值的情况下, 使用 "!" 强制解包, 强制解包失败(对 nil 解包)会导致运行时错误, 当被解包的数据是常量时, 使用强制解包一般是安全的, 因为可以确保常量值不会为空(常量必须有初值)
6. 可选型绑定(Optional Binding): 使用 if let(var) 解包, 若解包成功, 则说明解包值不是 nil, 可以使用解包出的变量或常量值, 作用域是语句块内, if 后可以接多个 let, 用逗号间隔
7. 隐式解包的可选型(Implicitly Unwrapped Optionals): 使用类型名接叹号, 声明任何时候都能确保有值的可选型, 则可直接使用, 不需要叹号, 因为已经隐式的被自动解包过了, 不需每次对值进行检查和解包, 隐式解包的可选型一般用于类的初始化
8. Optional Chaining: 使用"?."或".!"使可选型能够调用该类型的方法, 前者是普通解包, 若解包成功则可以调用方法, 若失败则返回 nil, 后者是强制解包

## 字符串 String

1. String 类型与 Foundation 的 NSString 类桥接, 只要包含 Foundation, 不需要类型转换即可使用 NSString 类公开的(expose)方法
2. 字符串可变性: String 类型常量或变量决定了字符串的可变性(mutability), 同 Swift 中的其他数据类型, 不同于 OC 中的 NSString 和 NSMutableString
3. 字符串字面值(String Literals): 使用双引号括起来的文本字符的固定长度的序列, 单个字符的字符串字面值也是字符串, 可显式声明为 Character 类型作为字符类型的常量或变量
4. 字符串字面值中的特殊字符: 以反斜杠开头的转义字符, 且可使用 `\u{n}` 形式的 Unicode 标量格式表示任意字符, Extended Grapheme Clusters 是一个或多个标量产生的单个可读字符
5. 字符串初始化: 使用初始化语法 `String()` 或空的字符串字面值来初始化一个空字符串, 字符数组可以作为字符串初始化语法中的参数来初始化一个字符串
6. 字符串是值类型, 传参和赋值都进行拷贝操作, 不会修改原字符串, 编译器对字符串优化只有在必要时才会进行拷贝操作
7. 字符串拼接(Concatenate): 使用 "+" 或 "+=" 操作符拼接字符串, 使用 append 方法拼接字符值到字符串, 字符值只能包含一个字符, 不能被拼接
8. 字符串插值(string interpolation): 在字符串中插入转义字符(反斜杠)加括号作为占位符(placeholder), 括号中为要转换为字符串的常量, 变量, 字面值和表达式, 相当于 sprintf 函数
9. 字符串编码格式: String 类型使用 Unicode 标量值 (Unicode scalar values) 构建, 字符采用 Unicode 编码(Unicode-compliant)
1. 字符串的字符: 表示为字符的标量通常具有名称, 字符和修饰符都是(还是最长是?)21位的数字, 需要用不同的内存长度进行存储, 不能用整数检索字符串中的字符
2. 字符串索引: 字符串的内容可以被当作字符值的集合来访问, 通过索引进行访问, Index 属性对应字符串中每个字符的位置, 索引越界会触发运行时错误
3. 字符串访问: 必须从字符串的开头或结尾(startIndex, endIndex 属性)或结合 index 方法进行迭代访问
4. 字符串遍历: 使用 count 属性检索字符串中的字符数, 使用 `for-in` 语句遍历字符串中的字符值
5. 字符串相等性: 语法和表现相等就认为相等, 即使是不同的 Unicode 标量, 使用比较运算符( == 和 !=)
5. 集合协议(Collection Protocol): String, Array, Dictionary, Set 类型遵循 Collection 协议, 都可以使用类似的索引方式
6. RangeReplaceableCollection protocol: String, Array, Dictionary, Set 类型遵循 RangeReplaceableCollection 协议, 都可以使用类似的插入和删除方式

属性和方法

```
endIndex	// 表示最后一个字符后面的位置, 不能用作下标, 如果字符串为空, 则 startIndex 等于 endIndex

isEmpty
append
index(before:)
index(after:)
index(_:offsetBy:)
insert(_:at:)			// 插入字符到字符串的指定索引位置
insert(contentsOf:at:)	// 插入字符串到字符串的指定索引位置
remove(at:)				// 删除指定索引的字符
removeSubrange(_:)		// 删除指定区间的字符
hasPrefix(_:)			// 前缀的相等性
hasSuffix(_:)			// 后缀的相等性
```
