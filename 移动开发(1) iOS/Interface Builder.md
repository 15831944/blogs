# Interface Buidler

1. Interface Buidler 原本是独立的应用, 现被集成到 Xcode 中, 用于建立逻辑操作代码和界面对象之间的通信
2. Interface Buidler 创建的是 OC 或 Swift 对象, 与在代码中所做的一样, 但不会生成任何需要手动维护的代码, 然后把这些对象序列化到 nib 或 storyboard 文件中
3. 应用程序运行时, 自动加载 nib 文件或 storyboard 文件, 实例化对象, 加载到内存中
4. 应用程序内容的组织和呈现方式是, 一个应用程序(application)对应一个或多个屏幕(sereen), 一个屏幕对应一个视图控制器, 管理该屏幕的一组视图对象, 多个屏幕则各自有其试图控制器
5. 视图就是眼睛能看到并且可以在 Interface Buidler 中进行编辑的部分
6. 控制器就是编写的代码, 用来处理用户的交互事件, 实际的操作都在控制器内执行, 新建一个项目后, 默认的主视图控制器覆盖整个屏幕


# 概念

1. storyboards: 用于规划 flow 或 story 来驱动你的 app, 包含了应用所有的视图和视图控制器
2. canvas: 画布, storyboard 的背景, 用于添加和安排界面元素
3. scene: 场景, 用于表示一个屏幕的内容, 每个场景有自己的视图层次, 由一个视图控制器进行管理
4. storyboard entry point: 指向 canvas 上的 scene 的左侧的箭头
5. outline view: 大纲视图, 显示在 canvas 的左侧, 用于查看 storyboard 中的对象层次, 以场景作为相关内容的容器进行划分
7. elements: 界面元素, 包括: views, view controllers, gesture recognizers

nib 和 storyboard 文件中的对象是作为归档对象存储的, 实例化时调用 initWithCoder: 方法

# 文件类型

1. .nib 是二进制格式文件, 只包含一个视图及相关联的控制器或对象, 只在需要显示某个视图时加载他的 nib 文件, 一次加载完所有内容, 节省内存, .xib 是 XML 衍生格式文件, 文本文件便于版本管理
2. .storyboard 文件, 相当于一个元 nib 文件(meta-nib file), 可以包含多组视图和控制器, 以及如何在应用运行时进行相互连接的配置信息, 加载某视图和控制器时请求特定内容

## nib

1. nib 文件实际上是静态对象图(frozen object graph), 当向运行中的程序加载 nib 时, 它所包含的对象会全部加载并且一直存在, 包括文件中指定的所有连接
2. 系统将依次为文件中的每个对象单独创建一个全新的实例, 并且关联所有的输出接口和对象

## storyboard

1. storyboard 中的每个场景可以看做是相应的 nib 文件, 当添加了元数据以描述场景如何通过转场互相关联后, 就得到一个 storyboard
2. storyboard 通常不会一次加载所有内容, 使新场景被激活的任何行为都会导致 storyboard 加载特定场景的静态对象图, 即不同场景中的对象不一定同时存在
3. Interface Builder 不知道哪些场景会共存, 索引禁止从一个场景中的对象向另一个场景中的对象关联任何输出接口或者目标/操作, 不同场景之间只能关联转场

# 代码和界面对象之间的通信

目标-动作模式 target-action paradigm : 

1. 输出接口(outlet): 视图控制器通过输出接口这个特殊属性(变量)来引用 storyboard 或 nib 文件中的对象, 本质是指向 xib 文件中界面对象(控件)的指针, 使用 IBOutlet 声明该属性(变量), 即视图对象作为控制器对象的属性, 向视图对象发消息
2. 输出接口集合(outlet collection): 把多个同类型的对象关联到一个 NSArray 属性, 不必为每个对象单独创建属性
3. 操作方法(action method): 对 storyboard 或 nib 文件中的界面对象进行设置, 以触发控制器中的某些特殊方法, 例如点击按钮就调用代码中的某个相关操作方法, 本质是 xib 文件中某一个控件的 action, 使用 IBAction 来声明该方法, 即视图对象向视图控制器发消息, 消息发送者可以作为方法的参数, 以便不同的视图对象可以复用一个操作方法
4. IBOutlet 和 IBAction 声明用于让 Interface Builder 上的控件识别输出接口或操作方法的标记, Interface Builder 根据 IBOutlet 来寻找可以在 Builder 里操作的成员变量, 根据IBAction 来说明该方法将与 Interface Builder 界面上的某个事件对应, 即与控件的相应动作相关联, 对于编译器而言, 前者为空, 后者为 void, 没有实际意义
5. 任何一个被声明为 IBOutlet 并且在 Interface Builder 里被连接到一个 UI 组件的成员变量, 会被额外保持(retain)一次, 只要使用了 IBOutlet 变量, 一定需要在 dealloc 或者 viewDidUnload 里 release 这个变量
6. sender 参数指向触发该操作方法的对象, 使得一个操作方法可以对多个控件做出响应, 并通过 sender 参数知道到底是哪个控件触发了这个操作方法
7. 一个控件可以触发多个操作方法, 如果一个控件已经关联了一个操作方法, 而后又将该控件的同一事件关联另一个方法, 不是不会断开前一个方法

```
#ifndef IBOutlet
#define IBOutlet	// 对编译器没有实际意义, 对 Interface Builder 有意义
#endif

#ifndef IBAction
#define IBAction void	// OC 中返回类型必须是 IBAction 
#endif

@IBOutlet weak var myButton: UIButton!						// Swift 中声明输出接口, 是常见属性, 必须是可选值
@property (weak, nonatomic) IBOutlet UIButton *myButton;	// OC 中声明输出接口, 是特殊属性, 指向用户界面中的任何按钮

@IBAction func doSomething(sender: UIButton) {}				// 使用 @IBAction 修饰符
@IBAction func doSomething() {}
@IBAction func doSomething(sender: UIButton, forEvent event: UIEvent) {}	// 控件事件

- (IBAction)doSomething:(id)sender;							// 返回类型为 IBAction 的特殊方法, 相当于 void 类型
- (IBAction)doSomething;
- (IBAction)doSomething:(id)sender forEvent: (UIEvent *)event;

```

```
IBOutlet UILabel *label;				// 变量 label 在 Interface Builder 里被连接到一个 UILabel 控件. 此时, 这个 label 的 retainCount 为2
- (IBAction)button_click: (id)sender;	// sender 是指当前的那个 control, 这样就可以不但是一个 button 对应一个 action, 而且可以让多个 button 对应与同一个 action
```

# View Controller Scene

1. View Controller: 视图控制器对象, 从文件加载控制器及相关的视图, 其中 View(主视图) 代表 UIView 类的一个实例
2. First Responder: 第一响应者指用户当前正在交互的对象(控件或视图)
3. Exit

# 设备方向 Device Orientation 和界面方向 Interface Orientation

1. Portrait, Upside Down, Landscape Left(顺时针旋转90°), Landscape Right
2. 应用级支持方向, 全局配置, 对应于 Info.plist 文件中的 Supported interface orientations 项
3. 视图控制器支持方向(应用级支持方向的子集), 设备旋转到新的方向时, 当前活动视图调用 supportedInterfaceOrientations 方法
4. 界面方向是相对于设备的, 设备方向是握持方向
