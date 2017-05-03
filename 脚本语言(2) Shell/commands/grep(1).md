# 语法 Synopsis

```
grep [选项] 输入样式 [目标文件...]
grep [选项] [-e 输入样式]...  [-f 文件样式]...  [目标文件...]
```

# 描述 Description

grep 搜索目标文件并获取匹配样式的行。如果没有指定文件或文件以"-"形式给出，则搜索标准输入。默认下，grep 打印匹配的行.

# 选项 Options

1. 通用程序信息 Generic Program Information
2. 匹配器选择 Matcher Selection
3. 匹配控制 Matching Control
4. 通用输出控制 General Output Control
5. 输出行前缀控制 Output Line Prefix Control
6. 上下文行控制 Context Line Control
7. 文件和目录选择 File and Directory Selection
8. 其他选项 Other Options

# 匹配器选择 Matcher Selection

1. 匹配器就是查找文本所用的正则表达式的种类, 包括: 基本正则表达式匹配(默认), 扩展正则表达式匹配, Perl正则表达式匹配, 普通固定文本匹配(不使用正则表达式).
2. -G, --basic-regexp, 将 PATTERN 解释为基本正则表达式
3. -E, --extended-regexp, 将 PATTERN 解释为扩展的正则表达式
4. -P, --perl-regexp, 将 PATTERN 解释为 Perl 正则表达式
5. -F, --fixed-strings, 将 PATTERN 解释为固定的字符串的列表（禁用正则表达式），使用换行符分离，每个字符串都会被匹配

# 匹配控制 Matching Control

匹配控制指匹配的规则: 匹配一个或多个样式, 匹配样式来自输入或文件, 匹配样式是否忽略大小写, 获取匹配的或不匹配的文本, 按单词匹配或按行匹配.

1. -e, 指定多个输入样式
2. -f(file), 从文件获得样式，每个样式占一行
3. -i(ignore), 输入样式和样式文件均忽略大小写
4. -v(invert), 倒匹配的识别，用于选择不匹配指定样式的行
5. -w(word), 匹配整个单词
6. -x, 匹配整个行, 相当于正则表达式样式加上括号然后用^和$围起来

# 通用输出控制 General Output Control

默认输出是满足选项和样式的行. 输出控制可输出满足的行数, 多个文件中匹配的文件名, 匹配的前几行, 不输出错误信息, 即输出指定内容而非默认输出.

1. -c(count), 匹配每个输入文件的行数, 使用 -v 选项则对非匹配行计数
2. --color[=WHEN], 匹配结果带颜色
3. -L, --files-without-match, 打印扫描过程中的文件名, 直到找到第一个匹配
4. -l, --files-with-matches, 只打印第一个匹配的文件名
5. -m NUM, --max-count=NUM, 只读取前 NUM 个匹配的行。
6. -o, --only-matching, 只打印匹配行的匹配部分, 每个匹配部分占一个输出行
7. -q, --quiet, --silent, 静默模式，不向打印任何输出。
8. -s, --no-messages, 不输出不存在或不可读文件的相关的错误信息。

# 上下文行控制 Context Line Control

上下文行的意思是, 有时我们不只关心匹配的那一行，还关心匹配行的前几行或后几行，例如我找到一个段的标题行，我还要知道这个标题下面的几行内容的情况.

1. -A NUM, --after-context=NUM, 打印匹配行的下面 NUM 个行
2. -B NUM, --before-context=NUM, 打印匹配行的上面 NUM 个行
3. -C NUM, -NUM, --context=NUM, 打印匹配行的上面和下面各 NUM 个行

# 参考

1. man grep
