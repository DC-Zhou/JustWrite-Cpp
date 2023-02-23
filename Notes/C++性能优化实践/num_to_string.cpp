// C++ num to string 5 ways
// from: C++性能优化（一）
#include <charconv>
#include <string>
#include <sstream>
#include "ScopedTimer.h"

// macro
#define STR(x) #x
#define TOSTRING(x) STR(x)


namespace detail
{
    template<uint8_t... digits> struct postive_to_chars{
        static const char value[];
        static constexpr size_t size = sizeof...(digits);
    };

    template<uint8_t... digits> const char postive_to_chars<digits...>::value[] = {('0' + digits)..., 0};

    template<uint8_t... digits> struct negative_to_chars{static const char value[]; };
    template<uint8_t... digits> const char negative_to_chars<digits...>::value[] = {'-', ('0' + digits)..., 0};

    template<bool neg, uint8_t... digits>
    struct to_chars : postive_to_chars<digits...> {};

    template<uint8_t... digits>
    struct to_chars<true, digits...> : negative_to_chars<digits...>{};

    template<bool neg, uintmax_t rem, uint8_t... digits>
    struct explode : explode<neg, rem / 10, rem %10, digits...>{};

    template<bool neg, uint8_t... digits>
    struct explode<neg, 0, digits...> : to_chars<neg, digits...>{};

    template<typename T>
    constexpr  uintmax_t cabs(T num) { return (num < 0) ? -num : num; }
}

template<typename T, T num>
struct string_from : ::detail::explode<num < 0, ::detail::cabs(num)> {};

void ss_to_string(){
    ScopedTimer timer("ss_to_string");
    for(size_t i = 0; i < 10000; i++){
        std::stringstream ss;
        ss << i;
    }
}

void to_string(){
    ScopedTimer timer("to_sting");
    for(size_t i = 0; i < 10000; i++){
        std::to_string(i);
    }
}

//void fmt_string(){
//    ScopedTimer timer("fmt_to_string");
//    for(size_t i = 0; i < 10000; i++){
//        std::fmt::format("{}", i);
//    }
//}

void conv_string(){
    ScopedTimer timer("conv_to_string");
    for(size_t i = 0 ; i < 10000; i++){
        char str[10];
        std::to_chars(str, str+10, i);
    }
}

void macro_string(){
    ScopedTimer timer("macro_to_sting");
    for(size_t i = 0; i < 10000; i++){
        TOSTRING(1);
    }
}

void compile_time_to_string(){
    ScopedTimer timer("compile_time_to_string");
    for(int i = 0; i < 10000; i++){
        string_from<unsigned , 1> ::value;
    }
}



int main() {
    std::cout << "Hello, Compile_time_optimize!" << std::endl;
    ss_to_string();
    to_string();
    conv_string();
    macro_string();
    compile_time_to_string();
    static_assert(string_from<unsigned , 100> :: size == 3);
    return 0;
}

//Result: Release:
//Hello, Compile_time_optimize!
//ss_to_string:2030916ns
//to_sting:127250ns
//conv_to_string:52167ns
//macro_to_sting:42ns
//compile_time_to_string:0ns