# Lambda

Lamdba表达式对于程序员来说，是一个好用且常用的cpp特性，能够避免声明很多少量使用的函数

## Lambda 表达式用法

```cpp

// lamdba表达式声明: [捕获列表](参数){ 函数体 }
// 捕获列表可选参数: =(按值捕获), &(引用捕获), 变量名显式指定捕获对象）

int num = 30;
auto func = [=](){ std::cout<<num<<std::endl; };
func();
num = 50;
func();

auto func_ = [&](){ std::cout<<num<<std::endl; };
func_();
num = 60;
func_();

auto change_value = [=]()mutable{ num = 80; } ;
change_value();

```

在上面的代码中，func通过按值捕获，获得的是num的副本，在函数体内不能对num做写操作，原因是lamdba表达式本质上是生成一个匿名对象(class)，调用lamdba表达式时，是调用()重载运算符.而按值捕获的对象在数据成员中是const的，也就是不可修改的，你必须添加mutable,告诉编译器你需要消除const属性.

func是通过引用捕获num的，匿名对象的num是它的引用，那么我们自然可以修改num.在引用捕获时，我们应该注意被引用对象的生命周期，避免引用悬垂(通俗一点来讲，就是是用了一个已经不存在的对象).

```cpp
#include <iostream>

auto get_lambda() {
    int num = 20;
    return [&]() {
        num++;
        std::cout << num << std::endl;
    };
}

int main() {
    auto error_lambda = get_lambda();
    error_lambda();
    return 0;
}

```

在上面的就是一个错误例子，在调用error_lambda时，因为nun是局部变量，在栈上已经回收了，是一个消失的对象，原先在栈上的内存地址可能已经被其他对象使用了.
