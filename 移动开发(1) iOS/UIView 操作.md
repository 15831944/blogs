# 概述

1. iPhone 屏幕的顶部的状态栏高度为20px
2. 使用 UIView 的自适应 autolayout
3. 图片的命名可以使用 name.png, name@2x.png, name@3x.png 的形式, Retina 屏幕会自动选择带有 `@2x` 的图片，plus 会选择@3x
4. bounds 是属性却可以按方法的方式使用?

# UIView

1. 定义一个确定 frame 的视图, 添加到父视图 ViewController 中
2. 子视图的 frame 是相对于其直接的父视图的
3. 同一个父视图中, 后添加的子视图会在视觉上覆盖先添加的
4. 子视图存放在数组中, 层级顺序即为数组元素顺序
5. 层级是跟随父视图的, 父视图的层级低, 其子视图的层级也就低, 即使后加入, 也会被覆盖, 属于不同父视图的子视图之间无关
6. 子视图跟随父视图自动变化, 目前已不再用 UIView 的自适应做适配, 而用 autolayout

## UIView 的属性

1. bounds: 边框大小, CGRect 结构体, 具有 size, bounds.size.width, bounds.size.height, bounds 为 0
2. frame: 画面大小, CGRect 结构体, 具有 size 和 origin, frame.origin.x, frame.origin.y 
3. center: 中心点坐标, CGPoint 结构体, 具有 center.x, center.y
4. backgroundColor
5. superview
6. tag, 唯一标识, 子视图的 tag 值可以相同, 但会导致无法区分
7. autoresizesSubviews
8. autoresizingMask

## UIView 的方法

```
[self.view addSubView: subView];
view.superview;											// 父视图只有一个
NSArray *subViewsArray = view.subviews;					// 子视图有多个, 即使只有一个, 也返回数组
UIView subView = [view viewWithTag: 2];					// 通过 tag 值获取子视图
[view exchangeSubviewAtIndex: 0 withSubviewAtIndex:1];	// 交换子视图的层级, 根据索引值直接交换数组元素位置即可
[view insertSubview: subView atIndex: 1];
[view insertSubview: subView aboveSubview: subView1];
[view insertSubview: subView belowSubview: subView1];
[view bringSubviewToFront: subView];
[view sendSubviewToBack: subView];
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

## UILabel 的属性

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


## UILabel 的方法

```
CGSize size = [label.text sizeWithFont: constrainedToSize: lineBreakMode: ];	// 根据字符串内容获取 label 大小
```

# UIImage

1. 添加图片到工程目录中
1. 一般使用 .png, .jpg 格式的图片, 其中 png 格式可以省略后缀名, 不推荐 .bmp, 颜色显示有问题
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

## UIImageView 的属性

1. animationImages
2. animationDuration
3. animationRepeatCount	// 0值则无限循环, 直到手动停止

## UIImageView 的方法

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
