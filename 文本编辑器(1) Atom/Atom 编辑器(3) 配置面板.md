本文完整翻译自atom的设置界面，注意红色字体的解释即可。

<font color=red>有个有趣的发现，settings 面板上的文字是可以拖动的，可以直接拖到 QQ 的聊天窗口变成txt格式的文本。</font>

# Core settings

These are Atom's core setting which affect behavior unrelated to text editing. Individual packages might have additional config settings of their own. Check individual package settings by clicking its package card in the Packages list.

以下是与文本编辑无关的Atom的核心设置项。个别的 package 可能有它们自己的附加的配置项。可以在package列表中查看这些 package。

## 1. Allow Pending Pane items

Allow items to be previewed without adding them to a pane permanently, such as when single clicking files in the tree view.

自动挂起面板允许在没有永久性的添加一个项目到面板的情况下，预览该项目，例如在目录树视图下单击文件时。

<font color=red>选定此项则单击的文件会在同一个面板标签页下显示该文件内容，否则会为每个文件各自打开一个标签页。</font>

## 2. Audio Beep

Trigger the system's beep sound when certain actions cannot be execulted of ther are no result.

动作未执行或执行失败时，触发系统警告提示音。

## 3. Auto Hide Menu Bar

Automatically hide the menu bar and toggle it by pressing Alt. This is only supported on Windows % Linux.

自动隐藏菜单栏，并且按Alt键切换。仅windows和Linux支持此功能。

## 4. Automatically Update

Automatically update Atom when a new release is avaliable.

有新版本可用时自动升级。

## 5. Close Empty Windows

向没有标签或面板的窗口发出“关闭标签”命令时，关闭该窗口。(Ctrl+W)

## 6. Remove Empty Panes

when the last tab of a pane is closed, remove that pane as well.

面板上最后一个标签被关闭时，移除该面板。

## 7. Exclude  VCS Ignored Paths

Files and directions ignored by the current project's VCS system will be ignored by some packages, such as the fuzzy finder and find and replace. For example, projects using Git have thers paths defined in the .gitignore file. Individual packages might have additional config settings for ignoring VCS ignored files and folders.

被当前项目的版本控制系统忽略的文件和位置会被一些package忽略，比如 “模糊搜索”和“查找替换”。例如，使用Git的项目保在.gitigonre文件中定义了其忽略的路径。个别packag可能有他们额外的对于忽略版本控制系统忽略的文件和文件夹的配置选项。

<font color=red>这些只有在你的源码文件夹由 git 控制的时候才会有影响。</font>


## 8. File Encoding

Default character set encoding to use when reading and writing files.

读写文件时默认使用的字符集编码格式。

<font color=red>统一码一般用UTF-8，它使用3个字节表示一个字符， 汉语有的可能会选择GBK，它是国标码。</font>

## 9. Follow Symlinks

follow symbolic links when searching files and when opening files with the fuzzy finder.

查找文件和用 fuzzy finder 打开文件时，跟随符号链接。

<font color=red>符号连接相当于 windows 下的快捷方式。</font>

## 10. Ignored Names

List of string glob patterns. Files and directories matching these patterns will be ignored by some packages, such as the fuzzy finder and tree view. Individual packages might have additional config settings for igonring names.

通配符样式列表。匹配这些样式的文件和目录会被某些packa忽略，比如 fuzzy finder 和 tree view. 个别packa可能对忽略名称有额外的配置选项。

<font color=red>查找字符是希望被忽略的项，例如版本文件，备份文件等。</font>

## 11. Open Empty Editor On Start

Automatically open an empty editor on startup.

启动时自动打开一个空白的编辑器。

## 12. Project Home

The directory where projects are assumed to be located. Packages created using the Package Generator will be stored here default.

项目应该放置的目录。用 Package Generator 创建的 Package 默认会被存储在这里。

# Editor Settings

These config settings are related to text editing. Some of these settings can be overriden on a per-language basis. Check language setting by clicking the language's package card in the Packages list.

以下设置与文本编辑相关。其中一些设置在特定语言基础上会被覆盖。单击 Packages list 中的语言包卡片来查看语言设置。

## 1. Auto Indent

Automatically indent the cursor when inserting a newline.

输入新行时自动缩进光标。

## 2. Auto Indent On Paste

Automatically indent pasted text based on the indentation of the previous line.

基于上一行的缩进自动缩进粘贴的文本。

## 3. Back Up Before Saving

Ensure file contents aren't lost if there is an I/O error during save by making a temporary backup copy.

通过制作一个临时的备份的副本来确保在发生I/O错误时文件内容不丢失。

## 4. Confirm Checkout HEAD Revision

