条件变量本身可以是互斥锁所保护的临界资源

pthread_cond_wait 函数不满足时，会解锁互斥量并挂起，满足后，会加锁互斥量并继续执行

# 参考

[浅析pthread_cond_wait - weihe6666 - ITeye技术网站](http://weihe6666.iteye.com/blog/1170141)
