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
8. set 的类型和下标返回的类型一致

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
