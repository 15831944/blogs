# UIWindow

1. Mac 中一般是多窗口应用，表示为 NSWindow 类的多个实例, NSWindow 继承自 NSResponder
2. iOS 中一般是单窗口应用，表示为 UIWindow 类的单个实例, UIWindow 继承自 UIView 继承自 UIResponder, 即窗口也是视图对象
3. UIWindow 对象并没有像关闭框或标题栏这样的视觉装饰，用户不能直接对其进行关闭或最小化等操作, 所有对窗口的操作都需要通过其编程接口来实现, 通常不必直接操作 UIWindow 对象中与 UIView 视图有关的属性变量

UIWindow 的作用

1. 作为容器，用来放置标签，按钮等子控件，或者说添加一或多个视图, 即为内容显示提供背景平台, 窗口显示出来之后，很少需要再次引用它
2. 传递触摸消息，应用程序可以借助窗口对象来进行事件传递，窗口对象会持续跟踪当前的第一响应者对象，并在 UIApplication 对象提出请求时将事件传递它
3. 协同控件做出响应，例如旋转手机时横屏竖屏的切换
4. UIWindow 的初始的边框尺寸总是应设置为整个屏幕的大小, 除了屏幕矩形之外，没有理由传入其它边框矩形
5. 如果窗口从 xib 文件装载得到，Interface Builder 并不允许创建比屏幕尺寸小的窗口, 如果窗口通过编程方式创建, 则必须在创建时传入期望的边框矩形

UIWindow 的属性

1. backgroundColor
2. windowLevel

UIWindow 的级别

1. 视图通过窗口进行显示, 3个级别可以同时显示在屏幕上，同一个级别的 window 可以有多个实例化对象, 但同一时刻只能显示一个

| level                  | 作用                  |
| ---------------------- | -------------------- |
| UIwindowLevelAlert     | 用于显示重要的警告      |
| UIwindowLevelStatusBar | 用于显示屏幕上方的状态栏 |
| UIwindowLevelNormal    | 应用程序窗口           |

UIWindow 的实例化

```
_window = [[UIWindow alloc] initWithFrame: [[UIScreen mainScreen] bounds]];
_window.backgroundColor = [UIColor whiteColor];
[_window makeKeyAndVisible];
UIViewController* vc = [[UIViewController alloc]initWithNibName:nil bundle:nil];
[_window setRootViewController:vc];
```

# UIScreen

```
CGFloat h = [[UIScreen mainScreen] bounds].size.height;		// 获取屏幕大小
CGFloat w = [[UIScreen mainScreen] bounds].size.width;
NSLog(@"witdh = %f, height = %f", w, h);
```

# UIColor

1. 设置颜色的方法是静态方法

| method                            | meaning        |
| --------------------------------- | -------------- |
| clearColor                        | 透明色          |
| redColor                          | 红色            |
| colorWithRed: green: blue: alpha: | RGB 颜色及透明度 |

# UIFont

```
[UIFont systemFontOfSize: 25];			// 字号
[UIFont boldSystemFontOfSize: 25];		// 粗体
[UIFont italicSystemFontOfSize: 25]		// 斜体
for (NSString *fontName in [UIFont familyNames])	// 系统字体库
[UIFont fontWithName: size:];			// 字体
```

# UILabel

1. UILabel 默认也是透明的

UILabel 的属性

| property      | meaning |
| ------------- | ------- |
| text          | 文本内容 |
| textColor     | 文本颜色 |
| textAlignment | 文本布局 |
| alpha         | 透明度，整个 Label，包括文本和背景 |
| font          | 字体及字号(斜体对中文无效) |
| shadowColor   | 文本阴影颜色 |
| shadowOffset  | 文本阴影偏移位置 |
| lineBreakMode | 断行模式, 按单词换行, 按字符换行 |
| numberOfLines | 限制行数(设置为0或-1表示不限制行数) |


UILabel 的方法

```
CGSize size = [label.text sizeWithFont: constrainedToSize: lineBreakMode: ];	// 根据字符串内容获取 label 大小
```

# UIImage

1. 添加图片到工程目录中
1. 一般使用 .png, .jpg 格式的图片, 其中 png 格式可以省略后缀名, 不推荐 .bmp, 颜色显示有问题
3. 图片的命名可以使用 name.png, name@2x.png, name@3x.png 的形式, Retina 屏幕会自动选择带有 `@2x` 的图片，plus 会选择 `@3x`
1. 原生不支持 gif, 可使用 SDWebImage 动态加载

```
NSString *projectPath = [[NSBundle mainBundle] resourcePath];					// 获取工程路径
NSString *imagePath = [NSString stringWithFormat: @"%@/name.png", projectPath];	// 获取图片路径
UIImage *image1 = [[UIImage alloc] initWithContentsOfFile:imagePath];			// 每次都重新加载，耗费加载时间，适合高清图片
UIImage *image1 = [[UIImage alloc] initWithData: ];								// 加载二进制格式的图片文件
UIImage *image2 = [UIImage imageNamed:@"pngname"];	// 加载到内存，耗费内存资源，程序结束才会释放, 适合频繁使用的小图片, 如表情
```

# UIImageView

1. UIImageView 是图片的载体, 图片需要载体才能显示在屏幕上
2. 载体可以是 UIImageView，可以是 Button 等
3. 载体控制屏幕上显示的图片的大小和模式, content Mode 是 UIView 的方法
4. 序列图: 将图片对象存入可变数组，进行动画播放

UIImageView 的属性

1. animationImages
2. animationDuration
3. animationRepeatCount	// 0值则无限循环, 直到手动停止

UIImageView 的方法

