// Copyright 2025 Ju-p
// Licensed under the MIT License (

#include <iostream>

// auto get_lambda() {
//     int num = 20;
//     return [&]() {
//         num++;
//         std::cout << num << std::endl;
//     };
//}

int main() {
    int num = 30;
    // 按值捕获，副本
    auto func = [=]() { std::cout << num << std::endl; };
    func();
    num = 50;
    func();

    // 引用捕获
    auto func_ = [&]() { std::cout << num << std::endl; };
    func_();
    num = 60;
    func_();

    // 按值捕获后，不能修改值
    // auto change_value = [=](){ num = 80; } 不合法
    // 添加mutable后，可以修改值
    auto change_value = [=]() mutable { num = 80; };
    change_value();

    // 错误示例
    // auto error_lambda = get_lambda();
    // error_lambda();
    return 0;
}
