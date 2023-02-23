//
// Created by Zhouzhou on 2023/2/22.
//
#include <iostream>

template<typename Char>
constexpr std::size_t constexpr_strlen(const Char* s) noexcept {
    std::size_t ret = 0;
    while(*s++){
        ++ ret;
    }
    return ret;
}

void test_strlen_in_constexpr(){
    auto len = constexpr_strlen("hello world");     // strlen in running time
    constexpr auto len1 = constexpr_strlen("hello world");  // strlen in compiling time
}

struct Dummy{
        Dummy(size_t val) : val_(val) {}
        size_t val_;
    };

#define GetDummy() Dummy(constexpr_strlen("Hello world"))

void test_strlen_in_non_constexpr(){
    Dummy d(constexpr_strlen("hello world"));   // strlen in running
    GetDummy();     // strlen in running
}

struct Dummy2{
    Dummy2(size_t val) : val_(val) {}
    size_t val_;
};

Dummy2 GetVal(){
    constexpr auto len = constexpr_strlen("Hello world");
    return Dummy2(len);
}

void test_strlen_in_constexper(){
    Dummy2 d(constexpr_strlen("Hello world"));      // strlen in running
    GetVal();       // strlen in compiling

}

#define GET_VAL1(str) []{constexpr auto len = constexpr_strlen(str); return Dummy(len);}()

int main()
{
    test_strlen_in_constexpr();
    test_strlen_in_non_constexpr();
    test_strlen_in_constexper();
    GET_VAL1("Hello World");        // strlen in compiling time
}