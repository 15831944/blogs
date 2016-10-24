# cin (istream)

1. << 操作符一次读取一个字符串(单词)
2. getline(array, size), 读取一行输入, 丢弃行末换行符(类似于 gets 函数), 在存储字符串时, 用空字符替换换行符, 返回 cin 对象
3. get(array, size), 读取一行输入, 将换行符保留在输入队列中(类似于 fgets 函数), 返回 cin 对象
4. 使用不带参数的重载的 get() 读取一个字符(换行符)
5. get 函数更加仔细, 可以通过判断下一个字符是否是换行符, 知道是读取了整行还是数组已填满
6. get 读取空行后将设置失效位(failbit)
7. getline 函数中数组溢出将设置失效位

# string (string)

1. 使用 L, u, U 分别表示 wchar_t, char16_t, char32_t 类型的字符串
2. 使用 u8 前缀表示 UTF-8编码的字符串
3. 使用 R 前缀表示原始(raw)字符串, 可以自定义定界符

## 初始化

```
string s1;			// 定义空的字符串对象
string s2("abc");	// 用字符串字面值初始化字符串对象
string s3 = "abc";
string s4 = {"abc"};
string s5(s2);
string s6(n,'c');	// 将 s4 初始化为 n 个 字符 'c' 的副本
```

## 赋值, 拼接, 附加

1. 字符串拼接只适用于字符串对象, 必须是变量, 两个字面值字符串不可以使用 "+" 进行拼接

```
str2 = str1;
str3 = str1 + str2;
str2 += str1;
```

## 成员函数

1. size()
