# 1. UIview 的作用

UIView 类继承自 UIResponder 类继承自 NSObject 类

但是单从图形界面看，UIView 可以看作是基类来用

UIView 对象负责在屏幕上定义一个矩形区域

视图在展示用户界面及响应用户界面交互方面发挥关键作用

每个视图对象都要负责渲染视图矩形区域中的内容，并响应该区域中发生的触碰事件

这一双重行为意味着视图是应用程序与用户交互的重要机制

在一个基于模型-视图-控制器的应用程序中，视图对象明显属于视图部分

除了显示内容和处理事件之外，视图还可以用于管理一或多个子视图

子视图是指嵌入到另一视图对象边框内部的视图对象

被嵌入的视图被称为父视图或超视图

视图的这种布局方式被称为视图层次

一个视图可以包含任意数量的子视图，通过为子视图添加子视图的方式，视图可以实现任意深度的嵌套

视图在视图层次中的组织方式决定了在屏幕上显示的内容，原因是子视图总是被显示在其父视图的上方

这个组织方法还决定了视图如何响应事件和变化，每个父视图都负责管理其直接的子视图，即根据需要调整它们的位置和尺寸，以及响应它们没有处理的事件

由于视图对象是应用程序和用户交互的主要途径，所以需要在很多方面发挥作用，下面是其中的一小部分：

## 1. 描画和动画

1. 视图负责对其所属的矩形区域进行描画
2. 某些视图属性变量可以以动画的形式过渡到新的值

## 2. 布局和子视图管理

1. 视图管理着一个子视图列表
2. 视图定义了自身相对于其父视图的尺寸调整行为(自适应)
3. 必要时，视图可以通过代码调整其子视图的尺寸和位置
4. 视图可以将其坐标系统下的点转换为其它视图或窗口坐标系统下的点

## 3. 事件处理

1. 视图可以接收触摸事件
2. 视图是响应者链的参与者

# 2. UIview 的子类

UIView类定义了视图的基本行为，但并不定义其视觉表示

UIKit通过其子类来为像文本框、按键及工具条这样的标准界面元素定义具体的外观和行为

# 3. ViewController 视图控制器

视图和视图控制器紧密协作，管理若干方面的视图行为。

视图控制器的作用是

1. 处理视图的装载与卸载
2. 处理由于设备旋转导致的界面旋转
3. 和用于构建复杂用户界面的高级导航对象进行交互

图控制器的作用
运行在iPhone OS上的应用程序在如何组织内容和如何将内容呈现给用户方面有很多选择。含有很多内容的应用程序可以将内容分为多个屏幕。在运行时，每个屏幕的背后都是一组视图对象，负责显示该屏幕的数据。一个屏幕的视图后面是一个视图控制器其作用是管理那些视图上显示的数据，并协调它们和应用程序其它部分的关系。

UIViewController类负责创建其管理的视图及在低内存时将它们从内容中移出。视图控制器还为某些标准的系统行为提供自动响应。比如，在响应设备方向变化时，如果应用程序支持该方向，视图控制器可以对其管理的视图进行尺寸调整，使其适应新的方向。您也可以通过视图控制器来将新的视图以模式框的方式显示在当前视图的上方。

除了基础的UIViewController类之外，UIKit还包含很多高级子类，用于处理平台共有的某些高级接口。特别需要提到的是，导航控制器用于显示多屏具有一定层次结构的内容；而页签条控制器则支持用户在一组不同的屏幕之间切换，每个屏幕都代表应用程序的一种不同的操作模式。

# 1. UIview 实例化

UIWindow 相当于画板 

UIview 相当于画布

## 1. 控件的位置

iPhone 屏幕的顶部的状态栏高度为20px

### 1. CGRect 结构体

| 距离 | 定义 |
| - | - |
| x | 控件距屏幕左侧的距离 |
| y | 控件距屏幕上方的距离 |
| width | 控件宽度 |
| height | 控件高度 |

bounds 和 frame 都是 CGRect 结构体类型

使用 bounds 和 frame 获取控件的边框大小和画面大小

bounds 为边框大小，其 origin.x 和 origin.y 永远为0

### 2. CGPoint 结构体

center 是 CGPoint 结构体类型

使用 center 属性获取控件的中心点的坐标

### 3. iPhone 的尺寸

| 型号 | 尺寸 | 分辨率 | 倍数 | 尺寸 |
| - | - | - | - | - |
| 3GS | 3.5英寸 | 320 * 480 | @1x | 320 * 480 |
| 4/4s | 3.5英寸 | 320 * 480 | @2x | 640 * 960 |
| 5/5s/5c | 4.0英寸 | 320 * 568 | @2x | 640 * 1136 |
| 6/6s | 4.7英寸 | 375 * 667 | @2x | 750 * 1334 |
| 6plus/6splus | 5.5英寸 | 414 * 736 | @3x | 1242 * 2208 |

图片的命名可以使用 name.png, name@2x.png name@3x.png 的形式

Retina 屏幕会自动选择带有 @2x 的图片，这样布局只需要一套，只是图片需要两套

### 4. UIScreen 类

获取屏幕大小

`float width = [[UIScreen mainScreen] bounds].size.width;`

`float height = [[UIScreen mainScreen] bounds].size.height;`

### 5. 子视图的层级

对于同一个父视图的各个子视图，后加入的子视图会覆盖先前加入的子视图

子视图跟随父视图的层级

正常遍历各个子视图是按照从底层到顶层的顺序

当交换子视图的层级之后，对应的子视图的数组下标也会改变


# 2. UIview 的属性

| 属性 | 说明 |
| - | - |
| superview |  |
| subviews |  |
| tag | 允许相同 |
| frame |  |
| center |  |
| backgroundColor |  |
| superview |  |
| subviews |  |
| autoresizesSubviews |  |
| autoresizingMask |  |


