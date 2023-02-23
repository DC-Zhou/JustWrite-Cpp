//
// Created by a'a on 2023/2/20.
//
#include <iostream>
#include <array>

template <typename Impl>
struct base{
    template<typename Buffer, typename ... Args>
    void read_some(Buffer buf, Args ... args){
        impl_.read_some(buf, args...);
    }

    Impl impl_;
};

struct derived_obj {
    void read_some(std::string buf){
        std::cout << "read string " << std::endl;
    }

    void read_some(std::string buf, int size){
        std::cout << "read string, size:" << size << std::endl;
    }

    void read_some(std::array<char, 20> buf)
    {
        std::cout << "read array " << std::endl;
    }
};

int main() {
    std::cout << "Hello, Static polymorphism based on variable template parameters !" << std::endl;

    base<derived_obj> d1{};
    d1.read_some("hello");
    d1.read_some("hello", 42);
}