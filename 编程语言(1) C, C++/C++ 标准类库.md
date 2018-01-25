# C++ 标准类库

ANSI/ISO C++ 类库

| libraries                   |     |
| --------------------------- | --- |
| Utilities library           |     |
| Strings library             |     |
| Containers library          |     |
| Algorithms library          |     |
| Iterators library           |     |
| Numerics library            |     |
| Input/Output library        | iostream, fstream |
| Localizations library       |     |
| Regular expressions library |     |
| Atomic operations library   |     |
| Thread support library      |     |
| Filesystem library          |     |

# string 类 (头文件 string)

1. 字符串对象相比于字符串数据类型操作更加简便
2. 使用 L, u, U 分别表示 wchar_t, char16_t, char32_t 类型的字符串
3. 使用 u8 前缀表示 UTF-8编码的字符串
4. 使用 R 前缀表示原始(raw)字符串, 可以自定义定界符
5. 字符串拼接只适用于字符串对象, 必须是变量, 两个字面值字符串不可以使用 "+" 进行拼接
