| object | meaning |  |  |
| ------ | ------------------------------------------- | --- | --- |
| NULL   | a macro defined in several standard headers |
| 0      | an integer constant                         |
| '\0'   | a character constant                        |
| nul    | the name of the character constant          |

All of these are not interchangeable:

1. NULL is to be used for pointers only since it may be defined as ((void *)0), this would cause problems with anything but pointers.
2. 0    can be used anywhere, it is the generic symbol for each type's zero value and the compiler will sort things out.
3. '\0' should be used only in a character context.
4. nul  is not defined in C or C++, it shouldn't be used unless you define it yourself in a suitable manner, like: #define nul '\0'

1、NULL 用于表示什么也不指向，也就是空指针((void *)0)
2、0    可以被用于任何地方，它是表示各种类型零值的符号并且编译器会挑出它
3、'\0' 应该只被用于结束字符串
4、NUL  没有被定义于C和C++，它不应该被使用除非你自己定义它，像：#define nul '\0'
