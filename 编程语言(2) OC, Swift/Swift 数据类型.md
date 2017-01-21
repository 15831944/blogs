# 常量和变量 constant and variable

1. 数据声明: 使用 let 声明常量, 使用 var 声明变量, 值不会变的情况下应尽量使用常量(存储在常量区, 效率高)
2. 类型安全(Type Safety): 在编译时进行类型检查(Type-checking)
3. 类型推断(Type Inference): 根据初始值隐式地判断数据对象的类型, 减少代码书写量
4. 类型声明(Type Annotations): 使用 ": " 显式地声明的数据类型
5. 类型别名(Type Aliases): 使用 typealias 关键字
6. 常量的初始化: 声明时可以不赋初值, 因为编译时的常量值不需要被知道, 声明后的第一次赋值将作为该常量的值, 且只能赋值一次, 常量声明但未初始化期间不可以使用
7. 常量与变量名: 不能包含空字符(whitespace characters), 数学符号(mathematical symbols), 箭头, 保留的或者非法的 Unicode 码位(private-use or invalid Unicode code points), 连线与制表符(line- and box-drawing characters), 不能以数字开头, 将关键字放在反引号内则可用关键字作为变量名

# 字面值 literal

1. 字面值(literal value): 直接显示在源代码中的值, 例如 3.14, 整数和浮点数字面值均可使用下划线和数字0进行分割, 提高可读性
2. 数值型字面值(Numeric Literals): 使用 0b, 0o, 0x 前缀表示不同进制数, 适用于整数和浮点数, 10进制浮点数的指数是可选的, 16进制浮点数必须有指数, 本身没有类型, 因此 3 + 0.14 是可以的, 编译器对其进行计算后才能推断出类型
3. 数值类型转换(Numeric Type Conversion): 整数之间的转换使用 SomeType(ofInitialValue) 语法, 浮点数强制转换为整数将总是被截断(truncated), 字符串("123")可能被转换为整数, 返回可选型

# 值类型和引用类型 value type and inference type

1. 值类型: 基本类型(Int, Float, String), 集合类型(Array, Set, Dictionary)的实现都是结构体, 是值类型, 在函数调用中采用传值方式传递, 通过不同实体间的拷贝赋值, 存储在栈中
2. 引用类型: 类和对象是引用类型, 使用指针访问堆中的内存, Objective C 中的以 NS 开头的类型是 Fundation 框架提供的类, 所有数据类型均采用引用方式传递

# 基本数据类型 fundamental types

1. 基本数据类型包括: Int(UInt, Int8~64), Float(CGFloat), Double, Bool, String, Tuple
2. 基本数据类型的实现是结构, 自定义数据类型实现为类, 所有数据类型名风格均为首字母大写

## 整型 Int, UInt, Int8, Int64

1. Int 类型的属性: 使用 max 和 min 属性查看整型的存储范围, 属性值的类型同原数据类型
2. Int 类型的宽度同所在平台的原生字长(native word size), 增强一致性(consistency)和复用性(interoperability), 推荐用 Int

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
2. 元组的解包(decompose): 将元组中的元素分解出来, 赋给各变量, 使用下划线忽略不需要解包的元素
3. 元素的名称: 使用 ":" 在初始值中或显式类型声明中为元组的各个元素命名(区分 ":" 后面接数据类型的习惯用法)
4. 元素的访问: 使用 "." 运算符以元素的序号或名称访问元祖的各个元素
5. 在 OC 版本的 Cocoa API 中有不少需要传递指针来获取值的地方, 一般是返回值只能有一个所造成的妥协, 使用元祖可使函数返回多个值

## 可选型 Optional

