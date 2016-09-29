# 1. 概念 CONCEPT

## 1. 匹配器 Matcher

匹配器就是查找文本所用的正则表达式的种类。好比用 google 搜索还是用 baidu 搜索。

## 2. 匹配控制 Matching Control

匹配控制就是匹配的规则，如何匹配。匹配哪个或哪些样式，匹配样式来自输入还是来自文件，匹配样式是否忽略大小写，获取满足匹配的文本还是获取不满足匹配的文本，按单词匹配或者按行匹配。

## 3. 输出控制 Output Control

正常情况下，输出打印的是满足选项和样式的行。但是，我们有时候不需要显示每个行，或者满足条件的行太多，我们只需要统计满足的行数即可。或者我们查找的是多个文件，不必打印每个文件的所有匹配行，只需要知道哪些文件符合匹配，打印出匹配的文件名即可。或者我们只关心匹配的前几行。或者我们想忽略掉错误信息的输出。因此不再显示正常的输出，而是输出我们指定的内容。

## 4. 上下文行 Context Line

有时我们不只关心匹配的那一行，还关心匹配行的前几行或后几行，例如我找到一个段 的标题行，我还要知道这个标题下面的几行内容的情况。

# 2. 语法 SYNOPSIS

两种类型的语法：

1. 选项 输入样式 目标文件 目标文件
2. 选项 输入样式 输入样式 文件样式 文件样式 目标文件 目标文件

一定要看清除规律，区分样式和目标文件。[-f FILE] 指的是样式，而不是要查找的文件。

注意 grep 可以进行多文件查找。

```
grep [OPTIONS] PATTERN [FILE...]
grep [OPTIONS] [-e PATTERN]...  [-f FILE]...  [FILE...]



```

# 3. 描述 DESCRIPTION

grep  searches  the  named input FILEs for lines containing a match to the given PATTERN.  If no files are specified, or if the file "-" is given, grep searches standard input.  By default, grep prints the matching lines.

grep 搜索 FILEs 文件并获取匹配 PATTERN 的行。如果没有指定文件或文件以"-"形式给出，则搜索标准输入。默认下，grep 打印匹配的行。

In addition, the variant programs egrep, fgrep and rgrep are the same  as  grep -E,  grep -F,  and  grep -r,  respectively.   These  variants  are deprecated, but are provided for backward compatibility.

另外，变体程序 egrep, fgrep and rgrep 分别同 grep -E,  grep -F,  and  grep -r. 不建议使用这些变体，但是为了向后兼容性，依然会提供。

# 4. 选项 OPTIONS

##  1. <font color=red>通用程序信息 Generic Program Information

### 1. --help
Output a usage message and exit.

### 2. -V, --version
Output the version number of grep and exit.

##  2. <font color=red>匹配器选择 Matcher Selection

匹配器有基本正则表达式匹配，扩展正则表达式匹配，Perl 正则表达式匹配和普通固定文本匹配。

默认情况下，输入的样式被当作基本正则表达式处理，即 -G 选项默认开启，如果不想使用正则表达式，可以使用 -F 选项。

### 1. -E, --extended-regexp

Interpret PATTERN as an extended regular expression (ERE, see below).

将 PATTERN 解释为扩展的正则表达式。

### 2. -F, --fixed-strings

Interpret PATTERN as a list of fixed strings (instead of regular expressions), separated by newlines, any of which is to be matched.

将 PATTERN 解释为固定的字符串的列表（禁用正则表达式），使用换行符分离，每个字符串都会被匹配。

### 3. -G, --basic-regexp

Interpret PATTERN as a basic regular expression (BRE, see below).  This is the default.

将 PATTERN 解释为基础的正则表达式。这是默认的。

### 4. -P, --perl-regexp

Interpret  PATTERN  as  a  Perl  regular  expression  (PCRE, see below).  This is highly experimental and grep -P may warn of unimplemented features.

将 PATTERN 解释为 Perl 正则表达式。这是高度实验性的选项，可能会警告为未生效的特性。

## 3. <font color=red>匹配控制 Matching Control

### 1. -e PATTERN, --regexp=PATTERN

Use PATTERN as the pattern.  Multiple -e can be used to specify different search patterns.  This option is also useful to protect a pattern beginning with a hyphen (-).

默认情况下，命令后面接一个 PATTERN，如果想使用多个 PATTERN，则可以使用多个 -e 选项指定不同的搜索样式。匹配到的样式都会被打印出来。

这个选项也可以用于保护以连字符号打头的样式。即以连字符号开头的文件不会被误认为是参数。

### 2. -f FILE, --file=FILE

Obtain patterns from FILE, one per line.  The empty file contains zero patterns, and therefore matches nothing.  Multiple -f can be used to
specify different files.

从文件获得样式，每个样式占一行。空文件不包含样式因此无法匹配。多个-f选项可以用于指定多个文件。
即可以把样式存储在文件中，方便日后使用。

### 3. -i, --ignore-case

Ignore case distinctions in both the PATTERN and the input files.

输入样式和样式文件均忽略大小写。

