# 互斥锁

互斥锁从字面意思说任意时刻，这把锁只能一个人拥有

## 锁的类型

| Type | Difference|
|------|-----------|
|mutex|普通的互斥锁，只允许一个时刻被一个线程拥有|
|shared_mutex|共享锁，允许多个线程拥有|
|recursive_mutex|支持在一个线程内多次获取并上锁|

## 不同应用场下的景性能比较

首先是写一个通用的计时器，便于统计花费时间
```cpp
#include <chrono>

class Timer{
    private:
    using TimePoint = std::chrono::high_resolution_clock::time_point;
    TimePoint start_;

    public:
    void recordStart() {
        start_ = std::chrono::high_resolution_clock::now();
    }

    // 计算从开始到现在的间隔时间（返回毫秒）
    double getIntervalMs() const {
        auto now = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(now - start_);
        return duration.count();
    }

    // 计算从开始到现在的间隔时间（返回秒）
    double getIntervalSec() const {
        auto now = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::duration<double>>(now - start_);
        return duration.count();
    }
};
```

1. 大量读操作，写操作较少

```cpp

std::vector<int> test_data(10000,200);
std::shared_mutex shared_mtx;
std::mutex normal_mtx;

// 第一个版本，使用共享锁
void read_data(){
    for(size_t count{0}; count < test_data.size(); count++){
        std::shared_lock<std::shared_mutex> lock(shared_mtx);
        std::cout<<test_data[count]<<std::endl; 
        std::this_thread::sleep_for(std::chrono::milliseconds(10)); }
}

// 第二个版本，只使用普通锁
// void read_data(){
//     for(size_t count{0}; count < test_data.size(); count++){
//         std::unique_lock<std::mutex> lock(normal_mtx);
//         std::this_thread::sleep_for(std::chrono::milliseconds(10));
//         std::cout<<test_data[count]<<std::endl; }
// }

int main(){
    Timer timer;
    timer.recordStart();
    std::thread t1(&read_data);
    std::thread t2(&read_data);
    t1.join();
    t2.join();

    if(t1.joinable())
       t1.join();
    if(t2.joinable())
       t2.join();

    std::cout<<"Totally spent "<<timer.getIntervalMs()<<" ms "<<std::endl;
    return 0;
}

```

| Type | Spent Time|
|------|-----------|
|mutex|202585ms|
|shared_mutex|101310ms|


## 锁的本质