函数声明的发展

# 1 隐式函数声明 implicit function declaration

main 函数和 printf 函数返回值类型为 int, 若不声明, 编译器默认函数返回值为 int 类型

C90标准起，这种写法就步入了被逐步抛弃的过程(尽管当时还没有完全立即废止)

C99废除了隐式函数声明法则(remove implicit function declaration), 省略main()前面的int也已经不再容许了

```
main()
{
	printf("hello,world!\n");
}
```

# 2 函数类型声明 function type declaration

sqrt 函数类型不是 int, 需要进行函数类型说明(只声明函数类型和函数名)

调用函数时存在参数类型或个数方面的错误编译器是无法察觉的

```
double sqrt();

int main()
{
	printf("%f\n" , sqrt(9.) );
}
```

# 3 函数定义声明

把函数定义写在函数调用之前, 这种声明可以检查出函数调用时在参数个数和类型方面的错误

弊端是在由多个源文件组成的源程序时, 不利于代码的组织

函数定义声明属于函数原型声明

```
double square ( double x)
{
	return x * x ;
}

int main(void)
{
	printf("%f\n" , square(3.) );
	return 0;
}
```

# 4 函数原型声明 function propotype

C标准借鉴C++语言规定了函数原型（Function Propotype）声明

不但可以检查函数调用时参数类型和个数方面的错误，同时解决了源代码的组织问题

```
double square (double x);

int main(void)
{
	printf("%f\n" , square(3.) );
	return 0;
}

double square ( double x)
{
	return x * x ;
}
```

# 5 总结

函数类型声明, 函数定义, 函数原型都是函数声明

## 声明 declaration

指定标识符的意义和性质 A declaration specifies the interpretation and attributes of a set of identifiers.

## 定义 definition

某个标识符的定义(Definition)同时也是这个标识符的声明(Declaration), 函数定义则包括函数体

A definition of an identifier is a declaration for that identifier that: ……for a function, includes the function body

## 原型 propotype

特指包括说明参数类型的函数声明，它同样包含用这种方式写出的函数定义

# 6 错误辨析

## 错误原文

谭浩强 ，《C程序设计》（第四版），清华大学出版社，2010年6月，p182

函数的定义是指对函数功能的确立，包括指定函数名，函数值类型、形参及其类型以及函数体等，它是一个完整的、独立的函数单位。

函数的声明的作用则是把函数的名字，函数类型以及形参的类型、个数和顺序通知编译系统，以便在调用该函数时进行对照检查（例如，函数名是否正确，实参与形参的类型和个数是否一致），它不包括函数体。

## 分析

“对函数的定义和声明不是一回事”是错误的, 函数定义本身就是一种函数声明, 是子集关系。

“而函数的声明的作用则是把函数的名字，函数类型以及形参的类型、个数和顺序通知编译系统，以便在调用该函数时进行对照检查，它不包括函数体”这句话同样不通。函数定义本身就是一种函数声明，所以无法断定函数的声明是否包括函数体；而且老式的函数类型声明也属于函数声明，这种函数声明并不检查参数类型及个数方面的错误。此外函数声明也并没有检查“函数名”正确与否的功能。这段文字中的“函数类型”这个概念也有错误，函数类型所描述的不但包括函数返回值类型，也可能一并描述参数的个数和类型（如果是函数原型），因此不能与“形参的类型、个数”相提并论。

# 参考

[“函数声明”、“函数原型”与“函数定义”辨析](http://www.cnblogs.com/pmer/archive/2011/09/04/2166579.html)
