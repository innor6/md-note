使用go线程时，通常将循环变量等临时的、线程私有的变量作为匿名函数的参数，而一些共享变量直接在函数体中使用。



-race 选项，动态检查线程间的数据竞争



编程风格：互斥锁 or channel？

- 状态：sharing and locks
- 通信（等待和通知）：channels、sync.Cond、time.Sleep()

