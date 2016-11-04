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

# 1. 表达式

## 1 原始表达式

原始表达式和运算符组成复合表达式

## 2. 初始化表达式

## 3. 函数表达式

## 4. 属性访问表达式

点号或中括号

## 5. 调用表达式

小括号，大括号

## 6. 对象创建表达式

new

# 2. 运算符

按操作数数量分为一元，二元及三元运算符

按类型分为赋值，比较，算术，位，逻辑，字符串及特殊运算符

## 特殊运算符

### 1. 条件运算符 ?:

### 2. 逗号运算符 ,

### 3. 删除属性运算符 delete

注意使用 defineProperty 方法 设置 configurable 标签为 ture 的属性才可以被删除

### 4. in 运算符

用于判断对象中是否存在指定的 key

### 5. instanceof

基于原型链判断

### 6. typeof

### 7. new 运算符

创建新对象

### 8. this 运算符

### 9. void 运算符

返回 undefined

## 运算符优先级

# 参考

[JavaScript 深入浅出](http://www.imooc.com/learn/277)

# block 语句

块语句用一对花括号定义

不存在块级作用域，在块中和块外定义变量是等效的

<font color=red>从ES6开始，let的出现，JavaScript也有了块级作用域的概念</font>

# var 语句

声明语句

var a = b = 1

a是局部变量，b 是全局变量

# try-catch 语句

异常捕获机制

catch 和 finally 至少有一个

# function 语句

定义函数对象，是函数声明，区分函数表达式：
在函数声明前调用函数是可以的，函数表达式则不可

# for in 语句

1. 顺序不确定
2. enumerable 标签为 false 时不会出现
3. for in 对象属性时受原型链影响

# switch 语句

# while 语句

# do while 语句

# for 语句

# with 语句

修改当前作用域

# 参考

[JavaScript 深入浅出](http://www.imooc.com/learn/277)
