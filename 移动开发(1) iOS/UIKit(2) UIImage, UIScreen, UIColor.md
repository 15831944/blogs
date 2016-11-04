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

# iPhone 的尺寸

| model        | size | resolution | times | size        |
| ------------ | ---- | ---------- | ----- | ----------- |
| 3GS          | 3.5  | 320 * 480  | @1x   | 320 * 480   |
| 4/4s         | 3.5  | 320 * 480  | @2x   | 640 * 960   |
| 5/5s/5c      | 4.0  | 320 * 568  | @2x   | 640 * 1136  |
| 6/6s         | 4.7  | 375 * 667  | @2x   | 750 * 1334  |
| 6plus/6splus | 5.5  | 414 * 736  | @3x   | 1242 * 2208 |

# 控件的位置

1. iPhone 屏幕的顶部的状态栏高度为20px
4. 图片的命名可以使用 name.png, name@2x.png name@3x.png 的形式, Retina 屏幕会自动选择带有 `@2x` 的图片，这样布局只需要一套，只是图片需要两套

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
