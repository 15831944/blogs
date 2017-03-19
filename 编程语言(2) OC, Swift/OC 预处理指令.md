# 预处理指令

`#pragma mark - Table view data source`

1. 用于在类视图中标记名称(tag), 仅用于提高可阅读性
2. Preferences -> Code Sense -> Sort list alphabetically 取消勾选

`#warning`

指定头文件搜索路径

# Prefix 头

项目设置->

定义预处理宏

Build Settings -> Preprocessor Macros ->

1. #import 不会导致重复引用

1. #import 不会导致重复引入头文件(不同于 #include)

```
MAC_OS_X_VERSION_MAX_ALLOWED	// 当前使用的开发环境(SDK)的版本
MAC_OS_X_VERSION_MIN_REQUIRED	// 用来说明使用该 SDK 开发的应用在运行时对系统版本的最低要求
MAC_OS_X_VERSION_10_4			// 系统版本(1040)
```
