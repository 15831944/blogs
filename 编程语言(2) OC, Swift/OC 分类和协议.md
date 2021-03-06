# 分类 Categories

1. 模块(Module): 引用包含在一个源文件中的任何数目的方法或者函数定义, 为系统头文件提供更快的处理速度(重新编译它们)和避免了潜在的命名冲突, 如 `#import UIKit`
2. 分类(Category): 一个类可以由多个范畴构成, 将一个有很多方法的类的实现以模块为单位分散到不同的文件(模块)中, 即范畴是类的子模块
3. 分类的作用: 以模块的方式向现有类定义添加新的方法, 将类的方法定义模块化到相关的方法的组或分类中, 是更简便的扩展类的方式
3. 分类的作用: 分类无须访问主类的源代码, 无须创建子类, 通过分类向主类添加的方法可以被主类的子类继承
4. 分类的访问权限: 分类可以直接访问主类的实例变量和方法, 而不能在分类中重复声明父类的实例变量, 因为主类已经向编译器告知了实例变量
5. 分类的声明: 分类的文件名习惯为主类名接分类名
6. 分类的接口: 接口可以定义为单独的文件(应包含主类的头文件)或写在主类接口文件下面(前提是可以访问主类的源代码)
7. 分类的实现: 实现可以定义为单独的文件(主类不能访问分类方法)或写在主类实现文件下面(主类的所有用户都可以访问分类方法)

# 扩展 Externtion

1. 未命名分类: 用于类的扩展, 类扩展可以定义新的实例变量(有命名的分类不允许)并可以在多个范畴中使用, 扩展的属性和方法是主类私有的(不能让包含了类扩展的头文件对外公开), 分类方法的实现必须放在主类的实现文件中

# 关联引用 Associative References

1. 关联引用: 为已存在的对象添加实例变量, 对类进行动态扩展, 在运行时根据需要为某个对象添加(或删除)关联
2. 所有者和引用对象: 要被增加关联(扩展)的对象称为所有者, 吧追加的对象称为引用对象
3. 键值: 关联引用使用键值表示, 键值必须是常量地址以保证唯一性, 不同所有者可以使用相同的 key
4. 关联策略: 通过保持, 赋值, 拷贝的方式进行关联, 可以使原子的或非原子的

# 协议 Protocol

1. 协议: 协议是声明方法的集合, 是两个类之间的接口定义, 是多个类共享的一个方法列表, 表示对象的行为, 可以理解为只有声明而没有实现其方法和实例变量等的抽象类
2. 协议是无类的(classless), 即不引用任何类, 与具体实现无关, 协议可进行扩展, 定义新协议采用已有协议, 一个协议中不可以重复声明签名不同而选择器相同的方法, 多个协议中可以重复包含同一个方法的声明
3. 采用(adopt): 类的接口声明中指定了某个协议(本质是将协议中的方法作为了类声明的一部分)
4. 遵循(conform): 类使用协议并实现了该协议声明的所有方法
5. 协议的适用性: 对象是否适用于指定协议, 适用于协议的属性相当于该类的代理, 可以调用协议方法
6. 匿名对象(anonymous object): 代码中只关注协议和抽象类, 没有具体类名的对象
7. 协议的继承: 协议可以继承自一个或多个协议, 系统框架提供的协议中很多都继承了 NSObject 协议(协议名可以和类名相同)
8. 协议中可选实现方法: @required, @optional, 需要动态检查可选方法是否可用

1. 多重继承(Multiple Inheritance): 定义类时继承多个超类
2. 单一继承(Single Inheritance): 只继承一个超类

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

# 非正式协议

1. 非正式(informal)协议是委托的基础, 实际上仅仅是一个名称之下的一组方法, 被声明为 NSObject 根类的范畴, 也成为抽象(abstract)协议, 声明非正式协议的类自己并不实现这些方法
2. 选择实现这些方法的类需要在它的接口部分重新声明这些方法, 并实现这些方法中的一个或多个
3. 编译器不提供有关非正式协议的帮助, 没有遵守协议或者由编译器测试这样的概念, 编译时和运行时都不能检查协议的适用性

# 委托 Delegate

1. 委托: 委托是对象之间分担功能并协同处理时的一个典型的设计模式, 是某个对象接收到不能处理的消息时让其他对象代为处理的一种方式, 是负责为其他对象处理特定任务的对象, 使用协议来实现委托, 例如应用程序委托, 将 UIApplication 的工作委托给 AppDelegate, 调用 applicationDidFinishLaunching 方法, 通过应用程序委托, 能够在某些预定义时间点为 UIApplication 类做一些工作, 类似还有选取器委托等等
2. 主要类: 适用于协议的类, 可以看作是将协议定义的方法代理给了实现他们的类
3. 代理类: 遵守(confirm to)或采用(adopt)主要类定义的协议, 实现该协议的所有方法, 实现的协议的方法可以被继承, 分类也可以采用协议
4. 举例: UITableViewController 类遵循 UITableViewDataSource 协议和 UITableViewDelegate 协议, 让用户决定表格的行(numberOfRowsInSection:)或选中行的行为(didSelectRowAtIndexPath:)

AppDelegate 类遵循 UIApplicationDelegate 协议, 在其未命名分类中实现 didFinishLaunchingWithOptions 方法

# 通知 Notification

1. 通知: 将要发生的事件通知给关联的多个对象
2. 通知中心(Notification Center): 期望取得通知的对象预先向通知中心注册期望取得的通知
3. 发送(post): 某对象向通知中心发送"消息发送请求", 任何对象都可以自由使用通知的发送机制, 不需要在通知中心注册
4. 观察者(observer): 消息发送的目标, 即在通知中心注册的对象
5. 一对一的通信: 对象之间发送消息, 发送者和接受者一对一通信
6. 多播(multicast): 某个对象向特定的多个对象发送消息, 通知属于多播
7. 广播(broadcast): 向非特定的多个对象发送消息
8. 通知对象: NSNotification 类实例, 集中必要的信息后发送给通知中心
9. 通知中心: NSNotificationCenter 类, 各进程会预先准备一个默认的通知中心
0. 通知队列(Notification Queue): NSNotificationQueue 类, 将通知对象临时存储在等待队列中
1. 异步发送(asychronous post): 将通知追加到队列, 然后在运行回路中完成当前处理或者输入都都处理完成后, 再发送通知
2. 同步发送(synchronous):