1. 程序执行时, 访问指向不存在的对象的指针会导致程序崩溃
2. C 语言使用 NULL 表示空指针, 本质是整型
3. OC 语言的方法(method)通常返回一个特殊值(NSNotFound)来表示没有值, 用 nil 空对象指针表示没有有效对象(nonexistent object)
4. 可选型一般是变量, 可用于任何类型, 而不仅是类, 用一个统一的符号(nil)代表"没有(absent)"这个概念, 避免用同类型指定值(404表示错误, 0表示没哟错误)带来的弊端
5. 可选型的声明: 可选型必须和其他类型共存, 必须显式声明可选型, 使用类型名接问号, 例如 Int? 代表整型的可选型, 即该类型的变量可选为整型, 也可选为 nil
6. implicitly unwrapped optionals: 定义任何时候都确保有值的可选型, 使用类型名接叹号, 避免每次对值进行检查和解包, 一般用于类的初始化, 访问时不需要用叹号强制解包, 可认为是已自动解包
7. 整型可以赋值给整型的可选型, 反之则不行, 因为是不同的数据类型, 且整型的取值范围比整型的可选型小
8. 可选型不同于其他数据类型, 在声明时可以不赋初始值, 默认值是 nil
9. 解包(unwrap): 可选型的值可能为 nil, 不能直接使用, 需要解包(unwrap)
10. 强制解包(forced unwrapping): 使用 "!" 强制解包(确保该可选型有值), 强制解包失败(对 nil 解包)会导致运行时错误
11. Optional Binding: 使用 if let(var) 解包, 若解包成功, 则说明解包值不是 nil, 可以使用解包出值(变量或常量), 作用域是语句块内, if 后可以接多个 let, 用逗号间隔
12. Optional Chaining: 使用"?."或".!"使可选型能够调用该类型的方法, 前者是普通解包, 若解包成功则可以调用方法, 若失败则返回 nil, 后者是强制解包
13. 使用逗号分隔, 进行多个可选型的解包, 使用 where 进行匹配样式
14. nil 只能用于某种数据类型的可选型, nil 不是指针(不同于 OC), nil 可以表示任何数据类型的没有值( absence of a value)
15. nil coalesce

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

# 集合数据类型 Collection Types

1. 集合数据类型包括: Array, Dictionary, Set, 用于存储值的集合(collections of values), 实现为 generic collections
2. 集合类型的可变性: 集合类型常量或变量决定了集合的可变性(mutability, 修改内容和长度), 同 Swift 中的其他数据类型
2. 数组和字典的最后一个元素后面可以有逗号

## 数组 Array

1. 数组是值的有序集合, 存储相同类型的值到有序的列表中, 且桥接到 Foundation 的 NSArray 类, 数组元素(element)使用逗号分隔, 最后一个元素后面可以有逗号
2. 数组元素类型: 数组元素类型用方括号括起来, 必须是相同类型, 但可以是 NSObject 类型(对象指针), 就可以包含整数, 字符串等各类型
3. 数组的声明: 完整语法为 `Array<Element>`, 简写语法(Array Type Shorthand Syntax)为 `[Element]`, 推荐简写语法
4. 数组的初始化: 使用[]初始化数组
5. 数组的拼接: "+" 和 "+=" 操作符
6. 数组的访问: 属性, 方法, 下标, 下标区间的方式
7. 数组下标: 越界访问会触发运行时错误
8. 数组的相等性: "==" 操作符比较数组的值是否相等, 类似整数和字符串, 不同于其他语言中判断的是数组的引用是否相等
9. 数组的迭代: for-in
1. 二维数组: 即数组元素本身为数组, 声明类型: [[Int]], [Array<Int>], Array<Array<>>

属性和方法

```
count		// 只读属性, 可用于判断下标是否越界
isEmpty		// count 是否等于0
first
last

let emptyArray = [String]()								// 使用初始化语法(initializer syntax)创建空数组
someInts.append(3)										// 类型推断为 Int
var threeDoubles = Array(repeating: 0.0, count: 3)		// 类型推断为 Double, 初始化为默认值
var fiveInt = [Int] (repeating: 0, count: 5)
var shoppingList = ["Eggs", "Milk"]						// 使用方括号括起来的数组字面值(Array Literal)初始化数组
var shoppingList: [String] = ["Eggs", "Milk"]
var NSString = []										// 即不指定类型, 也不初始化, 则为 NSString 类型, 不建议使用
var arr: Array<Int> = []								// 初始化泛型数组
var arr: Array<Int> = [1, 2, 3]
var arr = Array<Int>()
var arr = Array<Int> (repeating: 0, count: 3)

shoppingList.append("Flour")							// append 的参数是数组元素, += 操作符的操作数是数组
insert(_:at:)
remove(at:)
let apples = shoppingList.removeLast()
for item in shoppingList {}
for (index, value) in shoppingList.enumerated() {}
```

## 集 Set

1. Sets 是唯一值的无序集合, 存储同类型的互斥的(distinct)值, 桥接到 NSSet 类, 排序不重要或需要确保元素的值只出现一次时, 可使用 Set 而不是 Array
2. 散列值: 相等的对象的散列值是值相同的整数, 例如a == b, 则 a.hashValue == b.hashValue
3. 存储在 Set 中的类型必须是可散列的(hashable), 即该类型必须提供计算自身的散列值的方式
4. Swift 的所有基本类型默认都是可散列的, 可以用作 set 值类型或字典 key 类型
5. Enumeration case values without associated values (as described in Enumerations) are also hashable by default
6. Hashable protocol: 遵循 Swift 标准库的 Hashable 协议, 则可自定义 set 值类型或字典 key 类型
7. Set 的声明:  Set<Element>, 类似于 Array, 但没有简写

