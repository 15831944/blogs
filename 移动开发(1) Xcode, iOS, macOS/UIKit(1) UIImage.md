# UIImage

图片的加载

1. 每次都重新加载，耗费加载时间，适合大图片
2. 加载到内存，耗费内存资源，适合频繁使用的小图片

```
UIImage *image1 = [[UIImage alloc] initWithContentsOfFile:imagePath];
UIImage *image2 = [UIImage imageNamed:@"101"];
```

# 控件的位置

1. iPhone 屏幕的顶部的状态栏高度为20px
2. CGRect 结构体: bounds 和 frame 都是 CGRect 结构体类型, 使用 bounds 和 frame 获取控件的边框大小和画面大小, bounds 为边框大小，其 origin.x 和 origin.y 永远为0
3. CGPoint 结构体: center 是 CGPoint 结构体类型, 使用 center 属性获取控件的中心点的坐标
4. 图片的命名可以使用 name.png, name@2x.png name@3x.png 的形式, Retina 屏幕会自动选择带有 `@2x` 的图片，这样布局只需要一套，只是图片需要两套

# 序列图

1. 将图片对象存入数组，进行动画播放
