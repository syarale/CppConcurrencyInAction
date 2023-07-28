# 《C++ 并发编程实战》编程练习
- thread_guard: 利用 RAII 过程等待线程完结
- scoped_thread: 在离开对象所在的作用域前，确保线程完结（转移线程的归属权）
- joining_thread: std::jthead 的一个简单实现，作用和scoped_thread 类似 
- threadsafe_stack: 线程安全栈的一个简单实现，消除 pop 接口固有的条件竞争
- hierarchical_mutex: 层级互斥量的一个简单实现，限制加锁次序避免死锁
- threadsafe_queue: 线程安全对了的一个简单实现，增加了 wait_and_pop 接口