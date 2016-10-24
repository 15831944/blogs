# Synopsis

ps [-AaCcEefhjlMmrSTvwXx] [-O fmt | -o fmt] [-G gid] [-g grp] [-u uid] [-p pid] [-t tty] [-U user]
ps [-L]

# Options

-A, 显示其他用户的进程信息
-a, 显示所有用户的拥有控制终端(controlling terminal)的进程信息
-U, 显示属于指定真实用户ID的进程信息
-u, 显示属于指定用户名的进程信息
-X  对用其他选项匹配的信息忽略没有控制终端的进程
-x, 对用其他选项匹配的结果包含没有控制终端的进程

# keyword

| keyword | meaning |
| ------- | ------- |
%cpu       percentage CPU usage (alias pcpu)
%mem       percentage memory usage (alias pmem)
acflag     accounting flag (alias acflg)
args       command and arguments
comm       command
command    command and arguments
cpu        short-term CPU usage factor (for scheduling)
etime      elapsed running time
flags      the process flags, in hexadecimal (alias f)
gid        processes group id (alias group)
inblk      total blocks read (alias inblock)
jobc       job control count
ktrace     tracing flags
ktracep    tracing vnode
lim        memoryuse limit
logname    login name of user who started the session
lstart     time started
majflt     total page faults
minflt     total page reclaims
msgrcv     total messages received (reads from pipes/sockets)
msgsnd     total messages sent (writes on pipes/sockets)
nice       nice value (alias ni)
nivcsw     total involuntary context switches
nsigs      total signals taken (alias nsignals)
nswap      total swaps in/out
nvcsw      total voluntary context switches
nwchan     wait channel (as an address)
oublk      total blocks written (alias oublock)
p_ru       resource usage (valid only for zombie)
paddr      swap address
pagein     pageins (same as majflt)
pgid       process group number
pid        process ID
ppid       parent process ID
pri        scheduling priority
re         core residency time (in seconds; 127 = infinity)
rgid       real group ID
rss        resident set size
ruid       real user ID
ruser      user name (from ruid)
sess       session ID
sig        pending signals (alias pending)
sigmask    blocked signals (alias blocked)
sl         sleep time (in seconds; 127 = infinity)
start      time started
state      symbolic process state (alias stat)
svgid      saved gid from a setgid executable
svuid      saved UID from a setuid executable
tdev       control terminal device number
time       accumulated CPU time, user + system (alias cputime)
tpgid      control terminal process group ID
tsess      control terminal session ID
tsiz       text size (in Kbytes)
tt         control terminal name (two letter abbreviation)
tty        full name of control terminal
ucomm      name to be used for accounting
uid        effective user ID
upr        scheduling priority on return from system call (alias usrpri)
user       user name (from UID)
utime      user CPU time (alias putime)
vsz        virtual size in Kbytes (alias vsize)
wchan      wait channel (as a symbolic name)
wq         total number of workqueue threads
wqb        number of blocked workqueue threads
wqr        number of running workqueue threads
wql        workqueue limit status (C = constrained thread limit, T = total thread limit)
xstat      exit or stop status (valid only for stopped or zombie process)


# state

The state is given by a sequence of characters, for example, ``RWNA''.  The first character indicates the run state of the process:

I       Marks a process that is idle (sleeping for longer than about 20 seconds).
R       Marks a runnable process.
S       Marks a process that is sleeping for less than about 20 seconds.
T       Marks a stopped process.
U       Marks a process in uninterruptible wait.
Z       Marks a dead process (a ``zombie'').

Additional characters after these, if any, indicate additional state information:

+       The process is in the foreground process group of its control terminal.
<       The process has raised CPU scheduling priority.
/>      The process has specified a soft limit on memory requirements and is currently exceeding that limit; such a process is (necessarily) not swapped.
A       the process has asked for random page replacement (VA_ANOM, from vadvise(2), for example, lisp(1) in a garbage collect).
E       The process is trying to exit.
L       The process has pages locked in core (for example, for raw I/O).
N       The process has reduced CPU scheduling priority (see setpriority(2)).
S       The process has asked for FIFO page replacement (VA_SEQL, from vadvise(2), for example, a
       large image processing program using virtual memory to sequentially address voluminous
       data).
s       The process is a session leader.
V       The process is suspended during a vfork(2).
W       The process is swapped out.
X       The process is being traced or debugged.

# flags

The flags associated with the process as in the include file <sys/proc.h>:

P_ADVLOCK           0x00001      Process may hold a POSIX advisory lock
P_CONTROLT          0x00002      Has a controlling terminal
P_LP64              0x00004      Process is LP64
P_NOCLDSTOP         0x00008      No SIGCHLD when children stop
P_PPWAIT            0x00010      Parent is waiting for child to exec/exit
P_PROFIL            0x00020      Has started profiling
P_SELECT            0x00040      Selecting; wakeup/waiting danger
P_CONTINUED         0x00080      Process was stopped and continued
P_SUGID             0x00100      Had set id privileges since last exec
P_SYSTEM            0x00200      System proc: no sigs, stats or swapping
P_TIMEOUT           0x00400      Timing out during sleep
P_TRACED            0x00800      Debugged process being traced
P_WAITED            0x01000      Debugging process has waited for child
P_WEXIT             0x02000      Working on exiting
P_EXEC              0x04000      Process called exec
P_OWEUPC            0x08000      Owe process an addupc() call at next ast
P_WAITING           0x40000      Process has a wait() in progress
P_KDEBUG            0x80000        Kdebug tracing on for this process
