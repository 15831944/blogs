# 概述

1. 数据解析: 应用程序需读取配置文件以使用原始数据, 要进行数据解析
2. 数据组织: 客户端和服务器之间的传输和加载使用格式化数据, 需要进行数据组织

# JSON, JavaScript Object Notation

1. JSON 格式数据本质上是字符串, JSON 格式数据的解析即对字符串的语义分析

```
//语法
{key:value, key:value}				// 字典
{key : {key:value, key:value}}		// 嵌套的树形的字典
[{key:value}, {key:value}]			// 数组
//举例
{"weatherinfo" : {"city":"北京", "temp1":"15°C", "temp2":"5°C", "weather":"多云"}}
```

## JSON 解析库

库中的代码会静态的编译到程序中

1. TouchJson
2. SBJson
3. JSONKit
4. 苹果 JSON 库(since iOS 5)

## NSJSONSerialization 类

静态方法

```
[NSJSONSerialization JSONObjectWithData: options: error:];
```
# XML 库

1. SAX
2. DOM
