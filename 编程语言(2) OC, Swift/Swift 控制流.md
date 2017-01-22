# 控制流 Control Flow

1. 循环(loops): while, repeat-while
2. 分支(conditional branches): if, guard, switch
3. 转移(transfer): continue, break, fallthrough, return, throw

## for-in loop

1. for-in 循环: 可以对数组的元素, 字典的键值对(元组类型), 数字的范围(number intervals), 字符串中的字符, 以及其他序列(sequences)进行迭代(iterate over), 必须将区间中的值完整遍历一遍, 对字典的遍历是无序的(字典本身是无序的)
2. index 是常量, 用于获取序列的各个值, 在循环的每次迭代的开始被自动重新定义并赋值, 不需要在使用前进行声明, 而是简单地在 for-in 循环声明中被隐式地声明, 而无须使用 let 关键字, 可以使用下划线代替, 来忽略序列的值

```
for index in 1...5 {
    print("\(index) times 5 is \(index * 5)")
}
```

## if

1. if 语句的条件表达式不需要括号, 语句块必须有大括号
2. if let 的组合用于值可能丢失的情况, 判断可选型变量是否有值, 如果可选值为 nil, 则条件表达式为 false, 否则可选值被解包并分配给 let 后的常量, 使得被解包的值可以用于代码块内
3. if case

## switch

1. swith 语句支持任何类型的数据(不限于整型, 可以是区间, 元组)和各种比较操作(不限于相等性测试), 不会向下执行到(fall through)下一个 case(不再需要写 break), 空 switch 会导致编译时错误
2. case 必须穷举(exhaustive), 否则应有 default, 多个条件可以使用逗号分隔, 相当于逻辑或, default 必须放在最后, 后面可以写 break, case 不能为空, 否则必须接 break 来忽略某个条件
3. fallthrough 关键字可用于继续判断下一个 case
4. 值绑定(Value Bindings): case 可以进行值绑定, 类似与可选型的值绑定, 能够匹配不同的样式, 包括 interval matches, tuples, casts to a specific type, 匹配的值可以被限制(bound)在临时的常量或变量并用于 case 语句块内, `case let c where p` 的含义是常量 c 符合 p 指定的模版则将 p 赋值给 c
5. where 子句结合值绑定可于检查 case 中的额外条件, 限定 case 的匹配模式, Swift3 中换成使用逗号

## continue, break, fallthrough

1. continue 只能用于 loop
2. break 用于 loop 和 switch, 用于 switch 语句中空的 case 或 default 后, 使意图更加明显
3. fallthrough 只能用于 switch
4. 使用语句标签(statement label)标记循环或条件语句, continue 和 break 则可以作用于指定标签

## guard

1. 提前退出(Early Exit): 必须接 else 子句, 增加可读性

## #available

1. 检查 API 可用性
