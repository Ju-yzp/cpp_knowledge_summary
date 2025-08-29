// Copyright 2025 Ju-p
// Licensed under the MIT License (optional, 根据项目实际协议补充)

#include <cstddef>
#include <iostream>

class Image {};

int main() {
    double obstacles_num = 30;
    double* ptr = &obstacles_num;
    Image origin_img;
    std::cout << sizeof(ptr) << std::endl;
    Image* img = &origin_img;
    std::cout << sizeof(img) << std::endl;
    return 0;
}
