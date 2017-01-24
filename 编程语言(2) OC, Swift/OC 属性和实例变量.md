# 属性和实例变量 Properties and Instance Variables

1. 实例变量: 类的每个实例都拥有自己的实例变量的一份拷贝, 在多次方法调用时保持自己的值(静态存储), 本质是后端存储数据的按名称的直接访问, 在类内按名称直接访问
2. 静态实例变量: 所有的方法都可以访问?
3. 属性: 属性是实例变量的外部接口, 只能在接口文件中声明, 本质是后端存储数据的存取方法, 即调用 set 和 get 方法访问后端数据, 叫做访问器(accessor)方法(since OC 2.0), 在类外使用 "." 运算符调用方法进行访问
4. 实例变量和属性的对接: 实例变量名是属性名加下划线前缀, 二者内存操作不同(按名称和调用访问器方法), 在实现文件中使用 `@synthesize var = _var` 的形式将实例变量名和属性名进行对接, 若只在头文件中声明属性, 则会自动生成以下划线开头的同名的实例变量, 不再需要 `@synthesize`

# 实例变量的访问权限

实例变量可以被访问限定符修饰, 方法没有访问限定符, 方法的属性类似于 C 语言, 在头文件中声明则具有外部属性, 相当于公有, 可以被继承, 在实现文件中声明则为该类私有, 不能被继承

1. 受保护实例变量: 默认为 protected
1. 公有实例变量: 在类的接口部分(接口文件的`@interface`块中)声明的实例变量是公有的, 可以被继承
2. 私有实例变量: 在类的实现部分(实现文件的`@implementation`块中)声明或合成(synthesize)的变量是私有的, 推荐私有方式

| qualifier  | 类外                          | 类内               | 继承性 |
| ---------- | ---------------------------- | ------------------ | ----- |
| @public    | 只能使用 "->" 操作符访问(不推荐, 应使用属性) | 使用实例变量名直接访问 | 允许 |
| @proteced  | 禁止                          | 使用实例变量名直接访问 | 允许 |
| @private   | 禁止                          | 使用实例变量名直接访问 | 禁止 |
| @package   | 在框架内, 相当于私有            | 在框架外, 相当于受保护 |     |

# 属性的特性

1. atomic, nonatomic 是否使用互斥(mutex)锁定保护属性的存取方法 18.4
2. assign, retain, copy

表达式 `self.property = newValue;` 设值方法的实现

```
// assign 特性的实现
property = newValue;

// retain 特性的实现
if ( property != newValue) {
	[property release];
	property = [newValue retain];
}

// copy 特性的实现
if (property != newValue) {
	[property release];
	property = [newValue copy];
}
```
