# 概述

1. Hybrid 建立了 Web 和 Native 之间的桥梁, JavaScript Code 在 Web View 中, 层次为 Web View <-> Native Code
2. JS Binding 建立了 JS 和 Native 之间的桥梁, 层次为 JavaScript Code <-> JSBinding Layer <-> Native Code
3. Cocos2d-x 使用[zynga]的 JS Binding 方案, 内置 spider monkey 引擎
4. iOS7 内置 JS Binding 的方案, 内置 JavaScriptCore 引擎

# JavaScriptCore API

1. JavaScriptCore.h
2. JSContext
3. JSValue
4. JSExport

# Objective-C 中的操作

1. 执行 JS 代码 (eval JavaScript Code)
2. 调用 JS 函数( Call JavaScript Function)
3. 创建 JS 值对象(Create JavaScript Value)

# 类型转换

类型的映射关系

| Objective-C Type | JavaScript Type    |
| ---------------- | ------------------ |
| nil              | undefined          |
| NSNull           | null               |
| NSString         | string             |
| NSNumber         | number, boolean    |
| NSDictionary     | Object object      |
| NSArray          | Array object       |
| NSDate           | Date object        |
| NSBlock          | Function object    |
| id               | Wrapper object     |
| Class            | Constructor object |

[zynga]: https://github.com/zynga/jsbindings

# 参考

1. [When iOS loves JS](http://www.imooc.com/learn/92)
