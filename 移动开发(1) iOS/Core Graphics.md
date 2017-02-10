# Core Graphics

Core Graphics 绘图框架提供了更底层的库用于创建基于路径的复杂图形

1. 抗锯齿渲染
2. 添加梯度、图片和颜色
3. 使用坐标空间转换(coordinate-space transformations)
4. 创建、显示和分析PDF文档

# Quartz 2D

1. C 语言的 API 集合, 包含各种函数, 数据类型(CGPoint, CGFloat), 对象, 可在内存中直接绘制视图和对象
2. 虚拟画布: 遵循绘画模式
3. 视图: 向图形所在的 UIView 视图的 drawRect 方法添加绘图代码, 在视图被重新绘制前被调用
4. 图形环境(graphics context): 相当于画布, 先获取当前环境, 通过环境来调用各类 Quartz 函数, 由环境负责将图形绘制在视图上, 可使用系统默认环境, 也可自行创建
5. 坐标系统: 原点位于左上角, CGRect, CGPoint, CGSize
6. 颜色: UIColor 是 CGColor 的容器, 笔刷颜色, 填充颜色
7. 色彩模型(color model): 色彩空间(color sapce), 使用红, 绿, 蓝, 不透明度(alpha)4个元素表示颜色, CGFloat 类型值, 0.0~1.0 取值范围, 称为限定(clamped)浮点变量
8. 色域(gamut): 加法三原色(Additive Primary Colors)混合生成的颜色
9. 形状: 弧形, 贝塞尔路径(Bezier Path)

# 计算机图形学色彩模型

0. RGB:
1. HSV: 色相, 饱和度, 色明度
2. HSL: 色调, 饱和度, 亮度
3. CMYK: 蓝绿色, 洋红色, 黄色, 黑色, 应用于四色平板印刷
4. 灰度级

# 参考

官方文档 QuartzDemo
