# SQLite 概述

1. SQLite 是一个轻量级关系数据库管理系统, 包含在一个相对较小的 C 库中, 设计目标为针对嵌入式, 特点是占用资源低, 可移植性强, 速度快, 版本是 SQLite 3
2. Core Data 框架提供的内建 SQLlite 技术可以高效的管理数据

# SQLite 数据类型

| Data Type         |  |
| ----------------- | --- |
| INTEGER           | 有符号整型 |
| REAL              | 浮点型 |
| TEXT              | 字符串类型, 采用 UTF8, UTF16 编码 |
| BLOB              | 大二进制对象类型, 能够存放任何二进制数据 |
| VARCHAR CHAR CLOB | 转换成 TEXT 类型, 为兼容 SQ92 标准 |
| FLOAT DOUBLE      | 转换成 REAL, 为兼容 SQ92标准 |
| NUMERIC           | 转换成 INTEGER 或者 REAL 型, 为兼容 SQ92 标准 |

1. 没有布尔类型数据，用整型的1和0代替
2. 没有日期时间类型，存储在 TEXT 或者 REAL 类型中

# SQLite 语句

表名: USER; 字段: uid, name; 值: 0, 'wanghuiyong'

```
create table USER(uid, name);							// 创建数据表
create table if not existss USER(uid, name);			// 条件创建
drop table USER											// 删除表
insert into USER (uid, name) values(0, 'wanghuiyong');	// 插入
select uid from USER;									// 查询
update USER set name = 'wanghuiyong' where uid = 3;		// 修改
```

# SQLite 函数

```
sqlite3_open()		// 打开数据库
sqlite3_exec()		// 执行 Create Table 语句
sqlite3_close()		// 释放资源
```

# 参考

[iOS基础教程-SQLite数据库操作](http://www.imooc.com/learn/661)
