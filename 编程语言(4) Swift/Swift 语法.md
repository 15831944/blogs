# 1. 常量和变量 

使用 let 关键字声明常量(Constants)

`let maxnNum = 32`

使用 var 关键字声明变量(Variables)

`var index = 1`

1. swift 是一种类型安全(type safety)的语言，如果变量被初始化为整数1，则这个变量的类型就是 int

2. 语句的结尾并不需要添加分号

3. 数据类型的关键字的首字母是大写的

## 1. 基本数据类型

| 数据类型 | 注意 | 声明示例 |
| - | - | - |
| Int | 另有 Int8, Int16 等 |  |
| Double, Float | Double 为64位数据，精确到小数点后15位；Float 为32位数据，精确到小数点后6位 | `var red, green, bule : Double` |
| String | 用双引号括起来，不需要@符号 | `var websitename : String` |
| Bool | 使用 true 或 false 表示，而不再是 oc 中的 yes 或 no |  |

### 1. 声明不同进制的整型

`let decimalInt:Int = 17`

`let binaryInt:Int = 0b10001`

`let octalInt:Int = 0o21`

`let hexadecimalInt = 0x11`

### 2. 声明科学计数法形式的浮点数

`let a = 0.012`

`let b = 1.2e-2`

### 3. 声明大数字

用下划线隔开

`let bignum_a = 100000000`

`let bignum_b = 100_000_000`

`let bignum_c = 1_0000_0000`

### 4. 隐式类型转换

`let num_a:Float = 1`

`let num_b:Int = 1.2`

### 5. 强制类型转换

`let a:Int = 3`

`let b:Double = 0.1415926`

`let pi:Double = Double(a) + b`


### 6. 使用中文声明变量

支持任意 Unicode 类型的字符

`let 姓名 = “我的名字”`

字符串拼接：`姓名 + “你好”`

### 7. 定义布尔类型变量

1. 花括号不可省略

2. 整型值不可以作为布尔值


```
let trueVal = true
let falseVal = false

if trueVal
{
	println("true value")
}
else
{
	println("false value")
}
```

## 2. 高级数据类型

### 1. 元组 Tuples

1. 新引进的类型

2. 将多个不同的值集合成一个数据，用逗号分隔，元组中各项可以是不同类型

3. 显式声明使用以下形式: `(datatype, datatype, datatype)`

4. 用在函数返回值时可以返回一组值而不是单个值

`let connectresult = ( 404, “Not Found" )`


#### 1. 使用变量名访问元组

```
let registrationResult = (true, "username", "sex")
let ( isRegisterSuccess, nickname, gender ) = registrationResult
isRegisterSuccess
nickname
gender
```
#### 2. 使用点运算符访问元组

```
registrationResult.0
registrationResult.1
registrationResult.2
```
#### 3. 在声明时为元组中的分量指定名称

```
let registrationResult = (isRegisterSuccess: ture, nickname: "username", gender: "sex")
registrationResult.isRegisterSuccess
registrationResult.nickname
registrationResult.gender
```
#### 4. 不完整的赋值，使用下划线忽略部分数值

```
let loginResult : ( Bool, String ) = (true, "username")
let ( isRegisterSuccess, _) = loginResult
if isRegisterSuccess
{
	println("login success ! ");
}
```

### 2. 可选值 Optionals

1. 或者是一个值，或者没有值

2. 没有值时为nil（oc 中 nil 表示空指针，swift 中则更为广泛）

3. 注意，没有被初始化的值不能被直接引用，而非随机值

#### 1. 显式声明一个可选的 Int 值

`var anOptionalVarible:Int?`

此时，可选值的值为 nil

`anOptionalVarible = 12`

此时，可选值被初始化为12

#### 2. 示例

```
let userInput = "18"
var age = userInput.toInt()

if age != nil
{
	println("your age is \(age!)")
}
else
{
	println("Invalidate userInput")
}
```
1. toInt 方法返回一个可选值，所以 age 是一个可选值

2. 如果用户输入的字符可以转换为数字，则用插值的方式打印出这个值，否则报错

3. 把一个一定有值的可选型转换成相应类型的值，则在 age 后面加一个 "!" 号

4. 强制类型转换不可以对可选型，而使用 "!" 号就可以了，因为开发者确定其有值，引用是安全的。

5. 在可选型后面加 "!" 号叫做可选型的解包，在这里将一个 Int 型的可选型解包为整型

#### 3. Optional Binding

将判断和解包结合在一起

# 参考资料

[玩儿转 Swift](http://www.imooc.com/learn/127)




