# 核心插件 Core Packages

核心插件一般是 atom 官方提供的插件和你在安装 atom 编辑器时自带的插件

## 目录树视图 tree-view

1. tree-view 是 atom 自带的目录树视图面板, 当你打开一个文件, 它会显示文件所在目录下的所有文件
2. 文件夹内通常除了源文件, 还会存在目标文件等这些平时不需要显示的文件, 可通过勾选 `Hide Igonred Names` 隐藏指定类型的文件

## 符号视图 symbols-view

用来查看符号列表, 跳转到匹配变量或函数

`ctrl-r`

## 模糊查找 fuzzy-finder

用来查看最近的文件和跳转到匹配文件, 若搜索的文件名后面接冒号及数字, 则打开的文件会直接定位在该行, 接"@"符号, 则会定位在指定函数名(仅在 sublime 中支持)

`ctrl-p`

## 查找和替换 Find And Replace

1. Close Project Find Panel After Search	在执行一次项目查找后, 关闭查找面板
2. Focus Editor After Search				执行一次文件搜索后, 聚焦在编辑器并且选择下一个匹配, 如果没有找到匹配, 则不会聚焦到编辑器
3. Live Search Minimum Characters			至少输入几个字符后, 开始进行匹配和高亮
4. Open Project Find Results In Right Pane	当执行项目查找时, 在一个分割的面板中显示结果

## 命令面板 Command Palette

命令面板有助于你记忆快捷键, 即使一个命令没有快捷键, 你也可以找到并执行它, 随后也可以根据需要为其配置一个快捷键

`ctrl-shift-p`

## VIM 模式 vim-mode

vim 就不多解释了，问题是 vim 和 一般 GUI 下的软件的操作习惯完全不同，建议如果确定要用 vim，就完全放弃其他类型的操作，屏蔽掉其他插件的快捷键，例如就不要再用 ctrl-c 当做复制操作了，等等。二选一，否则会很混乱。

## Markdown 预览 markdown-preview

左侧是原始文本，右侧是 rendered version

`ctrl-shift-m`

## 拼写检查 spell-check

在编辑普通文本时, 文本下方会出现红色波浪线, 代表拼写错误, 关闭这个插件, 即可退出拼写检查, 去掉红色波浪线

## 语法选择器 grammar-selector

语法选择器，平时在右下角会显示出当前检测文本是哪种语言，手动修改可以直接点击修改或使用快捷键

`ctr-shift-l`

## 空白字符 whitespace

默认当你保存或者退出的时候, 编辑器会帮你删除文件尾的空行, 可以取消 `Remove Trailing whitespace` 选项禁用此功能

## 书签 bookmarks

没有添加书签这一快捷键, 因此用 toggle 来添加或删除书签

`ctrl-alt-f2`

## 括号匹配 bracket-matcher

1. 使用 `ctrl-m` 来回跳转到匹配括号
2. 使用 `ctrl-alt-m` 选择光标所在括号中的内容

## 字符编码选择器 encoding-selector

打开字符编码列表

`ctrl-shift-u`

## 代码段 snippets

如输入 `html` 并回车, 会自动扩展代码段

`alt-shift-s`

## 自动补全 autocomplete

提示当前 buffer 中的字符串

`ctrl-space`

## Keybinding resolver

Show what commands a keybinding resolves to

如果你按下快捷键之后没有执行命令，或者执行了错误的命令，那个键位的快捷键可能出了些问题。Atom自带keybinding resolver，一个小巧的包来帮助你理解执行了哪个快捷键。






# 社区插件 Community Packages

社区插件是第三方插件

## symbols-tree-view

1. 相当于 ultraedit 中的 function list 或者是 vim 中的 taglist, 作用是默认在右侧显示变量和函数
2. 在 AutoHideTypes 中输入 variable class, 隐藏变量的显示, 仅显示函数列表

## project-find-navigation

在项目中搜索时, 在 Project Find Results 面板中, 使用快捷键进行导航

## activate-power-mode

装逼利器

## language-viml

vim 脚本语言语法高亮

# 参考

1. [Atom飞行手册翻译： 3.7 调试](https://segmentfault.com/a/1190000003058018)
