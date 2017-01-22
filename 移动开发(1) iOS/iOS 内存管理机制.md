# 内存管理策略

1. 系统自动追踪对象
2. 需要时自动释放对象
3. 混合

# 内存管理机制

##  自动垃圾收集

1. 系统自动检测对象是否拥有其他对象, 当程序执行需要空间时, 不再被引用的对象会被自动释放(垃圾回收)
2. iOS 不支持, OS X 不推荐此机制

## 手工引用计数和自动释放池

1. 为了能够释放由对象创建或保持的实例变量或其他对象, 需要覆写 dealloc 方法
2. Foundation 框架中的一些方法会修改引用计数
3. 悬挂(dangling)指针: 已被销毁的对象的引用称为悬挂指针, 给悬挂指针发消息(如 release)会导致程序崩溃
4. 自动释放池: 在自定义的方法中创建一个对象, 并且方法返回该对象, 导致该方法不再使用该对象却不能释放它. 自动释放池可以追踪需要延迟释放的对象, 可在创建或返回该对象时, 向其发送 autorelease 消息
5. drain 方法: 给自动释放池发送 drain 消息, 则自动释放池会被清理, 对象会被释放
6. autorelease 方法: 给对象发送 autorelease 消息, 可将对象添加到由自动释放池维护的对象列表中, autorelease 方法不会影响该对象的引用计数
7. \@autoreleasepool 指令: 使用来自 Foundation, UIKit, AppKit 框架的类时, 首先需要创建一个自动释放池, 这样来自这些框架的类才会创建并返回自动释放的对象(不包括自定义的对象), 未启用 ARC 特性的项目会在生成的模板文件的 main 函数起始位置自动添加 \@autoreleasepool 指令
8. 程序执行到 autorelease 块末尾时, 系统会释放(发送 release 消息)自动释放池中的对象(所有发送过 autorelease 消息并被添加到自动释放池中的对象), 若这些对象的引用计数为0, 则会发出 dealloc 消息销毁对象, 释放其内存
9. 自动释放池并不包含实际的对象, 而是对象的引用
10. 以 alloc, copy, mutableCopy, new 为前缀的方法创建并拥有的对象(来自框架的和自定义的对象), 需要在使用完这些对象后负责人工释放其内存
11. 程序终止会释放所有对象(来自框架的和自定义的)

会修改对象的引用计数的方法

```
addObject:
addSubview:

removeObjectAtIndex:
removeFromSuperview:
```

### 事件循环

1. Cocoa 程序和 iOS 引用运行在事件循环中, 事件是伴随着某些行为(按下按钮)或隐性行为(网络请求)发生的
2. 系统会创建一个新的自动释放池来处理一个新事件, 可能会调用应用中的一些方法, 处理完后, 从方法中返回, 并等待下一个事件的发生
3. 事件处理完成前, 系统会清理自动释放池, 释放事件处理过程中创建的对象, 但如果对象使用了 retain 方法, 就需要我们在事件循环结束后清理自动释放池幸存的这些对象(自动释放池已经消失, 无法清理这些对象), 需要覆写 dealloc 方法, 先释放幸存的对象, 再释放父类

对象在事件循环结束后依然存在的方式

```
#import <UIKit/UIKit.h>
@interface myView : UIView
@property (nonatomic, retain) NSMutableArray *data;
@end

- (void)viewDidLoad {
	data = [NSMutableArray array];				// 创建一个自动释放的数组, 当前事件结束后会立即销毁
	data = [[NSMutableArray array] retain];		// 当事件结束后, 将从释放池中幸存
	data = [[NSMutableArray alloc] init];		// 创建一个不会自动释放的数组
	self.data = [NSMutableArray array];			// 使用设值方法, 保持已赋值给具有 retain 特性的属性的任何对象
}

- (void)dealloc {
	[data release];
	[super dealloc];
}
```

### 属性的特性

1. atomic, nonatomic 是否使用互斥(mutex)锁定保护属性的存取方法 18.4
2. assign, retain, copy

表达式 `self.property = newValue;` 设值方法的实现

```
// assign 特性的实现
property = newValue;

// retain 特性的实现
if ( property != newValue) {
	[property release];
	property = [newValue retain];
}

// copy 特性的实现
if (property != newValue) {
	[property release];
	property = [newValue copy];
}
```

## 自动引用计数 ARC

1. 系统会检测出何时需要保持对线, 自动释放对象或释放对象
2. 以 alloc, new, copy, mutableCopy, init 开头的且遵循驼峰拼写法(camelCase)的方法名, ARC 会假定方法返回对象的所有者给方法的调用者
3. ARC 只适用于 Swift 和 OC 对象以及结构体

ARC 代码与非 ARC 代码混合编译问题

# 强变量

1. 对象的指针变量(__ strong)默认是强变量
2. 属性(unsafe_unretained)默认是若变量(weak), 相当于 assign 特性
2. 强变量默认会被初始化为0(不论是实例变量, 局部变量还是全局变量)

# 弱变量

1. 循环引用的两个对象都持有彼此的强引用时, 将会产生循环保持(retain cycle), 由于对线仍然有引用, 导致系统不能销毁这个对象
2. 父视图持有子视图的强引用, 子视图持有父视图(弱变量)的弱引用, 弱变量也就不能阻止引用的对象被销毁, 即父视图被销毁后, 子视图无法引用父视图, 无法阻止父视图被销毁
3. 系统会追踪赋值给弱变量的引用, 当引用的对象释放时, 若变量会被自动设置为 nil, 即子视图持有的引用变为 nil, 给已经释放的父视图发消息会发给 nil 对象, 避免程序崩溃
4. 弱变量能够和代理很好的协作, 创建一个代理的弱变量引用, 如果代理对象被销毁, 变量就会被清0
5. 弱变量在 ARC 出现之前, 能够为程序避免很多系统崩溃

# 自动释放池

1. 可以在自动释放池中嵌套小的自动释放池来销毁临时产生的大量临时对象
2. 自动释放池对于程序使用或不使用 ARC 进行编译的情形均适用
