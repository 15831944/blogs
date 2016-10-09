# 1. 数据本地化

1. 图片处理

2. 个人信息处理

3. 共用信息分享


# 2. 沙盒机制

1. iPhone 中没有 SD 卡的概念，即没有共用的闪存供应用读写

2. 不能在应用程序之间直接访问数据

3. 只能对应用自身创建的沙盒内的文件进行读写 

4. 这样的一个独立的封闭的安全的空间叫做沙盒

5. 创建沙盒会自动创建沙盒路径

6. 删除沙盒会地洞删除沙盒路径

# 3. 沙盒内容

每个应用的沙盒中包含3个文件夹

| 名称 | 用途 | 举例 |
| - | - | - |
| Documents | 保存程序创建或应用浏览产生的数据文件 | iTunes 备份和恢复数据时会使用此目录 |
| Library | 保存程序的默认设置或状态信息 | 略 |
| tmp | 保存即时创建的临时的不需要持久化的文件，应用关闭时自动删除或应用不运行时由系统删除则此目录中的文件 | 略 |

## 1. fmdbDemo

所谓持久化的数据一般是指保存在数据库中的数据，iOS 8 以前的沙盒路径文件还有一个fmdbDemo, 是一个 bundle 包，现在这个文件已经被分离

# 4. 沙盒路径

程序中，路径用字符串表示

对于沙盒路径和 tmp 路径，提供有 api 接口函数

对于 Documents 路径 和 Library 路径，可以使用路径名称进行检索，或者使用已有的沙盒路径进行拼接

## 1. 获取沙盒路径

使用以下方法，该方法返回路径字符串

`NSHomeDirectory()`

## 2. 获取 Documents 路径

使用以下方法，该方法返回搜索到的指向各路径字符串的指针数组

`NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);`
 
## 3. 获取 Library 路径

使用以下方法，该方法返回搜索到的路径字符串数组

`NSSearchPathForDirectoriesInDomains(NSLibraryDirectory, NSUserDomainMask, YES);` 

## 4. 获取 tmp 路径

使用以下方法，该方法返回路径字符串

`NSTemporaryDirectory()`

# 5. 路径组成

使用以下方法获取路径各组成部分，包括文件名，该字符串对象方法返回存在路径组成的数组

`pathComponents`

使用以下方法获取路径中最后一个组成部分，可以是文件名或目录名

`lastPathComponent`

使用以下方法删除路径中最后一个组成部分，可以是文件名或目录名

`stringByDeletingLastPathComponent`

使用以下方法在路径的最后追加文件名或目录名

`stringByAppendingPathComponent:`


# 9. 参考

[iOS基础教程-文件操作](http://www.imooc.com/learn/655)
