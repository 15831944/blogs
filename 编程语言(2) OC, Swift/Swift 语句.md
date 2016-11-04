# 控制流

1. 条件表达式不需要括号, 语句块必须有大括号

## 循环

3. for in 循环跟常量(每次循环时重新定义并初始化, 而非一个变量的值在改变), 必须将区间中的值遍历一遍
5. repeat-while, 至少执行一次
6. swith 语句不需要写 break(可以写, 例如在 default 下不做任何处理时), 一个 case 中可以有使用逗号分隔的多个值, switch 可以判断整数以外的类型, case 需要穷举, 否则必须有 default
7. 使用空的小括号作为空语句, 而不能是分号
8. swith 不仅可以判断单值, 也可以是区间, 元组等
9. 使用 fallthrough 继续判断下一个 case
10. break 或 continue 接控制过程名字可以跳出多重循环或其他的控制转移, 相当于 goto
11. 控制转移包括: break, continue, fallthrough, return, throw
12. where 关键字 限定 case 的匹配模式, 3.0中换成逗号
12. if case
