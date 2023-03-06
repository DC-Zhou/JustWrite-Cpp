//
// Created by Zhouzhou on 2023/3/6.
//
#include <iostream>
#include <vector>
#include <array>
#include <numeric>
#include <algorithm>

void test_lambda()
{
    int arr[] = {1, 6, 3, 8, 4, 2, 9};
    std::sort(std::begin(arr), std::end(arr), [](int const a, int const b) { return a > b; });

    int pivot = 5;
    auto count = std::count_if(std::begin(arr), std::end(arr), [pivot](int const a) { return a > pivot; });
}

void test_lambda_feature_01()
{
    auto l1 = [] (int a)  {return a + a; };      // C++11, regular
    auto l2 = [] (auto a) {return a + a; };      // C++14, generic

    auto l3 = []<typename T>(T a) { return a + a; }; // C++20, template lambda

    auto v1 = l1(42);
    auto v2 = l1(42.0);                             // warning
//    auto v3 = l1(std::string{"42"});                // error

    auto v4 = l2(42);
    auto v5 = l2(42.0);                             // ok
    auto v6 = l2(std::string{"42"});                // ok

    auto v7 = l3(42);
    auto v8 = l3(42.0);                             // ok
    auto v0 = l3(std::string{"42"});                // ok

}

void test_lambda_feature_02()
{
    auto l1 = [] (int a, int b)  {return a + b; };      // C++11, regular
    auto l2 = [] (auto a, auto b) {return a + b; };      // C++14, generic

    auto l3 = []<typename T, typename U>(T a, U b) { return a + b; }; // C++20, template lambda

    auto v1 = l1(42,  1);
    auto v2 = l1(42.0, 1.0);                             // warning
//    auto v3 = l1(std::string{"42"}, std::string{"1"});                // error

    auto v4 = l2(42, 1);
    auto v5 = l2(42.0, 1.0);
    auto v6 = l2(std::string{"42"}, 1);                // ok
    auto v7 = l2(std::string{"42"}, std::string{"1"});                // ok

    auto v8 = l3(42, 1);
    auto v9 = l3(42.0, 1);                             // ok
    auto v10 = l3(std::string{"42"}, 1);                // ok
    auto v11 = l3(std::string{"42"}, std::string{"1"});                // ok
}

void test_lambda_with_array()
{
    auto l = []<typename T, size_t N>(std::array<T, N> const& arr)
    {
        return std::accumulate(arr.begin(), arr.end(), static_cast<T>(0));
    };

//    auto v1 = l(1);         // error
    auto v2 = l(std::array<int, 3>{1, 2, 3});
}

void test_generic_factorial()
{
    auto factorial = [](auto f, int const n) {
        if (n < 2) return 1;
        else return n * f(f, n-1);
    };

    factorial(factorial, 5);
}

int main()
{
    std::cout << "Hello lambda \n";
    test_lambda();
    test_lambda_feature_01();
    test_lambda_feature_02();
    test_lambda_with_array();
}