# 1. 数据类型

## 原始数据类型

number

string

boolean

null

undefined

## 对象数据类型

object

Function

Array

Date

# 2. 隐式转换

## 1. ‘+’ 字符串拼接运算符

实例

	var x = 'The answer is ' + 42;
	
	“37” + 	7 // 377

将整数转换为字符串

	num + ''
	


## 2. ‘-’ 减法运算符

实例

	"37" - 7 // 30

将字符转换为整数

	num - 0
	
## 3. '=='相等运算符

以下例子是成立的，即会返回 true，字符串会被转换为浮点数

	“1.23” == 1.23
	0 == false
	null == undefinde
	new Object() ==  new Object()
	[1, 2] == [1, 2]

## 4. '==='严格等于运算符

### 类型不同

则返回 false

### 类型相同

	null === null
	undefined === undefined

### 注意

1. NaN 不等于 NaN，它和任何值都不会相等
2. new Object 不等于 new Object，对象用引用比较，而不是用值比较


## 5. 隐式转换规则

1. 字符串转换为数字
2. boolean 转换为整数，1代表 true， 0代表 false
3. 对象转换为基本类型
4. null 和 undefined 隐式转换后是相等的

# 3. 包装对象

原始数据类型有其对应的包装类型
当以对象的方式访问基本数据类型时，会将其转换为包装对象类型，当完成访问后，这个临时对象会被销毁掉

# 4. 类型检测

## 检测类型的方法

### 1. typeof 运算符

用于判断基本类型和函数对象，返回类型字符串

### 2. instanceof 运算符

用于判断对象类型，左操作数期望为对象，右操作数为构造函数对象

原型会指向构造器，原型链会向父级查找

### 3. Ojbect.prototype.toString 方法

### 4. constructor 属性

继承自原型

### 5. duck type

# 参考

[JavaScript 深入浅出](http://www.imooc.com/learn/277)