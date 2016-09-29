# Bit fields

Declares a member with explicit width, in bits. Adjacent bit field members may be packed to share and straddle the individual bytes.

使用位显式地声明一个成员。相邻的位域成员可能被打包以共享和跨越单独的字节。

A bit field declaration is a struct or union member declaration which uses the following declarator:

一个位域声明是结构或联合的成员声明，使用以下声明符

identifier(optional) : width		

identifier	-	the name of the bit field that is being declared. The name is optional: nameless bitfields introduce the specified number of bits of padding

标识符 - 要被声明的位域的名字。名字是可选的：没有名称的 bitfields 引进边距的位的指定数量。

width	-	an integer constant expression with a value greater or equal to zero and less or equal the number of bits in the underlying type. When greater than zero, this is the number of bits that this bit field will occupy. The value zero is only allowed for nameless bitfields and has special meaning: it specifies that the next bit field in the class definition will begin at an allocation unit's boundary.

宽度 - 一个整型常量表达式，其值大于等于0且小于等于底层类型的位数。大于0时，这是位域将占用的位数。0值值适用于未命名的 bitfields 并且有特殊含义：它指定了类定义中的下一个位将起始域分配的单元的边界。

## Explanation

Bit fields can have only one of four types (possibly const or volatile qualified):

位域只能具有4中类型中的1个(可能被 const 或 volatile 限定)：

unsigned int, for unsigned bit fields (unsigned int b:3; has the range 0..7)
signed int, for signed bit fields (signed int b:3; has the range -4..3)
int, for bit fields with implementation-defined signedness (Note that this differs from the meaning of the keyword int everywhere else, where it means "signed int"). For example, int b:3; may have the range of values 0..7 or -4..3.
_Bool, for single-bit bit fields (bool x:1; has the range 0..1 and implicit conversions to and from it follow the boolean conversion rules.
Additional implementation-defined types may be acceptable. It is also implementation-defined whether a bit field may have atomic type. (since C11) The number of bits in a bit field (width) sets the limit to the range of values it can hold:

1. unsigned int
2. signed int
3. int
4. _Bool