Show confirmation dialog when checking out the HEAD revision and discarding changes to current file since last commit.

检测首版本和放弃自从上次提交的当前文件的变化时，显示确认对话框。

## 5. Font Family

The name of the font family used for editor text.

用于文本编辑的字体库的名称。

<font color=red>直接输入字体名称即可，例如 source code pro，当然，系统中要安装有此字体。</font>

## 6. Font Size

Height in pixels of editor text.

编辑器文本的以像素数计算的高度。


## 7. Invisibles

Invisibles Cr

Character used to render carriage return characters(for microsoft-style line endings) when the Show Invisibles setting is enabled.

指定当 Show Invisibles 配置使能时，用于渲染回车字符(微软风格的行结束符)的字符。

Invisibles Eol

Character used to render newline characters(\n) when the Show Invisibles setting is enabled.

指定当 Show Invisibles 配置使能时，用于渲染换行符(\n)的字符。

Invisibles Space

Character used to render leading and trailing space characters when the show Invisibles setting is enabled.

指定当 Show Invisibles 配置使能时，用于渲染引导空格和结尾空白的字符。


Invisibles Tab
Character used to render hard tab characters(\t) when the Show Invisibles setting is enabled.

指定当 Show Invisibles 配置使能时，用于渲染硬制表符的字符。

## 8. Line Height

Height of editor lines, as a multiplier of font size.

行间距默认当前字号的1.5倍。

## 9. Non Word Characters

A string of non-word characters to define word boundaries.

用来定义单词边界的非字母符号。

## 10. Preferred Line Length

Identifies the length of a line which is used when wrapping text with the Soft Wrap At Preferred Line Length setting enabled, in number of characters.

如果设置了自动换行，则指定到达多少的字符后就自动换行。

## 11. Scroll Past End

Allow the editor to be scrolled past the end of the last line.

允许编辑器向下滚动过文件的最后一行。

## 12. Scroll Sensitivity

Determines how fast the editor scrolls when using a mouse or trackpad.

滚动的灵敏度。

## 13. Show Indent Guide

Show indentation indicators in the editor.

在编辑器中显示缩进指引。

## 14. Show Invisibles

Render placeholders for invisible characters, such as tabs, spaces and newlines.

为不可见字符提供占位符。

## 15. Show Line Numbers

Show line numbers in the editor's gutter.

显示行号

## 16. Soft Tabs

If the Tab Type config setting is set to "auto" and autodetection of tab type from buffer content fails, then this config setting determines whether a soft tab or a hard tab will be inserted when the Tab key is pressed.

若 tab 类型配置为自动，且buffer中tab类型检测失败，那么此配置项决定tab键按下时，实际输入哪种类型。

## 17. Soft Wrap

Wraps lines that exceed the width of the window. When Soft Wrap At Preferred Line Length is set, it will wrap to the number of characters defined by the Preferred Line Length setting.

对超过窗口宽度的行进行折行。若 Soft Wrap At Preferred Line Length 已设置，则按指定字符数折行。

## 18. Soft Wrap At Preferred Line Length

Instead of wrapping lines to the window's width, wrap lines to the number of characters defined by the Preferred Line Length setting. This will only take effect when the soft wrap config setting is enabled globally or for the current language.

按指定字符数折行。

## 19. Soft Wrap Hanging Indent

When soft wrap is enabled, defines length of additional indentation applied to wrapped lines, in number of characters.

缩进的字符数。

## 20. Tab Length

Number of spaces used to represent a tab.

用多少个空格代替tab。

## 21. Tab Type

Determine character inserted when Tab key is pressed. Possible values: "auto", "soft" and "hard". When set to "soft" or "hard", soft tabs (spaces) or hard tabs (tab characters) are used. When set to "auto", the editor auto-detects the tab type based on the contents of the buffer (it uses the first leading whitespace on a non-comment line), or uses the value of the Soft Tabs config setting if auto-detection fails.

tab类型。

<font color=red>建议设置为hard。</font>

## 22. Undo Grouping Interval

Time interval in milliseconds within which text editing operations will be grouped together in the undo history.

 多少毫秒内，文本编辑会被计入撤消历史。

## 23. Use Shadow DOM

Disable if you experience styling issues with packages or themes. Be sure to open an issue on the relevant package or theme, because this option is going away eventually.


<font color=red>DOM是文档对象模型，用来获取或设置文档中标签的属性，例如获取或者设置input表单的value值。</font>

## 24. Zoom Font When Ctrl Scrolling

Change the editor font size when pressing the Ctrl key and scrolling the mouse up/down.

用Ctrl和鼠标滚轮调整字号。
