# 异常处理 Error Handling

1. 可选型可以用值的存在(presence)和不存在(absence)来传达函数的成功或失败
2. 异常处理用于响应程序在运行时遇到的错误情况, 相比可选型, 可以确定失败的潜在原因, 必要时还可以传播错误到程序的 catch 子句(clauses)
3. 在函数声明中使用 throws 关键字指明它可以抛出异常
4. 在函数调用前使用 try 关键字调用能够抛出异常的函数
5. do-catch 语句用于处理异常

```
func makeASandwich() throws {
    // ...
}

do {
    try makeASandwich()
    eatASandwich()
} catch SandwichError.outOfCleanDishes {
    washDishes()
} catch SandwichError.missingIngredients(let ingredients) {
    buyGroceries(ingredients)
}
```

# 决断 Assertions

1. 特定情况不满足导致代码无法继续执行时, 在代码中触发 Assertions 来结束代码执行和提供机会去调试值没有(absent)或无效(invalid)的原因
2. Assertions 是运行时检查, 确保必要的条件满足后才会继续执行, 否则 app 会终止(terminated)
3. 当使用优化进行编译时, Assertions 是禁用的, 例如在 Xcode 中采用目标的默认释出配置(target’s default Release configuration)构建 app 时
4. Assertions 用于下标溢出时, 给函数传递无效的值导致函数无法完成其任务, 可选值为 nil 但随后的代码要成功执行必须用非 nil 的可选值时
5. 程序发布前, 开发期间, Assertions 是让你发现非法条件的有效的方式

```
assert(_:_:file:line:)
```
