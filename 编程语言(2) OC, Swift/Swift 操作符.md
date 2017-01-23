# Swift 操作符

1. 运算符由 Swift 标准库(Swift Standard Library)提供, 后者也是框架
3. 使用溢出操作符 opt in to 值溢出行为
4. ++ 和 -- 两个操作符从 Swift3 开始正式被弃用, 原因是 Unicode 编码问题?
5. identity operators  引用的比较运算符为 "===" 和 "!==", 比较引用的对象实例的相等性

术语 Terminology

1. 一元运算符(Unary operators): 操作单一操作数(operand), 一元前缀运算符(Unary prefix operators)后面紧跟操作数(!a), 一元后缀运算符紧跟操作数后面(b!), 即单目运算符和操作数之间不能有空格
2. 二元运算符(Binary operators operate): 插在(infix)两个操作数之间
3. 三元运算符(Ternary operators): 同 C 和 OC 一样仅有一个, ternary conditional operator (a ? b : c)

# 基础运算符 Basic Operators

1. 赋值运算符(Assignment Operator): 没有返回值(跟 Java 一样), 不能用于条件表达式, 防止被误用为 "==", 元组类型可以直接赋值
2. 算术运算符(Arithmetic Operators): 检测且不允许值溢出, 字符串之间可使用 "+" 运算符
2. 求余运算符(Remainder Operator): Swift3 开始不能用于浮点数, 注意区别于其他语言的取模运算符, a % b 的算法为 'a = (b x some multiplier) + remainder', b 的符号不起作用
2. 负号运算符(Unary Minus Operator):
2. 正号运算符(Unary Minus Operator): 不起任何作用, 可以使代码看起来对称(symmetry)
3. 复合赋值运算符(Compound Assignment Operators): 没有返回值, 将两个操作变为一个操作
4. 比较运算符(Comparison Operators): 返回 Bool 值, 注意 Bool 值本身不能用于比较, 字符串可以比较, 元组的元素可以比较, 则该元组就可以进行比较(从左到右一个值一个值的比较, 7个元素以内)
5. 条件运算符(Ternary Conditional Operator): 应避免多个条件运算符组成的复合语句
6. 结合运算符(Nil-Coalescing Operator): 相当于 `a != nil ? a! : b`, b 必须匹配存储在 a 中的值的类型, 若 b 没有被赋值会造成短路, ?? 操作符给可选型变量赋默认值, 如果可选值丢失, 则默认值会被使用, 相当于增强的可选型版的条件表达式
7. 闭区间运算符(Closed Range Operator): `a...b` 相当于[a, b]区间, a 不大于 b, 接在 for-in 后面
7. 前闭后开区间运算符(Half-Open Range Operator): `a..<b` 相当于[a, b)区间, 若 a 等于 b, 则结果区间为空, 适用于 zero-based lists
8. 逻辑运算符(Logical Operators): 与和或操作符遵循最短路原则(short-circuit evaluation), 左结合性(left-associative)

# 高级运算符 Advanced Operators

1. 恒等运算符: 类是引用类型, 因此需要判断是否引用同一个实例, 读作"等价于"
