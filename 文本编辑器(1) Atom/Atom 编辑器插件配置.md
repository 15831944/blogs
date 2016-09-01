
# 1. 插件基础

由于 UNIX 一起皆文件。将整个 .atom 配置文件夹放到 github 上有一个很大的好处，就是你更改了任何配置，github 上都会显示出确切的文件修改，非常有助于初学者的学习。当然，还有利于在不同平台切换的时候，可以导入导出配置。

本文汇集了我自己在使用过程中添加的插件和配置方法。Atom 编辑器的功能几乎都是由插件实现的，包括最基本的查找和替换功能，如果你不喜欢原装的，甚至都可以替换掉。因此，了解每个快捷键是来自于哪个插件是很必要的。



# 2. 插件配置

## 1. 核心插件 Core Packages

核心插件一般是 atom 官方提供的插件和你在安装 atom 编辑器是自带的插件。

### 1. <font color=red> 目录树视图 tree-view

如何在目录树视图中仅显示源文件等特定类型文件？

tree-view 是 atom 自带的目录树视图面板，当你打开一个文件，它会显示文件所在目录下的所有文件，这是一个很棒的特性，但是文件夹内通常除了源文件，还会存在目标文件等这些平时不需要显示的文件，可以设置隐藏指定类型的文件。

先在配置面板中找到

`Igonred Names`

编辑你要忽略的文件类型

`.git, .hg, .svn, .DS_Store, ._*, Thumbs.db, *.o, *.gdb, *.txt`

再在 tree-view 中勾选

`Hide Igonred Names`

### 2. <font color=red> 符号视图 symbols-view

用来查看函数列表和跳转到匹配变量和函数。

`ctrl-r`

### 3. <font color=red> 模糊查找 fuzzy-finder

用来查看最近的文件和跳转到匹配文件。

`ctrl-p`

### 4. <font color=red> 查找和替换 Find And Replace

#### 1. Close Project Find Panel After Search

Close the find panel after executing a project-wide search.

在执行一次项目查找后，关闭查找面板。

#### 2. Focus Editor After Search

Focus the editor and select the next match when a file search is executed. If no matches are found, the editor will not be focused.

执行一次文件搜索后，聚焦在编辑器并且选择下一个匹配。如果没有找到匹配，则不会聚焦到编辑器。

#### 3. Live Search Minimum Characters

The minimum number of characters which need to be typed into the buffer find box before search starts matching and highlighting matches as you type.

输入几个字符后，开始进行匹配和高亮。

#### 4. Open Project Find Results In Right Pane

当执行项目查找时，在一个分割的面板中显示结果。

### 5. <font color=red> 命令面板 Command Palette

快捷键 ctrl-shift-p 可以用来执行任何命令。

第一个好处是有助于你记忆快捷键。

第二个好处是即使一个命令没有快捷键，你也可以找到并执行它，随后也可以根据需要为其配置一个快捷键。

### 6. <font color=red> VIM 模式 vim-mode

vim 就不多解释了，问题是 vim 和 一般 GUI 下的软件的操作习惯完全不同，建议如果确定要用 vim，就完全放弃其他类型的操作，屏蔽掉其他插件的快捷键，例如就不要再用 ctrl-c 当做复制操作了，等等。二选一，否则会很混乱。

### 7. <font color=red> Markdown 预览 markdown-preview

使用快捷键 ctrl-shift-m 可以像一般编辑器那样，左侧是原始文本，右侧是 rendered version.

### 8. <font color=red> 拼写检查 spell-check

在编辑普通文本时，文本下方会出现红色波浪线，代表拼写错误。

关闭这个插件，即可退出拼写检查，去掉红色波浪线。

### 9. <font color=red> 语法选择器 grammar-selector

语法选择器，平时在右下角会显示出当前检测文本是哪种语言，手动修改可以直接点击修改或使用 `ctr-shift-l` 快捷键。

### 10. <font color=red> 空白字符 whitespace

默认当你保存或者退出的时候，编辑器会帮你删除文件尾的空行，可以取消以下选项禁用死从能。

`Remove Trailing whitespace`

### 11. <font color=red> 书签 bookmarks

没有添加书签这一快捷键，因此用 toggle 来添加或删除书签

`ctrl-alt-f2`

### 12. <font color=red> 括号匹配 bracket-matcher

使用 `ctrl-m` 来回跳转到匹配括号

使用 `ctrl-alt-m` 选择光标所在括号中的内容

### 13. <font color=red> 字符编码选择器 encoding-selector

使用 `ctrl-shift-u` 打开字符编码列表

### 14. <font color=red> 代码段 snippets

使用 `alt-shift-s` 查看当前可支持的代码段列表

输入 `html` 并回车，会自动扩展代码段

### 15. <font color=red> 自动补全 autocomplete

输入 `ctrl-space` 默认会提示当前 buffer 中的字符串

## 2. 社区插件 Community Packages

社区插件为第三方插件。

### 1. <font color=red> symbols-tree-view

描述：a symbols view like taglist.

作者：xndcn

此插件相当于 ultraedit 中的 function list 或者是 vim 中的 taglist。
作用是默认在右侧显示变量和函数。
在 AutoHideTypes 中输入 variable，隐藏变量的显示，仅显示函数列表
在 Keybindings 中复制 keymap，并粘贴到自己的 keymap file 中，输入自定义的快捷键。

```
'atom-workspace':
  'F8': 'symbols-tree-view:toggle'



```

### 2. <font color=red> project-find-navigation

描述：improve project-find-result navigation by dirty hack.

作者：t9md

在项目中搜索时，显示 Project Find Results 面板，使用快捷键进行导航。

### 3. <font color=red> activate-power-mode

描述：Activae POWER MODE to write your code in style.

作者：JoelBesada

装逼利器，不用解释。。




## 3. 开发者插件 Development Packages




## 4. Git 插件 Git Packages
