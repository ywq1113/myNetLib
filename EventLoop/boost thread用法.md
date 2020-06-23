# Boost线程库用法

编译时加上`-lboost_system -lboost_thread-mt`来编译

## 代码

### Constructor

```cpp
#include <boost/thread/thread.hpp>

thread() noexcept; // Default Constructor
thread(thread&& other) noexcept; // Move Constructor

explicit thread(const boost::function0<void>& threadfunc); // 传入函数对象

this->get_id() = thread::id();  //获取id

void join();
```

## 使用方法

### 创建一个线程

```cpp
typedef std::function<void()> cb_func;

void func()
{
    cout << "hello world" << endl;
}

void test1()
{
    boost::thread thd(&func);  //传入函数指针
    thd.join();
}

void test2()
{
    boost::thread thd2(f);  //通过bind创建
    cb_func f = boost::bind(&func);
    thd2.join();
}

int main()
{
    test1();
    test2();
    return 0;
}

```

### 批量创建多个线程

```cpp
#include <functional>

typedef std::function<void()> cb_func;

boost::thread_group threads;
for(int i = 0; i < 10; ++i)
{
    threads.create_thread(cb_func);
}

threads.join_all();
```
