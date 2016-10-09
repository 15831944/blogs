# 1 C reserved keywords

## 1.1 storage-class specifier

auto     automatic duration storage-class specifier with no linkage.
extern   static duration storage-class specifier with either internal or more usually external linkage.
register automatic duration storage-class specifier with no linkage. Hints that the variable will be used heavily.
static   static duration storage-class specifier with internal linkage at file scope and no linkage at block scope.
         static array indices in function parameter declarations.(since C99)

根据以上可以确定变量的各属性: 作用域(可见性)和存储期.

## 1.2 statement

break    break statement: as the declaration of the statement
continue continue statement: as the declaration of the statement
goto     goto statement: as the declaration of the statement
return   return statement: as the declaration of the statement
if       if statement: as the declaration of the if statement
else     if statement: as the declaration of the alternative branch
switch   switch statement: as the declaration of the statement
case     switch statement: as the declaration of the case labels
default  switch statement: as the declaration of the default case label
         type-generic expression: as the declaration of the default generic association(since C11)

## 1.3 loop

do       do-while loop: as the declaration of the loop
for      for loop: as the declaration of the loop
while    while loop: as the declaration of the loop
         do-while loop: as the declaration of the terminating condition of the loop

## 1.4 type declarator

char     type specifier for the character types (char, signed char, and unsigned char).
int      int type: as the declaration of the type
double   double type: as the declaration of the type
enum     declaration of an enumeration type
float    float type: as the declaration of the type
inline   inline function specifier
struct   declaration of a compound type
union    declaration of a union type
typedef  typedef declaration
void     void type: as the declaration of the incomplete type
         void: in a function with no parameter or no return value

## 1.5 type modifier

long     long type modifier
short    short type modifier
signed   signed type modifier
unsigned unsigned type modifier

## 1.6 type qualifier

const    const type qualifier
restrict restrict type qualifier
volatile volatile type qualifier

## 1.7 operator

sizeof   sizeof operator

# 2 inline

内联函数 Inline function

在函数定义前添加 inline 关键字

内联函数在某些情况下类似于宏

内联函数的作用是将直接将代码内嵌到调用它的父函数中

编译时需要指定优化等级为 -O3 才能被内嵌

也可以指定内嵌函数属性 #pragma always_inline 强制内嵌

有几种情况将不内嵌，而作为普通函数调用：

1. 可变参数的函数
2. 调用 alloca 类库的函数
3. 有可变尺寸数组声明的函数
4. 非本地goto的函数
5. 嵌套调用的函数

使用 ISO C 标准的时候，可以使用 __inline__ 关键字代替 inline 关键字


# 参考

http://en.cppreference.com/w/c/keyword