```
startAnimating
stopAnimating
```

| Content Mode                     | meaning  |
| -------------------------------- | -------- |
| UIViewContentModeScaleToFill     | 拉伸(默认) |
| UIViewContentModeCenter          | 居中      |
| UIViewContentModeScaleAspectFit  | 按短边填充 |
| UIViewContentModeScaleAspectFill | 按长边填充 |

```
UIImageView * imageView = [[UIImageView alloc] initWithImage: image];	// 声明载体
imageView.frame = CGMake(10, 10, image.size.witdh, image.size.height);	// 获取指定位置, 按图片大小
[self.view addSubView: imageView];
[NSMutableArray *imageArray = [[NSMutableArray alloc] init];
for (int = 1; i <= 13; i++)
{
	UIImage *image = [UIImage imageNamed:[NSString stringWithFormat: @"png%d.png", i]];
	[imageArray addObject: image];
}
```

# 选取器 UIPickerView

1. 选取器是带有可旋转刻度盘的控件, 可以配置为一个或多个刻度盘(或组件, component), 用于显示文本和图像

日期选取器(Date Picker): 本身维护着日期数据, 无须委托和数据源
选取器视图(Picker View): 选取器本身不保存任何数据, 而是向它的控制器(数据源和委托)请求数据, 使用关联检查器进行关联委托和数据源视图控制器

# 选取器委托和数据源

1. 每个组件可具有独立的数据列表
2. 日期选取器不需要配置委托和数据源
3. 选取器将一些工作分配给它的委托, 委托可以确定为选取器的每个滚轮的每一行绘制的内容, 选取器从委托获取数据
4. 数据源: 选取器通过数据源获知滚轮数量和每个滚轮中的行数, 在预先指定的时刻调用委托方法, 数据源是控制器的一部分, 而不是模型的一部分, 模型用于存储数据, 虽然作为数据源的控制器可以存储数据(例如硬编码的数组), 但实际用于从模型(例如属性列表, 文件, URL 载入, 动态组合或计算)中检索数据, 并传递给选取器, 遵循 IPickerViewDataSource 协议的方法必须实现, 在视图被激活时被执行
5. 委托: 委托和数据源可以是同一对象, 一般是包含选取器视图的视图控制器, UIViewController 的子类, 遵循 IPickerViewDelegate 协议, 方法至少实现一个, 在滚轮变化时被执行
6. 遵循对应协议的控制器即是该选取器的委托和数据源

```
func numberOfComponents(in pickerView: UIPickerView) -> Int {}
func pickerView(_ pickerView: UIPickerView, numberOfRowsInComponent component: Int) -> Int {}

func pickerView(_ pickerView: UIPickerView, titleForRow row: Int, forComponent component: Int) -> String? {}
```

# UITableView

1. 表视图只能有一列, 但行数没有限制, 不负责存储表中的数据, 只存储足够绘制当前可见行的数据
2. 表视图从遵循 UITableViewDelegate 协议的对象获取配置数据, 从遵循 UITableViewDataSource 协议的对象获得行数据
3. 表视图有分组表(grouped table), 无格式表(plain table)两种基本样式, 使用索引的无格式表称为索引表(indexed table), 数据源提供的信息用于使用右侧的索引在列表中进行导航, 
4. 数据源的分区(section): 分组表的一组, 索引表的没给索引都是分区
5. 表单元标识符: 不同类型的单元需要使用不同的表单元标识符

表视图单元样式

1. 图像
2. 文本标签
3. 详细文本标签

default: 文本标签在左, 图像在左, 没有详细文本标签
subtitle: 文本标签在左上, 详细文本标签在左下, 有图像
value1: 文本标签在左, 详细文本标签在右, 有图像
value2: 文本标签在详细文本标签左侧, 没有图像

定制表视图单元格式

1. 在创建单元时通过程序向 UITableViewCell 添加子视图
2. 从 nib 文件中加载单元
3. 从 storyboard 中加载单元

UITableView 的方法

```
// Returns a reusable table-view cell object for the specified reuse identifier and adds it to the table.
UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:HomeCellIdentifier forIndexPath:indexPath];
```

# UITableViewCell

1. UITableView 是由一系列 UITableViewCell 组成的列表, 每个 UITableViewCell 对象可以包含图像, 文本, 可选附加图标, 可以添加子视图, 放置更多数据, 可以在创建单元格时在程序中添加子视图或从 storyboard, nib 文件加载
2. identifier: 用于标识 cell 对象

作用

1. setting and managing cell content and background (including text, images, and custom views)
2. managing the cell selection and highlight state
3. managing accessory views
4. initiating the editing of the cell contents

UITableViewCell 的属性

1. textLabel, detailTextLabel, imageView: set the text and images of the cell
2. contentView: add subviews
3. backgroundView:
4. backgroundColor:

UITableViewCell 的方法

```
- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
```

# 表视图委托和数据源

6. 遵循对应协议的控制器即成为该表视图的委托或数据源
2. 数据源提供了绘制表所需的所有数据
3. 委托用于配置表视图的外观并处理某些用户交互

# 参考

1. [UITableViewCell - UIKit | Apple Developer Documentation](https://developer.apple.com/reference/uikit/uitableviewcell)
1. [UITableView 系列之自定义 UITableViewCell](http://www.cnblogs.com/wzrong/p/3261130.html)
1. [趣味苹果开发](http://www.cnblogs.com/liufan9/tag/TableViewController/)
1. [UIWindow 与 UIView 深层解析](http://blog.csdn.net/gf771115/article/details/7761904)
1. [ios view的frame和bounds之区别（位置和大小）](http://blog.csdn.net/mad1989/article/details/8711697)
