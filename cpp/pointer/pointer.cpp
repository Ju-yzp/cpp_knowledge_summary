// Copyright 2025 Your Name/Your Team
// Licensed under the MIT License (optional, 根据项目实际协议补充)

#include <cstddef>
#include <iostream>

// 修复1：class后大括号紧跟末尾，不单独换行
class Image
{
public:
  std::size_t rows_{0};
  std::size_t cols_{0};
  double * data_{nullptr};
};

// 修复3：main()后大括号紧跟末尾，不单独换行
int main()
{
  double obstacles_num = 30;
  double * ptr = &obstacles_num;
  Image origin_img;
  std::cout << sizeof(ptr) << std::endl;
  Image * img = &origin_img;
  std::cout << sizeof(img) << std::endl;
  return 0;
}
