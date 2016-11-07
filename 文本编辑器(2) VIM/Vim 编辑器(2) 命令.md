# 文件操作

| command | function                 |
| ------- | ------------------------ |
| :n ()   | edit next file           |
| :N ()   | edit previous file       |
| :files  | list all opened files    |
| :sp ()  | split window             |
| :set    | set environment variable |
| :edit   | edit specified file      |
| :saveas | save as                  |
| :file   | rename                   |

# 查找和替换选项

| command    | function                   |
| ---------- | -------------------------- |
| :set ic    | ignore case                |
| :set is    | incsearch                  |
| :set hls   | highlight search result    |
| :set noic  | no ignore case             |
| :set nois  | no incsearch               |
| :set nohls | no highlight search result |
| :noh       | no highlight display       |

# 多文件查找

| command                   | function                        |
| ------------------------- | ------------------------------- |
| :vim/keyword/*            | 查找当前目录下所有文件              |
| :vim/keyword/**           | 查找当前目录及子目录下所有文件        |
| :vim/keyword/**/*.php     | 查找当前目录及子目录下所有 php 文件   |
| :vim/keyword/dir/**/*.php | 查找 dir 目录及子目录下所有 php 文件 |
| :cw                       | 查看搜索结果                       |
| :ccl                      | 关闭搜索结果                       |
| :cn                       | 查找下一个                        |
| :cp                       | 查找上一个                        |

# 单文件替换

| command            | function                        |
| ------------------ | ------------------------------- |
| :s                 | 替换                             |
| :s/old/new         | 将光标所在行第一个 old 替换为 new   |
| :s/old/new/g       | 将光标所在行所有 old 替换为 new     |
| :%s/old/new/g      | 全文执行替换                      |
| :3,10s/old/new/gic | 将第3行到第10行内容替换，忽略大小写，且每个询问是否替换 |

# 多文件替换

| command                     | function           |
| --------------------------- | ------------------ |
| :args filenames             | 选取指定文件到参数列表 |
| :arga filename              | 添加指定文件到参数列表 |
| :argdo %s/old/new/gc update | 对列表中的文件执行批量操作, 这里为执行替换操作, update 会自动保存替换后的文件，否则替换会被中断 |
| :args                       | 查看参数列表         |
| :argd *                     | 清空参数列表         |

# 查找和替换

替换操作会涉及几个常用的标记, g, i, c 可自由组合

| flag | describe      |
| ---- | ------------- |
| %    | 所有行         |
| g    | 单行内所有匹配项 |
| i    | 忽略大小写      |
| c    | 确认是否替换    |

# 编辑器配置

| command           | function           |
| ----------------- | ------------------ |
| :set autowrite    | 自动保存文件         |
| :set noautowrite  |                    |

# 参考

1. [vim查找和替换详解](http://blog.csdn.net/zcube/article/details/42710141)
2. [谁说vim不是IDE](http://www.cnblogs.com/chijianqiang/archive/2012/10/30/vim-1.html)
