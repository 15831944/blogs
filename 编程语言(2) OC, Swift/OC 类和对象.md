# 类和对象

1. 对象的本质是结构, 对象的实例变量是结构的成员, 继承自父类的实例变量和当前子类对象自身的实例变量将组成新的结构
2. 对象的引用是指向结构的指针, 因此才可以用"->"运算符访问 `@public` 修饰的实例变量(不推荐)
3. 对象的封装的作用是使具体实现不可见，只向用户提供方法调用的接口, 有利于更好的对事物进行抽象, 原则是不能在类外直接访问实例变量, 而是需要 set 和 get 方法, 否则会难以跟踪, 调试和修改
4. 对象是引用类型: 使用 alloc, init 方法或 new 方法(不推荐)实例化对象, 对象都通过对象指针进行引用, 即传址调用
5. 使用 `@class` 声明当前类要用到的类, 可使用该类的属性, 提高效率, 但要使用该类的方法, 则需包含该类的整个头文件
6. 使用 self 关键字指明调用该方法的实例对象是当前方法的接收者

```
// 头文件, 类的声明
@interface SimpleClass: NSObject		// 类名, 父类名
{
	@protected							// 实例变量访问限定符
	NSString	*_name;					// 实例变量(更推荐写在实现文件中)
}
@property (readonly) NSString	*name	// 属性
-(void) method;							// 方法
+(id) staticMethod;						// 静态方法
@end

// 源文件, 类的实现
#import "SimpleClass.h"					// 包含类声明的头文件
@implementation ClassName				// 类名
{
	NSString *_name;					// 实例变量
}
-(void) method{							// 方法的实现
	_name = @"string";					// 访问实例变量
	NSLog(@"Hello World");
}
@end
```
