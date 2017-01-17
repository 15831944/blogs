# Interface Buidler

1. Interface Buidler 原本是独立的应用, 现被集成到 Xcode 中, 用于建立逻辑操作代码和界面对象之间的通信
2. Interface Buidler 创建的是 OC 或 Swift 对象, 与在代码中所做的一样, 但不会生成任何需要手动维护的代码, 然后把这些对象序列化到 nib 或 storyboard 文件中
3. 应用程序运行时, 自动加载 nib 文件或 storyboard 文件, 实例化对象, 加载到内存中
4. 应用程序内容的组织和呈现方式是, 一个应用程序(application)对应一个或多个屏幕(sereen), 一个屏幕对应一个视图控制器, 管理该屏幕的一组视图对象, 多个屏幕则各自有其试图控制器
5. 视图就是眼睛能看到并且可以在 Interface Buidler 中进行编辑的部分
6. 控制器就是编写的代码, 用来处理用户的交互事件, 实际的操作都在控制器内执行, 新建一个项目后, 默认的主视图控制器覆盖整个屏幕

# 文件类型

1. .nib 是二进制格式文件, 只包含一个视图及相关联的控制器或对象, 只在需要显示某个视图时加载他的 nib 文件, 一次加载完所有内容, 节省内存, .xib 是 XML 衍生格式文件, 文本文件便于版本管理
2. .storyboard 文件, 相当于一个元 nib 文件(meta-nib file), 可以包含多组视图和控制器, 以及如何在应用运行时进行相互连接的配置信息, 加载某视图和控制器时请求特定内容

# storyboard

1. storyboards: 用于规划 flow 或 story 来驱动你的 app
2. canvas: 画布, storyboard 的背景, 用于添加和安排界面元素
3. scene: 场景, 用于表示一个屏幕的内容, 每个场景有自己的视图层次, 由一个视图控制器进行管理
4. storyboard entry point: 指向 canvas 上的 scene 的左侧的箭头
5. outline view: 大纲视图, 显示在 canvas 的左侧, 用于查看 storyboard 中的对象层次, 以场景作为相关内容的容器进行划分
6. content view: 目录视图对象, 用于定位视图层次顶部, 在其视图层次中作为一个容器为子视图提供服务
7. elements: 界面元素, 包括: views, view controllers, gesture recognizers

# 代码和界面对象之间的通信

1. 输出接口(outlet): 视图控制器通过输出接口这个特殊属性(变量)来引用 storyboard 或 nib 文件中的对象, 本质是指向 xib 文件中界面对象(控件)的指针, 使用 IBOutlet 声明该属性(变量)
2. 输出接口集合(outlet collection): 把多个同类型的对象关联到一个 NSArray 属性, 不必为每个对象单独创建属性
3. 操作方法(action method): 对 storyboard 或 nib 文件中的界面对象进行设置, 以触发控制器中的某些特殊方法, 例如点击按钮就调用代码中的某个相关操作方法, 本质是 xib 文件中某一个控件的 action, 使用 IBAction 来声明该方法
4. IBOutlet 和 IBAction 声明用于让 Interface Builder 上的控件识别输出接口或操作方法的标记, Interface Builder 根据 IBOutlet 来寻找可以在 Builder 里操作的成员变量, 根据IBAction 来说明该方法将与 Interface Builder 界面上的某个事件对应, 即与控件的相应动作相关联, 对于编译器而言, 前者为空, 后者为 void, 没有实际意义
5. 任何一个被声明为 IBOutlet 并且在 Interface Builder 里被连接到一个 UI 组件的成员变量, 会被额外保持(retain)一次, 只要使用了 IBOutlet 变量, 一定需要在 dealloc 或者 viewDidUnload 里 release 这个变量
6. sender 参数指向触发该操作方法的对象, 使得一个操作方法可以对多个控件做出响应, 并通过 sender 参数知道到底是哪个控件触发了这个操作方法

```
#ifndef IBOutlet
#define IBOutlet
#endif

#ifndef IBAction
#define IBAction void
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

# 自动布局 autolayout

1. stack view (UIStackView): A stack view provides a streamlined interface for laying out a collection of views in either a column or a row.
1. 自动布局 (Auto Layout): 为视图添加约束(constraint)
2. Trait Variations: 尺寸分类

约束 Constraints

1. 蓝色引导虚线 blue layout guides
1. 约束实线: 蓝色表示成功, 橙色表示有问题

拖动到父类

1. Leading Space to Container Margin,       Label.leading(左边缘到父视图左侧距离) = leadingMargin(16) + 150(视图左侧到容器左侧边缘的距离)
2. Trailing Space to Container Margin,      trailingMargin = Label.trailing(右边缘到父视图左侧距离) + 159
3. Vertical Spacing to Top Layout Guide,    Label.top = Top Layout Guide.bottom + 80
4. Vertical Spacing to Bottom Layout Guide, Bottom Layout Guide.top = Label.bottom + 467

5. Center Horizontally in Container 在容器中水平居中, Label.centerX = centerX
6. Center Vertically in Container 在容器中垂直居中,   Label.centerY = centerY

7. Equal Widths
8. Equal Height
9. Aspect Ratio

自动布局按钮

Embed In Stack

Align(对齐)

1. Horizontally in Container
2. Vertically in Container

Pin(固定)

1. Spacing to nearest neighbor, Constrain to margins 容器和屏幕左右侧距离16像素
2. Width, Height
3. Equal Widths, Equal Height, Aspect Ratio(尺寸变化行为)
4. Align

Resolve Auto Layout Issues(解决自动布局问题)


Resizing Behavior(尺寸变化行为)

# View Controller Scene

1. View Controller: 视图控制器对象, 从文件加载控制器及相关的视图, 其中 View(主视图) 代表 UIView 类的一个实例
2. First Responder: 第一响应者指用户当前正在交互的对象(控件或视图)
3. Exit

# Assets.xcassets

1. Assets 目录包含应用程序的所有图片
2. 图片格式是 png(portable network graphic, 便携式网络图像)文件

应用图标 AppIcon

1. 图标尺寸: 点数尺寸 * 倍数 = 像素尺寸
2. 图标类型: notification, spotlight, Settings, App

1. 启动图片
2. 启动文件 LaunchScreen.xib

# action sheet

# alert 对话框的设置
