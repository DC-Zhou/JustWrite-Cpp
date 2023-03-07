//
// Created by Zhouzhou on 2023/3/6.
//
#include <iostream>

template<typename T>
T min(T a, T b)
{
    return a < b ? a : b;
}

template <typename T, typename... Args>
T min(T a, Args... args)
{
    return min(a, min(args...));
}

void test_variadic_template()
{
    std::cout << "min(42.0, 7.5) = " << min(42.0, 7.5) << std::endl;
    std::cout << "min(1,5,3,-4,9) = " << min(1,5,3,-4,9) << std::endl;
}

int main()
{
    std::cout << "use variadic template: \n";
    test_variadic_template();
}
