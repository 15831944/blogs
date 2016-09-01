# 概述

SQLite 是一个轻量级关系数据库管理系统，包含在一个相对较小的 C 库中，设计目标为针对嵌入式

占用资源低

可移植性强

速度快

SQLite 3

# 数据类型

| INTEGER | 有符号整型 |
| - | - |
| REAL | 浮点型 |
| TEXT | 字符串类型，采用 UTF8 UTF16 编码 |
| BLOB | 大二进制对象类型，能够存放任何二进制数据 |
| VARCHAR CHAR CLOB | 转换成 TEXT 类型，为兼容 SQ92标准 |
| FLOAT DOUBLE | 转换成 REAL，为兼容 SQ92标准 |
| NUMERIC | 转换成 INTEGER 或者 REAL 型，为兼容 SQ92标准 |

1. 没有布尔类型数据，用整型的1和0代替

2. 没有日期时间类型，存储在 TEXT 或者 REAL 类型中

# SQLite 语句

## 1. 创建数据表

指令: create table 表名(字段1, 字段2, ……);

示例: create table USER(uid, name);

## 2. 条件创建（如果不存在则创建）

指令: create table if not existss 表名(字段1, 字段2, ……);

示例: create table if not existss USER(uid, name);

## 3. 删除表

指令: drop table 表名

示例: drop table USER

## 4. 插入

指令: insert into 表名 (字段1, 字段2, ……) values(值1, 值2, ……);

示例: insert into USER (uid, name) values(0, 'wanghuiyong');

## 5. 查询

指令: select 字段 from 表名

示例: select * from USER;

## 6. 修改

指令: update 表名 set 字段 = '新值' where 条件

示例：update USER set name = 'wanghuiyong' where uid = 3;

# 创建数据库

## 1. 打开数据库

`sqlite3_open` 函数

## 2. 执行 Create Table 语句

`sqlite3_exec` 函数

## 3. 释放资源

`sqlite3_close` 函数


# 参考

[iOS基础教程-SQLite数据库操作](http://www.imooc.com/learn/661)