# SQLite 概述

1. SQLite 是一个轻量级关系数据库管理系统, 设计目标为针对嵌入式, 特点是占用资源低, 可移植性强, 速度快, 版本是 SQLite 3
2. SQLite 被内建 在Core Data 框架中, 是一个相对较小的 C 库, 可高效的管理数据, 被植入到进程空间, 不需要跨进程处理, 提升处理速度

# SQLite 数据类型

1. 后面3个是为了兼容 SQ 92 标准而进行的转换

| data type         | describe                          |
| ----------------- | --------------------------------- |
| INTEGER           | 有符号整型, 可用1和0代表 bool 型      |
| REAL              | 浮点型                              |
| TEXT              | 字符串类型, 采用 UTF8, UTF16 编码, 可用于表示时间和日期类型 |
| BLOB              | 大二进制对象类型, 能够存放任何二进制数据 |
| NUMERIC           | 转换成 INTEGER 或者 REAL 型          |
| FLOAT DOUBLE      | 转换成 REAL                         |
| VARCHAR CHAR CLOB | 转换成 TEXT 类型                     |

# SQL 语句

表名: USER; 字段: uid, name; 值: 0, 'wanghuiyong'

```
create table USER(uid, name);							// 创建数据表
create table if not exists USER(uid, name);				// 条件创建数据表
drop table USER											// 删除表
insert into USER (uid, name) values(0, 'wanghuiyong');	// 插入
select uid from USER;									// 查询, 可使用通配符
update USER set name = 'wanghuiyong' where uid = 3;		// 修改, 使用 where 指定修改条件
														// 更多语句
```

# SQLite 函数

```
sqlite3_open()		// 打开数据库
sqlite3_exec()		// 执行 Create Table 语句
sqlite3_close()		// 释放资源
sqlite3_prepare_V2	// 预处理 SQL 语句
sqlite3_bind_text	// 绑定参数
sqlite3_step		// 执行 SQL 语句, 遍历结果集
sqlite3_column_text	// 提取字段数据
```

# 开发过程

1. 输入数据, 写入数据库
2. 读取数据库, 存入 table

# HomeViewController : UITableViewController

1. 替代默认的 ViewController
1. 在storyboard 中添加 TableViewController 嵌入到 Navigation Controller
1. 并将 Navigation Controller 设置为 Initial View Controller, 即 storyboard 的入口
1. 将 TableViewController 的 storyboard 的类指定为 HomeViewController
1. 将 Table View Cell 的 Style 设置为 Subtitle


HomeViewController 的属性:

```
@property NSMutableArray *studentArray;	// 数据源(学生模型)
```

# 参考

[iOS基础教程-SQLite数据库操作](http://www.imooc.com/learn/661)
