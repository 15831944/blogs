未命名信号量

命名信号量

# 内核中的定义

```
struct semaphore 
{
    raw_spinlock_t		lock;
    unsigned int		count;		// 其值为1则为二值信号量
    struct list_head	wait_list;	// 和互斥量一致
};
```
# 概念

“In computer science, a semaphore is a variable or abstract data type that provides a simple but useful abstraction for controlling access by multiple processes to a common resource in a parallel programming environment.

A useful way to think of a semaphore is as a record of how many units of a particular resource are available, coupled with operations to safely (i.e., without race conditions) adjust that record as units are required or become free, and if necessary wait until a unit of the resource becomes available. 

Semaphores are a useful tool in the prevention of race conditions and deadlocks; however, their use is by no means a guarantee that a program is free from these problems. 

Semaphores which allow an arbitrary resource count are called counting semaphores, while semaphores which are restricted to the values 0 and 1 (or locked/unlocked, unavailable/available) are called binary semaphores (same functionality that mutexes have).

思考信号量的一个有用的方式是，把它当作特定资源的单元的可用的数量的记录，结合单元被请求或释放时安全地调节这个记录的操作，并在必要时等待，直到资源的单元变得可用。

信号量是有用的工具用于防止竞争条件和死锁；然而，这些用法不保证程序免除这些问题。

允许任意资源计数的信号量称为计数信号量，而限制在0和1两个值的信号量称为二值信号量。

# 作用

semaphore 只能用在进程上下文中，不能用在中断上下文中。因为可能导致进程休眠，而中断中是没有进程调度的。

semaphore 可能对应多个 holder，而锁在同一个时刻顶多只有一个 holder。

You can draw some interesting conclusions from the sleeping behavior of semaphores:

你可以从信号量的休眠行为得出有趣的结论：

Because the contending tasks sleep while waiting for the lock to become available, semaphores are well suited to locks that are held for a long time.

因为相互竞争的任务在等待锁变得可用时会休眠，信号量很适合锁住很长时间的锁。

Conversely, semaphores are not optimal for locks that are held for very short periods because the overhead of sleeping, maintaining the wait queue, and waking back up can easily outweigh the total lock hold time.

相反，信号量不适合锁住保持时间很短暂的锁，因为休眠的系统开销，维护等待队列，并且从休眠中唤醒的时间很容易多于锁的保持时间。

Because a thread of execution sleeps on lock contention, semaphores can be obtained only in process context because interrupt context is not schedulable.

因为执行线程在锁的竞争中会导致其休眠，信号量只能存在于进程上下文中，因为中断上下文没有进程调度。

You can (although you may not want to) sleep while holding a semaphore because you will not deadlock when another process acquires the same semaphore. (It will just go to sleep and eventually let you continue.)

或许你不想，但你仍可以在拥有一个信号量时休眠，因为当另一个进程获取相同的信号量时，你并不会死锁。只会让你继续休眠并最终让你继续执行。

You cannot hold a spin lock while you acquire a semaphore, because you might have to sleep while waiting for the semaphore, and you cannot sleep while holding a spin lock.

在你获取一个信号量期间，不可以拥有自旋锁，因为在你等待信号量时，可能必须休眠，而拥有自旋锁的同时是不能休眠的。

These facts highlight the uses of semaphores versus spin locks. In most uses of semaphores, there is little choice as to what lock to use. If your code needs to sleep, which is often the case when synchronizing with user-space, semaphores are the sole solution. It is often easier, if not necessary, to use semaphores because they allow you the flexibility of sleeping. When you do have a choice, the decision between semaphore and spin lock should be based on lock hold time. Ideally, all your locks should be held as briefly as possible. With semaphores, however, longer lock hold times are more acceptable. Additionally, unlike spin locks, semaphores do not disable kernel preemption and, consequently, code holding a semaphore can be preempted. This means semaphores do not adversely affect scheduling latency.

这些事实突出了信号量区别于自旋锁的用途。在信号量的大多数用途中，对于用哪种锁几乎没有选择。

如果你的代码需要休眠，常见于和用户空间同步的情况，信号量是唯一的解决方案。

即使并非必要，用信号量也是相对容易的，因为信号量给予你休眠的灵活性。

当你选哪种都可以时，应基于锁的保持时间决定用信号量还是自旋锁。

理想情况下，你所有的锁应保持得尽可能短暂。

然而，对于信号量，长时间的锁相对更加可接受。

另外，不同于自旋锁，信号量不会禁用内核的抢占式多任务处理，并且，因此，保持一个信号量的代码可以被抢占。

这意味着信号量反而不会影响调度延时。

What to Use: Spin Locks Versus Semaphores

自旋锁和信号量的使用的选择


| Requirement | Recommended Lock |
| - | - |
| Low overhead locking 低开销的锁 |  自旋锁 |
| Short lock hold time 短时的锁 | 自旋锁 |
| Long lock hold time 长时的锁 | 信号量 |
| Need to lock from interrupt context 需要从中断上下文去锁 | 自旋锁 |
| Need to sleep while holding lock 保持锁过程需要休眠 | 信号量 | 

互斥量

多个线程企图在同一个时刻修改相同的变量，用互斥量。

优点：使线程间很好的合作，避免对于变量、函数以及资源的访问冲突。

缺点：它使程序运行变慢，程序效率低下。

信号量

信号量是一个变量，它可以被系统中的任何进程所访问。

进程间可以使用这个变量来协调对于共享内存和其他资源的访问。

信号量的使用比线程复杂的多，进程和线程可以接受任何种类的信号量。

信号量是系统中的全局变量。

条件变量

条件对象是进程中的全局变量。

进程间的通信

1. 文件。
2. 命名管道。
3. 共享内存。（为解决访问文件冲突，其中提供了一个更加灵活的机制来合作：信号量）
4. 消息队列

线程A获取到一个信号量，线程B可以把它释放掉（合理合法，参考生产者消费者模型）
线程A获取一个互斥量，线程B把它释放掉吗？（也许法但肯定不合理）

# 参考

[深层次探讨mutex与semaphore之间的区别(中)](http://blog.chinaunix.net/uid-12461657-id-3487457.html)

[有了信号量以后，还要线程间的互斥锁，进程间的文件锁何用？](http://bbs.csdn.net/topics/270014022)

http://www.kernel.org/doc/man-pages/online/pages/man7/pthreads.7.html

http://www.cs.fsu.edu/~baker/devices/lxr/http/source/linux/kernel/futex.c?v=2.6.11.8

http://www.cs.purdue.edu/homes/cs354/LectureNotes/Fall2000/9/
