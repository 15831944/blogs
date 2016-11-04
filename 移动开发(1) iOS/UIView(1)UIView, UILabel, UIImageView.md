# UIView

1. 定义一个确定 frame 的视图, 添加到父视图 ViewController 中
2. 子视图的 frame 是相对于其直接的父视图的
3. 同一个父视图中, 后添加的子视图会在视觉上覆盖先添加的
4. 子视图存放在数组中, 层级顺序即为数组元素顺序
5. 层级是跟随父视图的, 父视图的层级低, 其子视图的层级也就低, 即使后加入, 也会被覆盖, 属于不同父视图的子视图之间无关
6. 子视图跟随父视图自动变化, 目前已不再用 UIView 的自适应做适配, 而用 autolayout

# UIView 的属性

1. bounds: 边框大小, CGRect 结构体, 具有 size, bounds.size.width, bounds.size.height, bounds 为 0
2. frame: 画面大小, CGRect 结构体, 具有 size 和 origin, frame.origin.x, frame.origin.y 
3. center: 中心点坐标, CGPoint 结构体, 具有 center.x, center.y
4. backgroundColor
5. superview
6. tag, 唯一标识, 子视图的 tag 值可以相同, 但会导致无法区分
7. autoresizesSubviews
8. autoresizingMask

# UIView 的方法

```
[self.view addSubView: subView];
view.superview;								// 父视图只有一个
NSArray *subViewsArray = view.subviews;		// 子视图有多个, 即使只有一个, 也返回数组
UIView subView = [view viewWithTag: 2];		// 通过 tag 值获取子视图
[view exchangeSubviewAtIndex: 0 withSubviewAtIndex:1];	// 交换子视图的层级, 根据索引值直接交换数组元素位置即可
[view insertSubview: subView atIndex: 1];
[view insertSubview: subView aboveSubview: subView1];
[view insertSubview: subView belowSubview: subView1];
[view bringSubviewToFront: subView];
[view sendSubviewToBack: subView];
```

# iPhone 的尺寸

1. iPhone 屏幕的顶部的状态栏高度为20px
2. 图片的命名可以使用 name.png, name@2x.png name@3x.png 的形式, Retina 屏幕会自动选择带有 `@2x` 的图片，这样布局只需要一套，只是图片需要两套

| model        | size | resolution | times | size        |
| ------------ | ---- | ---------- | ----- | ----------- |
| 3GS          | 3.5  | 320 * 480  | @1x   | 320 * 480   |
| 4/4s         | 3.5  | 320 * 480  | @2x   | 640 * 960   |
| 5/5s/5c      | 4.0  | 320 * 568  | @2x   | 640 * 1136  |
| 6/6s         | 4.7  | 375 * 667  | @2x   | 750 * 1334  |
| 6plus/6splus | 5.5  | 414 * 736  | @3x   | 1242 * 2208 |

# 屏幕适配

1. 使用 UIView 的自适应

# UIScreen

```
UIView *view1 = [[UIView alloc] init];
view1.frame = CGRectMake(100, 20, 50, 100);
view1.backgroundColor = [UIColor redColor];
[self.view addSubview: view1];

CGFloat h = [[UIScreen mainScreen] bounds].size.height;		// 获取屏幕大小
CGFloat w = [[UIScreen mainScreen] bounds].size.width;
NSLog(@"witdh = %f, height = %f", w, h);
```

# UIColor

UIColor 的方法

| method                            | meaning        |
| --------------------------------- | -------------- |
| clearColor                        | 透明色          |
| redColor                          | 红色            |
| colorWithRed: green: blue: alpha: | RGB 颜色及透明度 |

# UIImage

图片的加载

1. 每次都重新加载，耗费加载时间，适合大图片
2. 加载到内存，耗费内存资源，适合频繁使用的小图片

```
UIImage *image1 = [[UIImage alloc] initWithContentsOfFile:imagePath];
UIImage *image2 = [UIImage imageNamed:@"101"];
```

# 序列图

1. 将图片对象存入数组，进行动画播放

## UILabel

1. UILabel 默认是透明的

UILabel 属性

| property      | meaning |
| ------------- | ------- |
| text          | 文本内容 |
| textColor     | 文本颜色 |
| textAlignment | 文本布局 |
| alpha         | 透明度，整个 Label，而非只是本文或控件 |
| font          | 字体及字号(斜体对中文无效) |
| shadowColor   | 文本阴影颜色 |
| shadowOffset  | 文本阴影偏移位置 |
| lineBreakMode | 断行模式 |
| numberOfLines | 行数(设置为0或-1表示不限制行数) |


## UIImageView

1. UIImageView 是图片的载体, 图片需要载体才能显示在屏幕上
2. 载体可以是 UIImageView，可以是 Button 等
3. 载体控制屏幕上显示的图片的大小

| Content Mode                     | meaning |
| -------------------------------- | ------- |
| UIViewContentModeScaleToFill     | 拉伸(默认) |
| UIViewContentModeCenter          | 居中      |
| UIViewContentModeScaleAspectFit  | 按短边填充 |
| UIViewContentModeScaleAspectFill | 按长边填充 |
