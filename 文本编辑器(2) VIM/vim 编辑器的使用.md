1. 查阅程序员手册
2. 系统配置和管理

# 1 常用快捷键

| keystroke             | describe           |
| --------------------- | ------------------ |
| v (visual char)       | 可视字符(高亮选择字符) |
| V (visual line)       | 可视行(高亮选择行)    |
| ctrl-v (visual block) | 可视块(高亮选择块)    |
| y (yank)              | 复制选择             |
| d (delete)            | 删除选择             |
| p                     | 粘贴到光标后         |
| P                     | 粘贴到光标前         |
| u (undo)              | 撤销                |
| ctrl-r (redo)         | 重做                |
| /keyword              | 从光标位置向后搜索关键词 |
| ?keyword              | 从光标位置向前搜索关键词 |
| n                     | 查找下一个            |
| N                     | 查找上一个            |

# 2 常用命令

| command                       | function                       |
| --------------------------- | -------------------------------- |
| :n (next file)                | 编辑下一个文件                   |
| :N (previous file)            | 编辑上一个文件                   |
| :files                        | 列出当前打开的所有文件             |
| :sp (split)                   | 分离窗口                         |
| :set                          | 设置环境变量                     |
| :edit                         | 编辑另一个文件                   |
| :saveas                       | 另存为                          |
| :file                         | 重命名                          |
| 查找和替换相关配置               |                                |
| :set ic (ignore case)         | 查找时忽略大小写                  |
| :set is (incsearch)           | 边输入边显示匹配结果               |
| :set hls (highlight search)   | 高亮显示匹配结果                  |
| :set noic (ignore case)       | 取消查找时忽略大小写               |
| :set nois (incsearch)         | 取消边输入边显示匹配结果            |
| :set nohls (highlight search) | 取消高亮显示匹配结果                |
| :noh (no highlight)           | 暂时取消高亮显示                   |
| 多文件查找                      |                                 |
| :vim/keyword/*                | 查找当前目录下所有文件              |
| :vim/keyword/**               | 查找当前目录及子目录下所有文件        |
| :vim/keyword/**/*.php         | 查找当前目录及子目录下所有 php 文件   |
| :vim/keyword/dir/**/*.php     | 查找 dir 目录及子目录下所有 php 文件 |
| :cw                           | 查看搜索结果                       |
| :ccl                          | 关闭搜索结果                       |
| :cn                           | 查找下一个                        |
| :cp                           | 查找上一个                        |
| 单文件替换                      |                                  |
| :s                            | 替换                             |
| :s/old/new                    | 将光标所在行第一个 old 替换为 new  |
| :s/old/new/g                  | 将光标所在行所有 old 替换为 new  |
| :%s/old/new/g                 | 全文执行替换 |
| :3,10s/old/new/gic            | 将第3行到第10行内容替换，忽略大小写，且每个询问是否替换 |
| 多文件替换 |  |
| :args filenames               | 选取指定文件到参数列表 |
| :arga filename                | 添加指定文件到参数列表 |
| :argdo %s/old/new/gc update   | 对列表中的文件执行批量操作, 这里为执行替换操作, update 会自动保存替换后的文件，否则替换会被中断 |
| :args                         | 查看参数列表                              |
| :argd *                       | 清空参数列表                              |

# 3 常用设置

| command           | function           |
| ----------------- | ------------------ |
| :set autowrite    | 自动保存文件         |
| :set noautowrite  |                    |
| :              |          |

# 4 查找和替换

替换操作会涉及几个常用的标记, g, i, c 可自由组合  

| flag | describe      |
| ---- | ------------- |
| %    | 所有行         |
| g    | 单行内所有匹配项 |
| i    | 忽略大小写      |
| c    | 确认是否替换    |

# 参考

[vim查找和替换详解](http://blog.csdn.net/zcube/article/details/42710141)

VIM 用户手册
VIM 参考手册
鸟哥的Linux私房菜
