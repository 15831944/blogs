# 控制流 Control Flow

1. 循环(loops): while, repeat-while
2. 分支(conditional branches): if, guard, switch
3. 转移(transfer): break, continue(接控制过程名字可以跳出多重循环或其他的控制转移, 相当于 goto), fallthrough, return, throw

## for-in loop

1. for-in 循环对数组元素, 字典的键值对(元组类型), 数字范围, 字符串中的字符, 其他序列(sequences)进行迭代(iterate over)
2. index 是常量, 用于获取序列的各个值, 在循环的每次迭代的开始被自动赋值, 不需要在使用前进行声明, 而是简单地在 for-in 循环声明中被隐式地声明, 而无须使用 let 关键字, 可以使用下划线代替, 来忽略序列的值

```
for index in 1...5 {
    print("\(index) times 5 is \(index * 5)")
}
```

## if

1. if 语句的条件表达式不需要括号, 语句块必须有大括号
2. if let 的组合用于值可能丢失的情况, 判断可选型变量是否有值, 如果可选值为 nil, 则条件表达式为 false, 否则可选值被解包并分配给 let 后的常量, 使得被解包的值可以用于代码块内

## switch

4. swith 语句支持任何类型的数据(不限于整型, 可以是区间, 元组)和各种比较操作(不限于相等性测试)
5.  case 必须穷举, 否则必须有 default, default 后面可以写 break
6. `case , :` 后的变量可以使用逗号分隔, 相当于逻辑或, 不再需要写 break
7. `case let c where p` 常量 c 符合 p 指定的模版则将 p 赋值给 c
8. fallthrough 继续判断下一个 case

switch 语句中

1. case 不会向下执行到(fall through)下一个 case, 能够匹配不同的样式, 包括 interval matches, tuples, casts to a specific type, 匹配的值可以被限制(bound)在临时的常量或变量用于 case 语句块内
2. where 子句可用于表示每个 case 中的复杂的匹配条件, 限定 case 的匹配模式, 3.0中换成逗号
5. if case

## 循环

1. for-in 循环可以跟常量(每次循环时重新定义并初始化, 而非一个变量的值在改变), 必须将区间中的值遍历一遍, 对字典的遍历是无序的(字典本身是无序的), in 后面可以接区间
2. while 循环
3. repeat-while 循环会至少执行一次

1. constants and variables created with a guard statement are available in the lines of code that follow the guard statement, as described in Early Exit.
