//
// Created by Zhouzhou on 2023/2/25.
//

#include <iostream>
#include <assert.h>

template <typename T>
class wrapper{
public:
    wrapper(T const v) : value(v) { }

    T const& get() const { return value; }
private:
    T value;
};


// a class template must be defined at the point where the template instantiation occurs.
// otherwise the compiler will generate an error

void use_wrapper(wrapper<int>* ptr);

void test_class_template()
{
//
}

void use_wrapper(wrapper<int> *ptr)
{
    std::cout << "show: " << ptr->get() << "\n";
}

int main(){
    std::cout << "Hello, class template\n";
    wrapper a(42);
    wrapper<int> b(42);
    wrapper<short> c(42);
    wrapper<double> d(42);
    wrapper e("42");

}