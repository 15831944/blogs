# C++ 库

| libraries                   |     |
| --------------------------- | --- |
| Utilities library           |     |
| Strings library             |     |
| Containers library          |     |
| Algorithms library          |     |
| Iterators library           |     |
| Numerics library            |     |
| Input/Output library        |     |
| Localizations library       |     |
| Regular expressions library |     |
| Atomic operations library   |     |
| Thread support library      |     |
| Filesystem library          |     |

# iostream

1. << 操作符一次读取一个字符串(单词)
2. getline(array, size), 读取一行输入, 丢弃行末换行符(类似于 gets 函数), 在存储字符串时, 用空字符替换换行符, 返回 cin 对象
3. get(array, size), 读取一行输入, 将换行符保留在输入队列中(类似于 fgets 函数), 返回 cin 对象
4. 使用不带参数的重载的 get() 读取一个字符(换行符)
5. get 函数更加仔细, 可以通过判断下一个字符是否是换行符, 知道是读取了整行还是数组已填满
6. 失效位: get 读取空行后将设置失效位(failbit)
7. 文件结束位: eofbit
7. getline 函数中数组溢出将设置失效位
8. cin 会忽略空格和换行符 c++ primer plus p153
9. cin.get 函数参数是引用类型

ios base::showpoint
ios base::

# fstream

1. ofstream 继承自 ostream

open
is_open
close

# string (string)

1. 字符串对象相比于字符串数据类型操作更加简便
1. 使用 L, u, U 分别表示 wchar_t, char16_t, char32_t 类型的字符串
2. 使用 u8 前缀表示 UTF-8编码的字符串
3. 使用 R 前缀表示原始(raw)字符串, 可以自定义定界符

string 对象的初始化

```
string s1;			// 定义空字符串对象
string s2("abc");	// 使用字符串字面值直接初始化
string s3 = "abc";
string s4 = {"abc"};
string s5(s2);		// 使用另一个字符串进行初始化
string s6(n,'c');	// 初始化为 n 个 字符 'c' 的副本
```

string 对象的访问, 赋值, 拼接, 附加, 判断

1. 字符串拼接只适用于字符串对象, 必须是变量, 两个字面值字符串不可以使用 "+" 进行拼接

```
str1[n];				// 返回 char 类型
str2 = str1;
str3 = str1 + str2;		// 拼接, 字符串字面值之间不可以进行拼接
str2 += str1;
str1 == str2
```

string 对象的成员函数

```
empty()
size()					// 返回整型
```