### 4. -v, --invert-match

Invert the sense of matching, to select non-matching lines.

颠倒匹配的识别，用于选择不匹配指定样式的行。

### 5. -w, --word-regexp

Select only those lines containing matches that form whole words.  The test is that the matching substring must either be at the  beginning of  the  line,  or preceded by a non-word constituent character.  Similarly, it must be either at the end of the line or followed by a non-
word constituent character.  Word-constituent characters are letters, digits, and the underscore.

仅选择匹配整个单词的行。
匹配子字符串的测试必须要么在行的开始，要么在非打印字符前面。
类似的，它必须要么在行的末尾，要么跟在非打印字符的后面。
可打印字符包括字母，数字和下划线。

### 6. -x, --line-regexp

Select only those matches that exactly match the whole line.  For a regular expression pattern, this is like parenthesizing the pattern and then surrounding it with ^ and $.

仅选择匹配整个行的行。
对于正则表达式样式来说，这就像给样式加上括号然后用^和$围起来。

### 7. -y     

Obsolete synonym for -i.

旧式的等同于 -i 的选项。

## 4. <font color=red>通用输出控制 General Output Control

### 1. -c, --count

Suppress normal output; instead print a count of matching lines for each input file.  With the -v, --invert-match option (see below), count non-matching lines.

阻止正常的输出，而是打印匹配每个输入文件的行的个数。

使用 -v 选项则对非匹配行计数。

### 2. --color[=WHEN]

Surround the matched (non-empty) strings, matching lines, context lines, file names, line numbers, byte offsets, and separators (for fields and  groups  of  context  lines) with escape sequences to display them in color on the terminal.  The colors are defined by the environment variable GREP_COLORS.  The deprecated environment variable GREP_COLOR is still supported, but its setting does not have priority.  WHEN  is never, always, or auto.

使用转义序列包围匹配的非空字符串，匹配行，上下文行，文件名，行号，字节偏移和分隔符，来在终端上用颜色显示他们。颜色由 GREP_COLORS 环境变量定义。
不被推荐使用的 GREP_COLOR 环境变量依然被支持，但是他的设置不具有优先级。

### 3. -L, --files-without-match

Suppress normal output; instead print the name of each input file from which no output would normally have been printed.  The scanning will stop on the first match.

阻止正常输出，而是打印每个正常情况下不会打印输出的输入文件的名字。
找到第一个匹配则停止扫描。

即在找到需要的匹配前，打印扫描到的文件的名字，以告诉用户扫描正在进行。

### 4. -l, --files-with-matches

Suppress normal output; instead print the name of each input file from which output would normally have been printed.   The  scanning  will
stop on the first match.

阻止正常输出，而是打印每个正常情况下会打印输出的输入文件的名字。

找到第一个匹配则停止扫描。

<font color=red>即找到第一个符合匹配的文件，并打印这个文件名。

### 5. -m NUM, --max-count=NUM

Stop  reading a file after NUM matching lines.  If the input is standard input from a regular file, and NUM matching lines are output, grep
ensures that the standard input is positioned to just after the last matching line before exiting, regardless of the presence  of  trailing
context  lines.   This  enables  a  calling  process to resume a search.  When grep stops after NUM matching lines, it outputs any trailing
context lines.  When the -c or --count option is also used, grep does not output a count greater than NUM.  When the -v  or  --invert-match
option is also used, grep stops after outputting NUM non-matching lines.

只读取前 NUM 个匹配的行。

### 6. -o, --only-matching

Print only the matched (non-empty) parts of a matching line, with each such part on a separate output line.

只打印匹配行的匹配部分。每个匹配部分占一个输出行。

我猜应该是适合一行中有多个匹配的情况。

### 7. -q, --quiet, --silent

Quiet;  do  not write anything to standard output.  Exit immediately with zero status if any match is found, even if an error was detected.
Also see the -s or --no-messages option.

静默模式，不向打印任何输出。

### 8. -s, --no-messages

Suppress error messages about nonexistent or unreadable files.

不输出不存在或不可读文件的相关的错误信息。

## 5. 输出行前缀控制 Output Line Prefix Control

## 6. 上下文行控制 Context Line Control

### 1. -A NUM, --after-context=NUM

Print NUM lines of trailing context after matching lines.  Places a line containing a group separator (--)  between  contiguous  groups  of
matches.  With the -o or --only-matching option, this has no effect and a warning is given.

打印匹配行的下面 NUM 个行。

### 2. -B NUM, --before-context=NUM

Print  NUM  lines  of  leading context before matching lines.  Places a line containing a group separator (--) between contiguous groups of
matches.  With the -o or --only-matching option, this has no effect and a warning is given.

打印匹配行的上面 NUM 个行。

### 3. -C NUM, -NUM, --context=NUM

Print NUM lines of output context.  Places a line containing a group separator (--) between contiguous groups of matches.  With the  -o  or
--only-matching option, this has no effect and a warning is given.

打印匹配行的上面和下面各 NUM 个行。

## 7. 文件和目录选择 File and Directory Selection

## 8. 其他选项 Other Options