集运算 Fundamental Set Operations

1. combining two sets together
2. determining which values two sets have in common
3. determining whether two sets contain all, some, or none of the same values.

```
count
isEmpty

var letters = Set<Character>()
letters.insert("a")
var favoriteGenres: Set<String> = ["Rock", "Classical", "Hip hop"]	// 使用数组字面值初始化 set
var favoriteGenres: Set = ["Rock", "Classical", "Hip hop"]
favoriteGenres.insert("Jazz")
remove(_:)
removeAll()
ontains(_:)
for genre in favoriteGenres {print("\(genre)")}
for genre in favoriteGenres.sorted() {print("\(genre)")}

intersection(_:)			// 交集
symmetricDifference(_:)		// 对称差集
union(_:)					// 并集
subtracting(_:)				// 差集
isSubset(of:)				// 子集
isSuperset(of:)				// 超集
isStrictSubset(of:)			// 子集且不相等
isStrictSuperset(of:)		// 超集且不相等
isDisjoint(with:)			// 不相交
```

## 字典 Dictionary

1. 字典是无序的键值关系(key-value associations)的集合, 可基于标识符查找值, 桥接到 NSDictionary 类
2. 字典的声明: 完整语法为 Dictionary<Key, Value>, 简写语法为 [Key: Value], 推荐后者, Key 类型遵循 Hashable 协议

```
count
isEmpty

let emptyDictionary = [String: Float]()									// 使用构造函数语法(initializer syntax)创建空字典
var namesOfIntegers = [Int: String]()
namesOfIntegers[16] = "sixteen"
namesOfIntegers = [:]													// 依据上一条语句进行类型推断
var occupations = ["Malcolm": "Captain", "Kaylee": "Mechanic",]			// 使用方括号形式的字典字面值初始化字典
var airports: [String: String] = ["YYZ": "Toronto Pearson", "DUB": "Dublin"]
var airports = ["YYZ": "Toronto Pearson", "DUB": "Dublin"]
occupations = [:]														// 给变量赋新值或给函数传参时, 类型可以被推断, 可以写一个空字典
airports["LHR"] = "London"												// 添加键值对
airports["LHR"] = "London Heathrow"										// 修改键值对
let oldValue = airports.updateValue("Dublin Airport", forKey: "DUB")	// 添加键值对
if let airportName = airports["DUB"] {}									// 检索键值对
airports["APL"] = "Apple International"
airports["APL"] = nil													// 删除键值对
let removedValue = airports.removeValue(forKey: "DUB")					// 删除键值对
for (airportCode, airportName) in airports {}							// 迭代
for airportCode in airports.keys {}
for airportName in airports.values {}
let airportCodes = [String](airports.keys)								// 数组
let airportNames = [String](airports.values)
sorted()
```

# 自定义数据类型 named types

## 枚举 enumeration

1. Use enum to create an enumeration. Like classes and all other named types, enumerations can have methods associated with them.
2. rawValue 属性, 默认从 0 开始, 可以指定

## 结构体 structure

1. 常量成员: 若结构体成员是常量, 但结构体本身是变量, 则不可以赋值给结构体的常量成员, 但可以赋值给结构体, 间接的改变了常量成员的值
2. 默认构造函数: 结构体的默认构造函数的参数的顺序需与结构体中声明成员的顺序一致, 调用默认构造函数时, 要么没有参数, 要么参数要完整
3. 自定义构造函数: 会覆盖默认的构造函数
4. 构造函数的第一个参数的外部参数名不可以省略(可以使用下划线进行忽略)
5. 结构体成员可以具有默认值
6. 可失败的构造函数 failable initializer

## 类 Class

# 参考

1. [玩儿转 Swift](http://www.imooc.com/learn/127)
2. [玩儿转Swift 2.0（第一季)](http://www.imooc.com/learn/635)
3. [玩儿转Swift 2.0（第二季)](http://www.imooc.com/learn/642)
4. [玩儿转Swift 2.0（第三季)](http://www.imooc.com/learn/663)
5. [玩儿转Swift 2.0（第四季)](http://www.imooc.com/learn/677)