# 3. UIview 的方法

| 方法 | 说明 |
| - | - |
|  bounds |  |
| addSubview |  |
| bringSubviewToFront |  |
| sendSubviewToBack |  |

# 4. UIview 的自适应

子视图跟随父视图自动变化

目前已不再用 UIView 的自适应做适配

而用 autolayout

```
typedef NS_OPTIONS(NSUInteger, UIViewAutoresizing) {
    UIViewAutoresizingNone                 = 0,
    UIViewAutoresizingFlexibleLeftMargin   = 1 << 0,
    UIViewAutoresizingFlexibleWidth        = 1 << 1,
    UIViewAutoresizingFlexibleRightMargin  = 1 << 2,
    UIViewAutoresizingFlexibleTopMargin    = 1 << 3,
    UIViewAutoresizingFlexibleHeight       = 1 << 4,
    UIViewAutoresizingFlexibleBottomMargin = 1 << 5
};
```

# 5. 示例

```
- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    
    // 实例化 UIView 对象
    UIView *view1 = [[UIView alloc] init];
    
    // bounds 的原点坐标永远为0
    float x = [[UIScreen mainScreen] bounds].origin.x;
    float y = [[UIScreen mainScreen] bounds].origin.y;
    
    float width = [[UIScreen mainScreen] bounds].size.width;
    float height = [[UIScreen mainScreen] bounds].size.height;
    NSLog(@"x = %.2f, y = %.2f, width = %.2f, height = %.2f", x, y, width, height);
    
    // 位置和大小
    view1.frame = CGRectMake(20, 20, 340, 600);
    float i = view1.center.x;
    float j = view1.center.y;
    NSLog(@"i = %.2f, j = %.2f", i, j);
    
    // 背景颜色
    view1.backgroundColor = [UIColor grayColor];
    
    // 将视图添加到父视图中
    [self.view addSubview:view1];
    
    // 获取父视图
    UIView *superview1 = view1.superview;
    superview1.backgroundColor = [UIColor whiteColor];
    
    
    
    // 创建子视图
    UIView *view2 = [[UIView alloc] init];
    // 子视图的坐标基于其父视图
    view2.frame = CGRectMake(20, 20, 100, 100);
    view2.backgroundColor = [UIColor redColor];
    view2.tag = 2;
    // 将 view2 添加到 view1
    [view1 addSubview:view2];
    
    // 创建子视图
    UIView *view3 = [[UIView alloc] init];
    view3.frame = CGRectMake(40, 40, 100, 100);
    view3.backgroundColor = [UIColor greenColor];
    view3.tag = 3;
    // 将 view3 添加到 view1
    [view1 addSubview:view3];
    
    // 交换两个子视图的层级，先添加的层级为0，依次递增
    [view1 exchangeSubviewAtIndex:0 withSubviewAtIndex:1];
    
    // 获取多个子视图
    NSArray *subViewArray = view1.subviews;
    for (UIView *view in subViewArray)
    {
        NSLog(@"%.2f", view.frame.origin.x);
//        if (view.tag == 2)
//            view.backgroundColor = [UIColor whiteColor];
    }
    
    // 获取指定子视图
    UIView *subview = [view1 viewWithTag:3];
    subview.backgroundColor = [UIColor orangeColor];
    
    // 子视图的层级
    UIView *view4 = [[UIView alloc] init];
    view4.frame = CGRectMake(200, 60, 100, 100);
    view4.backgroundColor = [UIColor yellowColor];
    [self.view addSubview:view4];
    

    
    UIView *view5 = [[UIView alloc] init];
    view5.frame = CGRectMake(60, 60, 100, 100);
    view5.backgroundColor = [UIColor greenColor];
    
    // 插入视图到指定层
    [view1 insertSubview:view5 atIndex:5];
    // 插入视图到某层上
    [view1 insertSubview:view5 aboveSubview:view2];
    // 插入视图到某曾下
    [view1 insertSubview:view5 belowSubview:view2];
    
    // 将子视图放在父视图中的最顶层
    [view1 bringSubviewToFront:view2];
    // 将子视图放在父视图中的最底层
    [view1 sendSubviewToBack:view3];
    
    // 自适应
    UIView *backview = [[UIView alloc] init];
    backview.frame = CGRectMake([UIScreen mainScreen].bounds.size.width / 2 - 25, 400, 50, 50);
    backview.backgroundColor = [UIColor blackColor];
    backview.autoresizesSubviews = YES;
    backview.tag = 1001;
    [self.view addSubview:backview];
    
    UIView *topview = [[UIView alloc] init];
    topview.frame = CGRectMake(10, 10, 30, 30);
    topview.backgroundColor = [UIColor redColor];
    topview.autoresizingMask = UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleLeftMargin | UIViewAutoresizingFlexibleRightMargin;
    [backview addSubview:topview];
    
    UIButton *btn = [UIButton buttonWithType:UIButtonTypeSystem];
    btn.frame = CGRectMake([UIScreen mainScreen].bounds.size.width / 2 - 25, 630, 50, 20);
    btn.backgroundColor = [UIColor purpleColor];
    [btn addTarget:self action:@selector(btnClick) forControlEvents:UIControlEventTouchUpInside];
    [self.view addSubview:btn];
    
    
}

- (void) btnClick
{
    UIView *view = [self.view viewWithTag:1001];
    view.frame = CGRectMake(view.frame.origin.x - 5, view.frame.origin.y - 5, view.frame.size.width + 10, view.frame.size.height + 10);
}
```

# 6. 参考

[iOS 基础教程之界面初体验](http://www.imooc.com/learn/486)
