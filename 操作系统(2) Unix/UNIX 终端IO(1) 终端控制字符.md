可用 stty 命令设置终端输入环境

| 按键 | 功能 | 说明 |
| - | - | - |
| <font color=red>ctrl-c</font> | 中断 intr | 送出一个中断**信号**给目前正在运行的进程（不可以是后台进程） |
| <font color=red>ctrl-\\</font> | 退出 quit | 终止目前的命令，会向进程发**信号** |
| ctrl-? | 删除 erase | 向后删除字符 |
| <font color=red>ctrl-u</font> | kill | 删除在目前命令行上的所有文字，在提示符下，将整行命令删除 |
| ctrl-d | eof = | end of file 输入结束 |输入结束(EOF)，例如邮件结束的时候 |
| undef | eol |  |
| undef | eol2 |  |
| undef | swtch |  |
| <font color=red>ctrl-q</font> | start | 在某个进程停止以后，重新启动它的输出，恢复屏幕的输出 |
| <font color=red>ctrl-s</font> | stop | 停止目前屏幕的输出，暂停屏幕的输出 |
| <font color=red>ctrl-z</font> | susp | 送出一个terminal stop 的信号给正在运行的进程，暂停（挂起）目前的命令 |
| ctrl-r | reprint |
| ctrl-w | wearse | 删除一个单词 |
| ctrl-v | inext |
| ctrl-o | flush |
| ctrl-m | 就是Enter |
| 1 | min |
| 0 | time | 