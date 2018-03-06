# Component Development Environment (CDE)

嵌入式组件

1. An embedded component is a software entity that exposes a specific set of methods, properties, and events providing an abstraction for peripheral I/O and CPUs.
2. An embedded component may also encapsulate/package a software stack or RTOS adapter.

组件的类型

1. Software Component
2. RTOS Component
3. 接口(Interface): 指定接口用于在新的组件中继承其他组件的功能, 接口是由被继承的祖先组件实现的方法和事件的列表, 组件实现了接口才能被继承, 才能被注册到接口中, 并在PE中向用户提供

组件的访问

1. 属性
2. 方法
3. 事件

驱动: 包含组件的所有方法和事件的源码的脚本, 驱动可以在组件内, 也可以和组件分开

# 继承(Inheritance)

创建硬件无关的组件, 提高代码可重用性

1. 基础硬件组件(basic hardware components): 在 PE 中提供, 涵盖了处理器的所有功能, 且硬件独立(实际是因为你拥有 PE 支持的所有 CPU 的 driver)
2. 通过继承这些组件, 你不再需要处理你的组件的低层(low-level)部分
3. 通过编写算法的高层(high-level)部分, 使用组件的继承的硬件独立的方法和事件, 使新组件保持硬件独立

CDE 允许新的被继承的组件的创建, 或者向已经创建的组件直接添加继承, 自己创建的组件未来也可以被其他组件继承

与面向对象的语言的对比

1. 在新组建被创建后任何时候, 子组件可以将父组件替换为其他组件. 而在标准的面向对象的语言中, 父对象在子对象的定义中声明的那一刻, 父对象就不能改变了

父组件如何被选择

1. 当一个组件被继承, 并且它的接口被创建或指定, 父组件和子组件之间没有绑定, 接口只是方法和事件的列表, 要建立绑定, 组件必须被注册到接口中

模板和接口在继承过程中的使用

方法的继承

接口的作用域特性, 方法和事件可以被继承为

1. 私有(Private)
2. 覆盖(Override)
3. 发布(Published)

# 组件模板(Template)

相当于已经初始化的组件, 模板由接口使用

代码生成脚本

1. edit each method independently
2. edit the whole driver using the file editor

被生成的代码的整体叫做 driver
生成代码的文件叫做 script

1. File editor

Processor Expert scripting language

Inherited components

Inherit component
Deploying components: 拷贝相关的组件文件到PE用户路径, 使PE使用最新的创建的组件


# 宏处理器 Macroprocessor
