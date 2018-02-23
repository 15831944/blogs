# 概述

1. 流编辑器, 用于对输入流(文件或管道)执行基本的文本过滤和转换
2. 只扫描一次输入, 更加高效
3. 模式空间: 处理文件中一行内容的一个临时缓冲区。处理完一行之后就会把模式空间中的内容打印到标准输出，然后自动清空缓存。
4. 保持空间: 缓冲区不会自动清空，但也不会主动把此缓冲区中的内容打印到标准输出中。

# Synopsis

sed [OPTION]... {script-only-if-no-other-script} [input-file]...

# Options

| short          | long                | meaning |
| -------------- | ------------------- | ------- |
| -n             | --quiet, --silent   | 不对样式空间进行打印
| -e script      | --expression=script | 为将要执行的命令添加脚本
| -f script-file | --file=script-file  | 为将要执行的命令添加脚本文件的内容
|                | --follow-symlinks   |

# Command Synopsis

| command               | meaning                                           |
| --------------------- | ------------------------------------------------- |
| h H                   | Copy/append pattern space to hold space           |
| g G                   | Copy/append hold space to pattern space           |
| s/regexp/replacement/ | Attempt to match regexp against the pattern space |


# Addresses

# regular expressions

# 参考

[sed高级用法：模式空间(pattern space)和保持空间(hold space)](http://blog.csdn.net/itsenlin/article/details/21129405)
