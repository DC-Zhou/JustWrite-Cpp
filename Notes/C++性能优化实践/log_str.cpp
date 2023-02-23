//
// Created by Zhouzhou on 2023/2/22.
//
// 编译时字符串操作性能优化
// C++性能优化实践（二）
#include <sstream>
#include <string>
#include "ScopedTimer.h"


std::string log_str(const char* filename, int line_number){
    std::string_view s(filename);
    auto pos = s.rfind('/');
    auto name = (pos == std::string_view::npos) ? filename : s.substr(pos + 1);
    std::stringstream ss;
    ss << name << ":" << line_number << ":";
}

//template<class Char, std::size_t N>
//class FixedString{
//    Char data_[N + 1u];
//    std::size_t size_;
//public:
//    template<class That, std::size_t... Is>
//    constexpr FixedString(const That& that, std::size_t size, std::index_sequence<Is...>,
//            std::size_t pos = 0, std::size_t count = npos) noexcept
//            :data_{ (Is < (size - pos) && Is < count ? that[Is + pos] : Char(0))..., Char(0)},
//            size_{std::min(size - pos, count)} {}
//
//constexpr  std::size_t size() const noexcept { return size_;}
//};
//
//
//void test_construct(){
//    constexpr const char* str = "Hello";
//    constexpr  FixedString<char, 5> fixed_str(str, 5, std::make_index_sequence<5>{});
//    static_assert(fixed_str.size() == 5);
//
//}




void test_log_str(){
    ScopedTimer timer("ss log str");
    for(int i = 0; i < 10000; ++i){
        log_str(__FILE__, __LINE__);
    }
}

int main()
{
    test_log_str();
}


