# C reserved keywords

## 存储类型说明符 storage-class specifier

| keywords | meaning                                                                                                   |
| -------- | --------------------------------------------------------------------------------------------------------- |
| auto     | automatic duration storage-class specifier with no linkage                                                |
| extern   | static duration storage-class specifier with either internal or more usually external linkage             |
| register | automatic duration storage-class specifier with no linkage. Hints that the variable will be used heavily  |
| static   | static duration storage-class specifier with internal linkage at file scope and no linkage at block scope |
|          | static array indices in function parameter declarations (since C99)                                       |

## 跳转, 条件, 循环语句声明符 statement declarator

| keywords | meaning                             |
| -------- | ----------------------------------- |
| break    |                                     |
| continue |                                     |
| goto     |                                     |
| return   |                                     |
| if       | if statement                        |
| else     | if statement: alternative branch    |
| switch   | switch statement                    |
| case     | switch statement: case labels       |
| default  | switch statement: efault case label |
|          | type-generic expression: as the declaration of the default generic association(since C11) |
| do       | do-while loop                       |
| for      | for loop                            |
| while    | while loop                          |
|          | do-while loop: terminating condition of the loop |

## 类型声明符 type declarator

| keywords | meaning                   |
| -------- | ------------------------- |
| char     |                           |
| int      |                           |
| double   |                           |
| enum     | enumeration type          |
| float    |                           |
| inline   | inline function specifier |
| struct   | compound type             |
| union    |                           |
| typedef  |                           |
| void     | incomplete type           |
|          | in a function with no parameter or no return value |

## 类型修饰符 type modifier

| keywords | meaning                   |
| -------- | ------------------------- |
| long     | long type modifier        |
| short    | short type modifier       |
| signed   | signed type modifier      |
| unsigned | unsigned type modifier    |

## 类型限定符 type qualifier

| keywords | meaning                   |
| -------- | ------------------------- |
| const    | const type qualifier      |
| restrict | restrict type qualifier   |
| volatile | volatile type qualifier   |

## 操作符 operator

| keywords | meaning         |
| -------- | --------------- |
| sizeof   | sizeof operator |

# inline

1. 使用 inline 关键字声明内联函数 Inline function, 内联函数在某些情况下类似于宏, 直接将代码内嵌到调用它的父函数中
2. 编译时需要指定优化等级为 -O3 才能被内嵌, 也可以指定内嵌函数属性 #pragma always_inline 强制内嵌
3. 使用 ISO C 标准的时候，可以使用 \_\_inline\_\_ 关键字代替 inline 关键字

有几种情况将不内嵌，而作为普通函数调用：

1. 可变参数的函数
2. 调用 alloca 类库的函数
3. 有可变尺寸数组声明的函数
4. 非本地 goto 的函数
5. 嵌套调用的函数

# const

1. 使用 const 限定符修饰形参可以防止函数修改传入的参数
2. 使用 const 限定符修饰指针和引用

# 参考

1. [cppreference](http://en.cppreference.com/w/c/keyword)
