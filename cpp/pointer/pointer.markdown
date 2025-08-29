# 普通指针

指针是一个双刃剑


## 本质

指针本质其实是一个记录物品地址的纸条

```cpp
double *ptr = new double;
std::cout<<ptr<<std::endl;
```

通过对指针的解引用，我们可以获得物品

```cpp
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
```

我们通过sizeof()函数获得两个不同类型指针的大小，发现都是八字节的，这是由于地址总线造成的，它最多只能访问这么大的内存

```cpp
ptr = &origin_img;
```

如果在上一段代码中，写入这一段话，在编译期将会不通过，因为指针类型和origin_ptr的不相同,但是我们可以通过强转origin_ptr的类型给ptr赋值.话又说回来，为什么不支持直接赋值呐

我认为有以下几点原因:
1. 如果支持程序员进行这种隐式转换，那么一旦程序员忘记这个指针实际指向的对象是什么，那么极其容易造成访问不合法（内存模型问题）
2. 显式转换代表着程序员知道自己在做什么，那么责任由他自己承担