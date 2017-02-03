# iOS SDK

Cocoa Touch

Xcode also contains the iOS SDK, which extends Xcode to include the tools, compilers, and frameworks you need specifically for iOS development.

iOS SDK 10

# Toolbar 工具栏

1. 方案(scheme): 目标和构建设置
2. 活动视图(activity viewer): 当前进行的操作
3. 标准编辑器(standard editor): 编辑文件和配置
4. 辅助编辑器(assistant editor): 操作相关联的文件, 支持布局预览(preview)
5. 版本编辑器(version editor): 版本比较

# Navigator 导航视图

1. 项目导航面板(Project Navigator): 项目文件, 可在一个工作区中存放多个项目便于项目之间共享资源, 文件的逻辑分组与文件系统的层级结构无关
2. 符号导航面板(Symbol Navigator): 编译器识别的符号(类, 枚举类型, 结构体, 全局变量等)
3. 查找导航面板(Find Navigator): 查找和替换
4. 问题导航面板(Issues Navigator): 显示错误和警告
5. 测试导航面板(Test Navigator): 单元测试功能
6. 调试导航面板(Debug Navigator): 列出每个活动线程的栈帧
7. 断点导航面板(Breakpoint Navigator): 指向应用程序停止运行(或中断)的代码
8. 日志导航面板(Report Navigator): 构建指令和构建问题

# Editor 编辑器

1. workspace window 用于对项目进行配置
2. 文件跳转: 跳转栏弹出菜单图标包括: Recent Files, Counterparts(关联文件), Superclasses, Subclasses, Siblings(兄弟类), Categories, Includes
3. 跳转栏的弹出菜单图标点击后用于跳转到指定文件, 左右箭头用于跳转到上一个和下一个文件, 分段式弹出菜单表示文件层级

# Utility 实用工具面板

检查器面板(Inspector)

1. File inspector
2. Quick Help inspector
3. Identity inspector
4. Attributes inspector
5. Size inspector
6. Connections inspector

资源库面板(Library)

1. 文件模板库(File Template Library):
2. 代码段库(Code Snippet Library):
3. 对象库(Object Library): 主要来自 iOS 的 UIKit 框架
4. 媒体库(Media Library):

# 类视图

// MARK: - Properties
// MARK: - Initializers
// MARK: - Methods

// TODO:

// FIXME:

# 快捷键

| keystroke             | meaning |
| --------------------- | ------- |
| command-b             | 构建应用
| command-1~8           | 导航面板
| option-command-0      | 实用工具面板
| option-command-1~6    | 检查器面板
| option-command-return | 辅助编辑器
| shift-command-o       | 快速打开(Open Quickly)
| control-option-3      | 资源库面板的搜索栏

# 常用操作

| menu                                  | meaning |
| ------------------------------------- | ------- |
| debug -> clean                        | 清理编译
| Help -> Documention and API Reference | 参考文档
| Preference -> Downloads -> Components | 下载 Command Line Tool 或 Simulator 等

# 单词缩写

| char | meaning  |
| ---- | -------- |
| C    | Class    |
| M    | method   |
| P    | Property |
| V    | variable |

# 真机调试

1. Xcode -> Preferences -> Accounts -> + -> Add Apple ID -> View Details -> Create -> Done
2. Project -> Singing -> Team ->

App ID: Bundle Identifier, profiles

# 属性列表编辑器

# 参考
