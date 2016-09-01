# 进程标识

| PID | 进程 | 作用 |
| - | - | - |
| 0 | 内核交换进程 swapper | 调度进程，系统进程，内核的一部分 |
| 1 | init 进程 | 在自举过程结束后由内核调用，启动一个 UNIX 系统，以超级用户权限运行 |
| 2 | 页守护进程 page daemon | 支持虚拟存储器系统的分页操作 |

# 终止状态

| 进程终止原因 | 含义 | 取得退出状态 exit status、信息编号 signal number | 含义 |
| - | - |
| WIFEXITED(status) | 正常终止的子进程 normal termination | WEXITSTATUS(status) | 获取 exit 参数的低8位 |
| WIFSIGNALED(status) | 异常终止的子进程 abnormal termination | WTERMSIG(status) WCOREDUMP(status) | 获取子进程终止的信息编号 获取进程终止的 core 文件 |
| WIFSTOPPED(status) | 当前暂停的子进程 child stopped | WSTOPSIG(status) | 获取子进程暂停的信息编号 |
| WIFCONTINUED(status) | 作业控制暂停后继续的子进程 |  |  |