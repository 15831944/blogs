# 手写纯代码方式

使用代码手写UI及布局, 在 AppDelegate 类的 didFinishLaunchingWithOptions: 函数中初始化 UIWindow

优势

1. 适合大型项目, 有利于版本管理, 检查追踪, 代码合并
2. 代码重用性高, 适合编写高度重用的控件, 如 UIView 的子类
3. 功能强大, 能够完成 xib 或者 StoryBoard 做不了的事情

劣势

1. 布局困难, 可借助 Reveal 或者 RestartLessOften 之类的工具

# Interface Builder 和 xib

1. User interfaces are actually archived Cocoa or Cocoa Touch objects (saved as .nib files)
使用单个 xi b文件组织 viewController 或者 view , 应用程序在启动后, 从 xib 文件创建窗口

优势

1. 良好的 MVC 设计模式: 一个 xib 文件对应一个 ViewController, 对于自定义的 view, 也使用单个 xib 文件并从 main bundle 进行加载的方式来载入, Interface Builder 帮助完成 view 的创建, 布局和与 file owner 的关系映射等一些列工作, xib 文件都是 view 的内容, 有助于建立起较好的 MVC 的概念

劣势

1. xib 与代码结合

# storyboard

1. 使用 StoryBoard 来通过单个或很少的几个文件构建全部 UI, storyboard 的本质是 xml 文件
2. StoryBoard 可以看做是一组 viewController 对应的 xib, 以及它们之间的转换方式的集合
3. 在 StoryBoard 中不仅可以看到每个 ViewController 的布局样式, 也可以明确地知道各个 ViewController 之间的转换关系

优势

1. 代码需求少
2. API 简单

劣势

1. 使用多个 storyboard 进行协作开发

# Main.storyboard

1. 最新版本中, 默认使用 main.storyboard(可视化开发工具) 初始化 UIWindow, 将 Deployment Info 中的 main interface 指定为空, 则可以在上述函数中手动进行初始化 UIWindow
2. The main storyboard is what your app actually displays when the app is running. It contains your app, code, and logic.

# LaunchScreen.storyboard

1. The launch screen is what first appears when the user taps the app icon before the app is finished launching.
2. It shows a single, static screen. It can't be dynamic and it can't use any custom classes or code. It's the replacement for launch images.

# 参考

博客

1. [代码手写UI，xib和StoryBoard间的博弈，以及Interface Builder的一些小技巧](https://onevcat.com/2013/12/code-vs-xib-vs-storyboard/)
1. [Storyboards & XIBs: Best Practices](https://mobilejazz.com/blog/storyboards-xibs-best-practices/)
1. [iOS 开发可视化编程之Xib 简述](http://www.jianshu.com/p/ea3f90cc744b)

stackoverflow

1. [What is the difference between launchscreen.storyboard and main.storyboard](http://stackoverflow.com/questions/34891481/what-is-the-difference-between-launchscreen-storyboard-and-main-storyboard)

Apple Developer Documentation

1. [Xcode - Interface Builder - Apple Developer](https://developer.apple.com/xcode/interface-builder/)
