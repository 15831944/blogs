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

UIview 的属性

| property            | describe |
| ------------------- | -------- |
| superview           |  |
| subviews            |  |
| tag                 | 允许相同 |
| frame               |  |
| center              |  |
| backgroundColor     |  |
| superview           |  |
| subviews            |  |
| autoresizesSubviews |  |
| autoresizingMask    |  |

UIview 的方法

| method              | describe |
| ------------------- | -------- |
| bounds              |  |
| addSubview          |  |
| bringSubviewToFront |  |
| sendSubviewToBack   |  |

UIview 的自适应

1. 子视图跟随父视图自动变化, 目前已不再用 UIView 的自适应做适配, 而用 autolayout

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
