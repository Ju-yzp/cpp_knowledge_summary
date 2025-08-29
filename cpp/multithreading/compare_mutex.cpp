// Copyright 2025 Ju-p
// Licensed under the MIT License

// 对于各种互斥锁在不同应用场景下的性能比较

#include <chrono>
#include <cstddef>
#include <iostream>
#include <mutex>
#include <shared_mutex>
#include <thread>
#include <vector>

std::vector<int> test_data(10000, 200);
std::shared_mutex shared_mtx;
std::mutex normal_mtx;

class Timer {
private:
    using TimePoint = std::chrono::high_resolution_clock::time_point;
    TimePoint start_;

public:
    void recordStart() { start_ = std::chrono::high_resolution_clock::now(); }

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

// 读多写少的应用场景

// 第一个版本，使用共享锁
void read_data() {
    for (size_t count{0}; count < test_data.size(); count++) {
        std::shared_lock<std::shared_mutex> lock(shared_mtx);
        std::cout << test_data[count] << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

// 第二个版本，只使用普通锁
// void read_data(){
//     for(size_t count{0}; count < test_data.size(); count++){
//         std::unique_lock<std::mutex> lock(normal_mtx);
//         std::this_thread::sleep_for(std::chrono::milliseconds(10));
//         std::cout<<test_data[count]<<std::endl; }
// }

int main() {
    Timer timer;
    timer.recordStart();
    std::thread t1(&read_data);
    std::thread t2(&read_data);
    t1.join();
    t2.join();

    if (t1.joinable()) t1.join();
    if (t2.joinable()) t2.join();

    std::cout << "Totally spent " << timer.getIntervalMs() << " ms " << std::endl;
    return 0;
}
