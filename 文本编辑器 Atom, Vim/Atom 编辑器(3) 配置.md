# 核心设置项 Core Settings

以下是与文本编辑无关的Atom的核心设置项, 独立的包有各自的附加配置项

1. Allow Pending Pane items: 单击目录树视图中的文件时, 以斜体的面板标题的悬挂面板进行预览, 而不是固定的标签页
2. Audio Beep: 动作未执行或执行失败时, 触发系统警告提示音
3. Auto Hide Menu Bar: 自动隐藏菜单栏, 按Alt键进行切换. 仅windows和Linux支持此功能.
4. Automatically Update: 有新版本可用时自动升级.
5. Close Deleted File Tabs: 文件在外部被删除时关闭其所在标签页
6. Close Empty Windows: 向没有标签或面板的窗口发出“关闭标签”命令时, 关闭该窗口. (Ctrl+W)
7. Remove Empty Panes: 面板上最后一个标签被关闭时, 移除该面板
8. Exclude VCS Ignored Paths:  “模糊搜索”和“查找替换”这样的包会忽略当前VCS系统忽略的文件和路径,在.gitigonre文件中定义了其忽略的路径
9. File Encoding: 读写文件时默认使用的字符集编码格式. 统一码一般用UTF-8, 它使用3个字节表示一个字符,  简体中文用 GBK 国标码, 繁体中文用 big5
1. Follow Symlinks: 查找文件和用 fuzzy finder 打开文件时, 跟随符号链接. 符号连接相当于 windows 下的快捷方式.
1. Ignored Names: 通配符样式列表. 匹配这些样式的文件和目录会被某些packa忽略
1. Open Empty Editor On Start: 启动时自动打开一个空白的编辑器.
1. Project Home: 项目应该放置的目录. 用 Package Generator 创建的 Package 默认会被存储在这里.
1. Reopen Project Menu Count: 最近打开项目数量
1. Restore Previous Windows On Start: 启动时载入之前的窗口
1. Send Telemetry to the Atom Team: 发送错误报告
1. Use Proxy Setting When Calling APM: 调用 APM 时使用代理设置
1. Warn On Large File Limit: 超过打开文件大小限制时发出警告

# 编辑器设置项 Editor Settings

以下设置与文本编辑相关. 其中一些设置在特定语言基础上会被覆盖. 单击 Packages list 中的语言包卡片来查看语言设置.

1. Auto Indent: 输入新行时自动缩进光标.
2. Auto Indent On Paste: 基于上一行的缩进自动缩进粘贴的文本.
3. Back Up Before Saving: 通过制作一个临时的备份的副本来确保在发生I/O错误时文件内容不丢失.
4. Confirm Checkout HEAD Revision: 检测首版本和放弃自从上次提交的当前文件的变化时, 显示确认对话框.
5. Font Family: 用于文本编辑的字体库的名称. 直接输入字体名称即可, 例如 source code pro, 当然, 系统中要安装有此字体.
6. Font Size: 编辑器文本的以像素数计算的高度.
7. Invisibles
指定当 Show Invisibles 配置使能时, 用于渲染回车字符(微软风格的行结束符)的字符.
Invisibles Eol: 指定当 Show Invisibles 配置使能时, 用于渲染换行符(\n)的字符.
Invisibles Space: 指定当 Show Invisibles 配置使能时, 用于渲染引导空格和结尾空白的字符.
Invisibles Tab: 指定当 Show Invisibles 配置使能时, 用于渲染硬制表符的字符.
8. Line Height: 行间距默认当前字号的1.5倍.
9. Non Word Characters: 用来定义单词边界的非字母符号.
1. Preferred Line Length: 如果设置了自动换行, 则指定到达多少的字符后就自动换行.
1. Scroll Past End: 允许编辑器向下滚动过文件的最后一行.
1. Scroll Sensitivity: 滚动的灵敏度.
1. Show Indent Guide: 在编辑器中显示缩进指引.
1. Show Invisibles: 为不可见字符提供占位符.
1. Show Line Numbers: 显示行号
1. Soft Tabs: 即用 space 代替 tab, 当你按下 tab 时, 实际会被空格代替. 若 tab 类型配置为自动, 且buffer中tab类型检测失败, 那么此配置项决定tab键按下时, 实际输入哪种类型.
1. Soft Wrap: 自动折行, 一行内容超过窗口宽度时, 就会折到下一行进行显示, 但实际上还是会当作一行来处理. 若 Soft Wrap At Preferred Line Length 已设置, 则按指定字符数折行.
1. Soft Wrap At Preferred Line Length: 按指定字符数折行.
1. Soft Wrap Hanging Indent: 缩进的字符数.
1. Tab Length: 用多少个空格代替tab.
1. Tab Type: tab类型.
1. Undo Grouping Interval: 多少毫秒内, 文本编辑会被计入撤消历史.
1. Use Shadow DOM: DOM是文档对象模型, 用来获取或设置文档中标签的属性, 例如获取或者设置input表单的value值.
1. Zoom Font When Ctrl Scrolling: 用Ctrl和鼠标滚轮调整字号.

# 系统设置项 System Settings

以下配置项决定如何与操作系统成为一体

1. Register as file handler: 文件打开方式
2. Show in file context menus: 使用 Atom 打开文件
3. Show in folder context menus: 使用 Atom 打开文件夹
