# 编辑器基础

1. buffer: 文件缓冲区, 指加载到内存中的显示在一个标签页中的某个文件
1. pane: 面板, 包括标签栏, 行数槽(gutter), 状态栏, 编辑区域等
1. 粒度, 指光标一次跳一个字符, 一个单词还是一行, 选择到文件首, 文件尾等

# 设计细节

1. Atom 原生是为 Mac 开发的, Mac 上使用 cmd 键的一些快捷键在 Windows 上无法使用
1. atom 基于 Chromium Embedded Framework, 就好像一个运行在本地的浏览器
1. 如果你打开了不同文件夹中的同名文件, 文件名后会提示出这个文件所属的文件夹
1. 如果你打开一个文件, 默认会把这个文件所在的文件夹当做项目目录放在目录树视图面板中
1. 临时显示的面板的标题会以斜体显示（也即挂起的面板, 目的是防止出现过多的标签, 类似于浏览器的在当前标签打开）, 固定打开的面板会以常规字体显示
1. Vim, Sublime, Atom 等等的编辑器的配置文件都是 UNIX 风格的纯文本格式, 可以在 github 上找到已有的配置文件, 利用 git 命令直接 clone 到自己的配置文件路径中
1. 配置文件及插件都集中存放在 ~/.atom 文件夹中

# 快捷键

1. 在 settings 面板中的 keybindings 可以查看所有的快捷键
2. 快捷键的名称的作用是在你不记得快捷键的情况下, 可以通过命令面板直接输入命令名, 进行相应的操作
3. 用户自定义的快捷键会覆盖系统默认快捷键
4. 快捷键配置文件是 `~/.atom/keymap.cson`

## 光标移动

我是在 keybinding 中搜索 move-to- 这个关键字来获得以下快捷键的, 更多快捷键请自行检索

| keystroke     | command                          | 含义解析 |
| ------------- | ---------------------------------| ---------------- |
| alt-b(ack)    | editor:move-to-beginning-of-word | 移动到当前单词起始处 |
| alt-f(orward) | editor:move-to-end-of-word       | 移动到当前单词结束处 |
| ctrl-end      | core:move-to-bottom              | 移动到文件底部 |
| ctrl-home     | core:move-to-top                 | 移动到文件首 |

## 编辑操作

| keystroke       | command                           | 含义解析 |
| --------------- |---------------------------------- | ---------- |
| cmd-p           | fuzzy-finder:toggle-file-finder   | 快速打开文件 |
| shift-cmd-p     | command-palette:toggle            | 命令面板 |
| cmd-enter       | newline-blow                      | 在下一行创建新行 |
| shift-cmd-enter | newline-above                     | 在上一行创建新行 |
| cmd-]           | indent-selected-rows              | 缩进 |
| cmd-[           | outdent-selected-rows             | 反缩进 |
| command -/=     |                                   | 调节字号 |
| ctrl-tab        | pane:show-next-recently-used-item | 切换标签 |
| cmd-j           | editor:join-lines                 | 将当前行和下一行合并 |
| cmd-l           | editor:select-line                | 选择当前行 |
| cmd-click       |                                   | 多点编辑 |
| cmd-d           | find-and-replace:select-next      | 多次按可以选中多个字符串 |
| ctrl-m          |                                   | 跳转到匹配括号 |
| ctrl-alt-m      |                                   | 选择光标所在的匹配括号中的内容 |
