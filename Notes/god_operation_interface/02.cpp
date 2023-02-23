//
// Created by Zhouzhou on 2023/2/20.
//

#include <iostream>
#include <vector>
#include <array>

template <typename Impl>
struct base{
    template<typename Buffer>
    void read_some(Buffer buf){
        impl_.read_some(buf);
    }

    Impl impl_;
};

struct derived_obj {
    void read_some(std::string buf){
        std::cout << "read string " << std::endl;
    }

    void read_some(std::array<char, 20> buf)
    {
        std::cout << "read array " << std::endl;
    }
};

int main() {
    std::cout << "Hello, Static polymorphism based on stable template parameters !" << std::endl;

    base<derived_obj> d1{};
    d1.read_some("hello");

    std::array<char, 20> arr{"test"};
    d1.read_some(arr);
}