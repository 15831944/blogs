# 概述

1. 数据解析的应用: 应用程序读取配置文件, 客户端和服务器之间的数据传输
2. 数据的形式: 应用程序使用原始数据, 需要进行数据解析, 传输和加载使用格式化数据, 需要进行数据组织

# JSON

1. JavaScript Object Notation
2. 语法: 可以嵌套

```
{key:value,key:value}			// 字典
{key:{key:value,key:value}}		// tree
{{key:value},{key:value}}		// 数组

{"weatherinfo":{"city":"北京","temp1":"15°C","temp2":"5°C","weather":"多云"}}
```

## JASN 库

库中的代码会静态的编译到程序中

1. TouchJson
2. SBJson
3. JSONKit
4. 苹果 JSON 库(iOS 5)

## NSJSONSerialization 类

JSONObjectWithData: options: error:

# XML

库

1. SAX
2. DOM
