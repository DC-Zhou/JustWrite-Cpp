//
// Created by Zhouzhou on 2023/2/28.
//

#include <iostream>
#include <type_traits>
#include <array>

template <typename T>
struct is_floating_point
{
    constexpr static bool value = false;
};
template <>
struct is_floating_point<float>
{
    constexpr static bool value = true;
};
template <>
struct is_floating_point<double>
{
    constexpr static bool value = true;
};
template <>
struct is_floating_point<long double>
{
    constexpr static bool value = true;
};

template <typename U>
struct foo {};
template <typename U>
void func(foo<U>)
{
    std::cout << "primary template \n";
}
template <>
void func(foo<int>)
{
    std::cout << "int specialization \n";
}

template<typename T, typename U>
void func(T a, U b)
{
    std::cout << "primary template \n";
}
template <>
void func(int a, int b)
{
    std::cout << "int - int specialization \n";
}
template <>
void func(int a, double b)
{
    std::cout << "int - double specialization \n";
}

template <typename T, int S>
struct collection
{
    void operator()()
    { std::cout << "primary template\n"; }
};
template <typename T>
struct collection<T, 10>
{
    void operator()()
    { std::cout << "partial specialization <T, 10>\n"; }
};
template <int S>
struct collection<int, S>
{
    void operator()()
    { std::cout << "partial specialization <int, S>\n"; }
};
template <typename T, int S>
struct collection<T*, S>
{
    void operator()()
    { std::cout << "partial specialization <T*, S>\n"; }
};

// how print int array & char array by partial specialization
template<typename T, size_t S>
std::ostream & pretty_print(std::ostream& os, std::array<T,S> const& arr)
{
    os << "[";
    if(S > 0)
    {
        size_t i = 0;
        for(; i < S - 1; ++i)
            os << arr[i] << ",";
        os << arr[S-1];
    }
    os << "]";
    return os;
}

template<size_t S>
std::ostream& pretty_print(std::ostream& os, std::array<char, S> const& arr)
{
    os << "[";
    for(auto const& e : arr)
        os << e;
    os << "]";
    return os;
}

void test_explicit_specialization()
{
    std::cout << is_floating_point<int>::value << "\n";
    std::cout << is_floating_point<float>::value << "\n";
    std::cout << is_floating_point<double>::value << "\n";
    std::cout << is_floating_point<long double>::value << "\n";
    std::cout << is_floating_point<std::string>::value << "\n";

    std::cout << std::is_floating_point<double>::value << "\n";
    std::cout << std::is_floating_point<float>::value << "\n";
}

void test_explicit_specialization_1()
{
    func(foo<double>());
    func(foo<int>());
    func(foo<std::string>());
}

void test_explicit_specialization_2()
{
    func(1,2);
    func(1, 2.0);
    func(1.0, 2.0);
}

void test_partial_specialization_0()
{
    collection<char, 21> a;
    collection<int, 21> b;          // <int, S>
    collection<char, 10> c;         // <int, 10>
    collection<int*, 20> d;         // <T*, S>
}

void test_partial_specialization_1()
{
    std::array<int,9> arr {1,1,2,2,3,3,4,4,5};
    pretty_print(std::cout, arr);

    std::array<char, 9> str {"template"};
    pretty_print(std::cout, str);
}

int main()
{
    std::cout << "This is template specialization \n";
    test_explicit_specialization();
    test_explicit_specialization_1();
    test_explicit_specialization_2();
    test_partial_specialization_0();
    test_partial_specialization_1();
}

