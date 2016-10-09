C_INCLUDE_PATH

CPLUS_INCLUDE_PATH

LIBRARY_PATH

PS1 prompt symbol 命令提示符1

# 环境变量内容的修改（关键字紧跟在变量名后面）：

| 命令 | 作用 |
| --- | --- |
| #  | 删除从左至右数的匹配样式的最短的字符串 |
| ## | 删除从左至右数的匹配样式的最长的字符串 |
| %  | 删除从后往前数的匹配样式的最短的字符串 |
| %% | 删除从后往前数的匹配样式的最长的字符串 |
| /  | 将首个第一个 / 后面的字符串替换为第二个 / 后面的字符串 |
| // | 将第一个 // 后面的字符串全部替换为第二个 / 后面的字符串 |

# 将 express 赋值给 varible 变量的测试条件：

| 命令 | 表达式 | 作用 |
| --- | --- | --- |
| - | variable=${string-express} | 若string不存在则成功设置新值expression，否则取string的值 |
| + | variable=${string+express} | 若string存在则成功设置新值expression，否则取空字符串 |
| = | variable=${string=express} | 若string不存在则成功设置新值expression，否则取string的值; 若strig不存在则string也设置新值expression，否则sting值不变 |
| ? | variable=${string?express} | 若string存在则成功设置为string，否则输出错误expression |

# 参考

《鸟哥的 Linux 私房菜》
