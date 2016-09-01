# 内核中的定义

```
struct mutex 
{
    /* 1: unlocked, 0: locked, negative: locked, possible waiters */
    atomic_t			count;
    spinlock_t			wait_lock;
    struct list_head	wait_list;

#if defined(CONFIG_DEBUG_MUTEXES) || defined(CONFIG_SMP)
    struct task_struct *owner;
#endif

#ifdef CONFIG_DEBUG_MUTEXES
    const char *name;
    void *magic;
#endif

#ifdef CONFIG_DEBUG_LOCK_ALLOC
    struct lockdep_map	dep_map;
#endif

};
```

```
struct mutex {
	/* 1: unlocked, 0: locked, negative: locked, possible waiters */
	atomic_t			count;
	spinlock_t			wait_lock;
	struct list_head	wait_list;
	struct task_struct	*owner;
};
```

# 1. 作用

同一时刻，只允许一个线程对临界区进行访问

多个临界区之间是互斥的，即只能一个执行完了再执行下一个

临界区是指加锁和解锁之间的那段代码

例如，线程1的代码块A和线程2的代码块B都使用同一个互斥量加锁和解锁。

内核先调度线程1，线程1对互斥量并执行代码块A。

此时如果线程2被调度执行代码块B，由于互斥量已经被锁，因此线程2会阻塞在代码块B起始处。

直到线程1执行完代码块A并解锁后，线程2才能执行代码块B。

最终导致代码块A和代码块B的执行是互斥的。即一个执行期间，另一个不能执行。临界区内的操作近似为原子操作。

互斥锁的主要特点是互斥锁的释放必须由上锁的进(线)程释放，如果拥有锁的进(线)程不释放，那么其它的进(线)程永远也没有机会获得所需要的互斥锁。

# 2. 原理

使进程休眠

在实现中，锁并不是与某个具体的变量进行关联，它本身是一个独立的对象。进(线)程在有需要的时候获得此对象，用完不需要时就释放掉。

# 3. 互斥量属性变量

## 1. 互斥量类型

### 1. Linux

PTHREAD_MUTEX_NORMAL(默认属性)

PTHREAD_MUTEX_ERRORCHECK(会进行错误检查，速度比较慢)

PTHREAD_MUTEX_RECURSIVE(递归锁)同一个线程对一个递归锁加锁多次，会有一个锁计数器，解锁的时候也需要解锁这个次数才能释放该互斥量

### 2. uclinux

PTHREAD_MUTEX_TIMED_NP(普通锁)

PTHREAD_MUTEX_ADAPTIVE_NP(适应锁)

PTHREAD_MUTEX_RECURSIVE_NP(检错锁)

PTHREAD_MUTEX_ERRORCHECK_NP(嵌套锁)

## 2. 互斥量共享属性

PTHREAD_PROCESS_SHARE(进程间锁：进程间同步)

PTHREAD_PROCESS_PRIVATE(进程内锁：进程内线程间同步)

# 4. 死锁

## 1. 死锁的发生

1. 一个线程对同一个互斥量加锁两次, 第1此加锁成功, 第2此加锁则会阻塞, 那么线程自身就会陷入死锁

2. 线程1拥有互斥量 A, 并试图访问互斥量 B, 线程2拥有互斥量 B, 并试图访问互斥量 A, 则两个线程都将阻塞

## 2. 死锁的避免

1. 对互斥量进行排序, 总是以相同的顺序对互斥量进行加锁

2. 使用 pthread_mutex_trylock 接口, 如果成功返回, 则可以继续前进, 如果不能获取锁, 则先释放已经占有的锁, 做好清理工作, 然后过一段时间再试
