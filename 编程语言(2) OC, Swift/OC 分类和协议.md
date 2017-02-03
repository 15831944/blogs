# 分类和扩展 Categories and Externtions

1. 模块(module): 引用包含在一个源文件中的任何数目的方法或者函数定义, 为系统头文件提供更快的处理速度(重新编译它们)和避免了潜在的命名冲突, 如 `#import UIKit`
2. 分类的作用: 以模块的方式向现有类定义添加新的方法, 将类的定义模块化到相关的方法的组或分类中, 是更简便的扩展类的方式, 可向主类添加的方法, 无须访问类的源代码, 无须创建子类, 通过分类向主类添加的方法可以被主类的子类继承
3. 分类的访问权限: 分类可以直接访问主类的实例变量和方法, 而不能在分类中重复声明父类的实例变量, 因为主类已经向编译器告知了实例变量
4. 分类的声明: 分类的文件名习惯为主类名接分类名, 分类的接口可以定义为单独的文件(应包含主类的头文件)或写在主类接口文件下面(前提是可以访问主类的源代码), 实现可以定义为单独的文件(主类不能访问分类方法)或写在主类实现文件下面(主类的所有用户都可以访问分类方法)
5. 未命名的分类: 用于类的扩展, 可以定义额外的属性和方法(有命名的分类不允许),扩展到属性和方法是主类私有的, 必须放在主类的实现文件中

```
#import ClassName.h
@interface ClassName (Category)			// 分类的定义
@interface ClassName ()					// 未命名分类的定义
@implementation ClassName (Category)	// 分类的实现
```

# 协议和委托 Protocol and Delegate

1. 协议: 协议是两个类之间的接口定义, 是多个类共享的一个方法列表, 协议是无类的(classless), 即不引用任何类, 协议可进行扩展, 定义新协议采用已有协议
2. 主要类: 定义了协议的类, 可以看作是将协议定义的方法代理给了实现他们的类
3. 代理类: 遵守(confirm to)或采用(adopt)主要类定义的协议, 实现该协议的所有方法, 实现的协议的方法可以被继承, 分类也可以采用协议
4. 举例: UITableViewController 类遵循 UITableViewDataSource 协议和 UITableViewDelegate 协议, 让用户决定表格的行(numberOfRowsInSection:)或选中行的行为( didSelectRowAtIndexPath:)

AppDelegate 类遵循 UIApplicationDelegate 协议, 在其未命名分类中实现 didFinishLaunchingWithOptions 方法

```
@protocol NSCopying										// 协议的定义
@optional												// 定义协议中可选的实现, 用于取代非正式协议的使用
@required												// 定义协议中需要的实现
@interface ClassName: SuperClass <NSCopying, NSCoding>	// 协议的采用(声明的类采用指定协议)
id <NSCopying, NSCoding> currentObject;					// 定义遵守指定协议的变量
@protocol Drawing3d <Drawing>							// 协议的扩展
@interface ClassName (Category) <NSCopying>				// 定义采用指定协议的分类
```

相关方法

```
BOOL c = [currentObject conformToProtocol: @protocol (protocolName)];	// 指定类是否满足指定协议
BOOL c = [currentObject respondsToSelector: @selector (method)];		// 指定类是否实现指定方法
```

非正式协议

1. 非正式(informal)协议是委托技术的基础, 实际上仅仅是一个名称之下的一组方法, 是一个分类, 通常用于根类, 也成为抽象(abstract)协议, 声明非正式协议的类自己并不实现这些方法
2. 选择实现这些方法的类需要在它的接口部分重新声明这些方法, 并实现这些方法中的一个或多个
3. 编译器不提供有关非正式协议的帮助, 没有遵守协议或者由编译器测试这样的概念
