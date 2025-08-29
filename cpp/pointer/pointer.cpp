#include <cstddef>
#include <iostream>

class Image
{
public:
std::size_t rows_{0};
std::size_t cols_{0};
double *data_{nullptr};
};

int main()
{
double obstacles_num = 30;
double *ptr = &obstacles_num;
Image origin_img;
std::cout<<sizeof(ptr)<<std::endl;
Image *img = &origin_img;
std::cout<<sizeof(img)<<std::endl;
}