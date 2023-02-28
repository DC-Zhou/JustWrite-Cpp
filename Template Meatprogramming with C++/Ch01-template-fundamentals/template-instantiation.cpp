//
// Created by ZhouZhou on 2023/2/28.
//
#include <iostream>
#include <type_traits>

template <typename T>
struct foo1
{
    void f() {}
    void g() {}
};

template <typename T>
struct  foo2
{
    static T data;
};
template <typename T> T foo2<T>::data = 0;

void test_implicit_instantiation(){

    foo1<int> *p;
    foo1<int> x;
    foo1<double> *q;
    // compiler only instantiate x;

    x.f();
    q -> g();
    // compiler need to instantiate x, foo1<int>::f(), foo1<double>, foo1<double>::g()
}

void test_static_implicit_instantiation(){
    foo2<int> a;
    foo2<double> b;
    foo2<double> c;

    std::cout << a.data << "\n";
    std::cout << b.data << "\n";
    std::cout << c.data << "\n";
    b.data = 42;
    std::cout << a.data << "\n";
    std::cout << b.data << "\n";
    std::cout << c.data << "\n";
}

void test_explicit_instantiation_definition(){
    // Explicit instantiation definition
    namespace ns
    {
        template <typename T>
        struct wrapper
        {
            T value;
        };
        template struct wrapper<int>;   // [1]
    }
//    template struct ns::wrapper<double> a;// [2]
}



int main(){

}
